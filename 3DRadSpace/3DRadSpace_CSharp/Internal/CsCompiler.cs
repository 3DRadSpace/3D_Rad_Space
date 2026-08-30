using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.Loader;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.Emit;
using System.Text;

namespace Engine3DRadSpace.Internal;

/// <summary>
/// Provides C# source code compilation and execution capabilities for the game engine.
/// Designed to work with nethost for dynamic script compilation and execution.
/// </summary>
public static class CsCompiler
{
	private static readonly object _compileLock = new();
	private static List<MetadataReference>? _cachedReferences;

	/// <summary>
	/// Compiles C# source code from a string.
	/// </summary>
	/// <param name="source">The C# source code to compile.</param>
	/// <returns>A CompilationResult containing the outcome of compilation.</returns>
	public static CompilationResult Compile(string source)
	{
		return CompileInternal(source, null);
	}

	/// <summary>
	/// Compiles C# source code from a file.
	/// </summary>
	/// <param name="filePath">Path to the .cs file containing the source code.</param>
	/// <returns>A CompilationResult containing the outcome of compilation.</returns>
	public static CompilationResult CompileFromFile(string filePath)
	{
		try
		{
			if (!File.Exists(filePath))
			{
				return new CompilationResult
				{
					Success = false,
					Errors = new List<string> { $"File not found: {filePath}" }
				};
			}

			string source = File.ReadAllText(filePath);
			return CompileInternal(source, filePath);
		}
		catch (Exception ex)
		{
			return new CompilationResult
			{
				Success = false,
				Errors = new List<string> { $"Error reading file: {ex.Message}" }
			};
		}
	}

	/// <summary>
	/// Adds additional assembly references for script compilation.
	/// Useful when scripts need to reference additional libraries.
	/// </summary>
	/// <param name="assemblyPaths">Paths to additional assemblies to reference.</param>
	public static void AddReferences(params string[] assemblyPaths)
	{
		lock (_compileLock)
		{
			_cachedReferences ??= GetDefaultReferences();

			foreach (var path in assemblyPaths)
			{
				if (File.Exists(path))
				{
					_cachedReferences.Add(MetadataReference.CreateFromFile(path));
				}
			}
		}
	}

	/// <summary>
	/// Clears the cached references, forcing them to be rebuilt on next compilation.
	/// </summary>
	public static void ClearReferenceCache()
	{
		lock (_compileLock)
		{
			_cachedReferences = null;
		}
	}

	/// <summary>
	/// Initializes and warms up the Roslyn compiler. (C++ callable version)
	/// Call this during plugin startup (e.g., in PluginMain) to avoid the ~1-2 second
	/// startup cost on the first script compilation.
	/// </summary>
	/// <remarks>
	/// Note: This is the [UnmanagedCallersOnly] version for C++.
	/// Use InitializeManaged() from C# code.
	/// </remarks>
	[UnmanagedCallersOnly]
	public static void Initialize()
	{
		InitializeManaged();
	}

	/// <summary>
	/// Initializes and warms up the Roslyn compiler. (C# callable version)
	/// Call this during plugin startup to avoid the ~1-2 second startup cost on first compilation.
	/// </summary>
	/// <remarks>
	/// This method:
	/// - Pre-caches all assembly references
	/// - Performs a dummy compilation to JIT-compile Roslyn code paths
	/// - Should be called once during application startup
	/// </remarks>
	public static void InitializeManaged()
	{
		lock (_compileLock)
		{
			// Pre-cache references
			_cachedReferences = GetDefaultReferences();

			// Perform a minimal dummy compilation to warm up Roslyn JIT
			// This forces the JIT compiler to compile Roslyn's internal code paths
			const string dummyCode = "class __RoslynWarmup { }";
			
			var syntaxTree = CSharpSyntaxTree.ParseText(dummyCode);
			var compilation = CSharpCompilation.Create(
				assemblyName: "__WarmupAssembly",
				syntaxTrees: new[] { syntaxTree },
				references: _cachedReferences,
				options: new CSharpCompilationOptions(OutputKind.DynamicallyLinkedLibrary)
			);

			// Emit to memory to trigger full compilation pipeline
			using var ms = new MemoryStream();
			compilation.Emit(ms);
		}
	}

	private static CompilationResult CompileInternal(string source, string? sourceFilePath)
	{
		lock (_compileLock)
		{
			try
			{
				// Parse the source code
				var syntaxTree = sourceFilePath != null
					? CSharpSyntaxTree.ParseText(source, path: sourceFilePath, encoding: Encoding.UTF8)
					: CSharpSyntaxTree.ParseText(source);

				// Get references to required assemblies
				var references = _cachedReferences ?? GetDefaultReferences();

				// Create compilation options
				var compilationOptions = new CSharpCompilationOptions(
					OutputKind.DynamicallyLinkedLibrary,
					optimizationLevel: OptimizationLevel.Release,
					allowUnsafe: true,
					platform: Platform.X64
				);

				// Create the compilation
				string assemblyName = sourceFilePath != null
					? Path.GetFileNameWithoutExtension(sourceFilePath)
					: $"DynamicScript_{Guid.NewGuid():N}";

				var compilation = CSharpCompilation.Create(
					assemblyName: assemblyName,
					syntaxTrees: new[] { syntaxTree },
					references: references,
					options: compilationOptions
				);

				// Compile to memory stream
				using var ms = new MemoryStream();
				using var pdbMs = new MemoryStream();
				
				var emitOptions = new EmitOptions(
					debugInformationFormat: DebugInformationFormat.PortablePdb
				);

				EmitResult result = compilation.Emit(ms, pdbMs, options: emitOptions);

				if (!result.Success)
				{
					// Compilation failed - collect errors and warnings
					var errors = result.Diagnostics
						.Where(d => d.Severity == DiagnosticSeverity.Error)
						.Select(d => FormatDiagnostic(d))
						.ToList();

					var warnings = result.Diagnostics
						.Where(d => d.Severity == DiagnosticSeverity.Warning)
						.Select(d => FormatDiagnostic(d))
						.ToList();

					return new CompilationResult
					{
						Success = false,
						Errors = errors,
						Warnings = warnings
					};
				}

				ms.Seek(0, SeekOrigin.Begin);
				pdbMs.Seek(0, SeekOrigin.Begin);
			
				var assemblyLoadContext = new AssemblyLoadContext($"ScriptContext_{assemblyName}", isCollectible: true);

				assemblyLoadContext.Resolving += (context, name) =>
				{
					foreach (var loaded in AppDomain.CurrentDomain.GetAssemblies())
					{
						if (loaded.GetName().Name == name.Name)
							return loaded;
					}
					return null;
				};

				var assembly = assemblyLoadContext.LoadFromStream(ms, pdbMs);

				var warnings2 = result.Diagnostics
					.Where(d => d.Severity == DiagnosticSeverity.Warning)
					.Select(d => FormatDiagnostic(d))
					.ToList();

				return new CompilationResult
				{
					Success = true,
					Assembly = assembly,
					LoadContext = assemblyLoadContext,
					Warnings = warnings2,
					SourceFilePath = sourceFilePath
				};
			}
			catch (Exception ex)
			{
				return new CompilationResult
				{
					Success = false,
					Errors = new List<string> { $"Exception: {ex.Message}\n{ex.StackTrace}" }
				};
			}
		}
	}

	private static string FormatDiagnostic(Diagnostic diagnostic)
	{
		var lineSpan = diagnostic.Location.GetLineSpan();
		return $"{diagnostic.Id} at Line {lineSpan.StartLinePosition.Line + 1}: {diagnostic.GetMessage()}";
	}

	/// <summary>
	/// Gets the default set of assembly references for compilation.
	/// </summary>
	private static List<MetadataReference> GetDefaultReferences()
	{
		var references = new List<MetadataReference>();

		// Add core .NET references
		var runtimePath = Path.GetDirectoryName(typeof(object).Assembly.Location)!;
		
		references.Add(MetadataReference.CreateFromFile(typeof(object).Assembly.Location));
		references.Add(MetadataReference.CreateFromFile(typeof(Console).Assembly.Location));
		references.Add(MetadataReference.CreateFromFile(typeof(IEnumerable<>).Assembly.Location));
		references.Add(MetadataReference.CreateFromFile(Path.Combine(runtimePath, "System.Runtime.dll")));
		references.Add(MetadataReference.CreateFromFile(Path.Combine(runtimePath, "System.Collections.dll")));
		references.Add(MetadataReference.CreateFromFile(Path.Combine(runtimePath, "System.Linq.dll")));
		references.Add(MetadataReference.CreateFromFile(Path.Combine(runtimePath, "System.Console.dll")));
		references.Add(MetadataReference.CreateFromFile(Path.Combine(runtimePath, "System.Drawing.dll")));
		references.Add(MetadataReference.CreateFromFile(Path.Combine(runtimePath, "System.Drawing.Primitives.dll")));
		references.Add(MetadataReference.CreateFromFile(Path.Combine(runtimePath, "System.Numerics.dll")));
		references.Add(MetadataReference.CreateFromFile(Path.Combine(runtimePath, "System.Numerics.Vectors.dll")));
		references.Add(MetadataReference.CreateFromFile(Path.Combine(runtimePath, "netstandard.dll")));

		references.Add(MetadataReference.CreateFromFile(Assembly.GetExecutingAssembly().Location));

		return references;
	}

	/// <summary>
	/// Represents the result of a C# compilation operation.
	/// </summary>
	public class CompilationResult
	{
		/// <summary>
		/// Gets or sets whether the compilation was successful.
		/// </summary>
		public bool Success { get; set; }

		/// <summary>
		/// Gets or sets the list of compilation errors, if any.
		/// </summary>
		public List<string> Errors { get; set; } = new();

		/// <summary>
		/// Gets or sets the list of compilation warnings, if any.
		/// </summary>
		public List<string> Warnings { get; set; } = new();

		/// <summary>
		/// Gets or sets the compiled assembly, if compilation was successful.
		/// </summary>
		public Assembly? Assembly { get; set; }

		/// <summary>
		/// Gets or sets the assembly load context used for loading the compiled assembly.
		/// This can be used to unload the assembly later.
		/// </summary>
		public AssemblyLoadContext? LoadContext { get; set; }

		/// <summary>
		/// Gets or sets the source file path, if compiled from a file.
		/// </summary>
		public string? SourceFilePath { get; set; }

		/// <summary>
		/// Finds and invokes a static method with the specified name in the compiled assembly.
		/// </summary>
		/// <param name="typeName">The fully qualified type name.</param>
		/// <param name="methodName">The method name to invoke.</param>
		/// <param name="parameters">Optional parameters to pass to the method.</param>
		/// <returns>The result of the method invocation.</returns>
		public object? InvokeMethod(string typeName, string methodName, params object?[]? parameters)
		{
			if (!Success || Assembly == null)
			{
				throw new InvalidOperationException("Cannot invoke method on failed compilation.");
			}

			var type = Assembly.GetType(typeName);
			if (type == null)
			{
				throw new InvalidOperationException($"Type '{typeName}' not found in compiled assembly.");
			}

			var method = type.GetMethod(methodName, BindingFlags.Public | BindingFlags.Static);
			if (method == null)
			{
				throw new InvalidOperationException($"Method '{methodName}' not found in type '{typeName}'.");
			}

			return method.Invoke(null, parameters);
		}

		/// <summary>
		/// Creates an instance of a type from the compiled assembly.
		/// </summary>
		/// <param name="typeName">The fully qualified type name.</param>
		/// <param name="constructorArgs">Arguments to pass to the constructor.</param>
		/// <returns>An instance of the specified type.</returns>
		public object? CreateInstance(string typeName, params object?[]? constructorArgs)
		{
			if (!Success || Assembly == null)
			{
				throw new InvalidOperationException("Cannot create instance from failed compilation.");
			}

            var type = Assembly.GetType(typeName);
			if (type == null)
			{
				throw new InvalidOperationException($"Type '{typeName}' not found in compiled assembly.");
			}

			return Activator.CreateInstance(type, constructorArgs);
		}

		/// <summary>
		/// Gets all types defined in the compiled assembly.
		/// </summary>
		/// <returns>Array of types in the assembly.</returns>
		public Type[] GetTypes()
		{
			if (!Success || Assembly == null)
			{
				throw new InvalidOperationException("Cannot get types from failed compilation.");
			}

			return Assembly.GetTypes();
		}

		/// <summary>
		/// Finds types in the assembly that implement or inherit from a specific type.
		/// </summary>
		/// <typeparam name="T">The base type or interface to search for.</typeparam>
		/// <returns>Array of matching types.</returns>
		public Type[] GetTypesImplementing<T>()
		{
			if (!Success || Assembly == null)
			{
				throw new InvalidOperationException("Cannot get types from failed compilation.");
			}

			return Assembly.GetTypes()
				.Where(t => typeof(T).IsAssignableFrom(t) && !t.IsAbstract && !t.IsInterface)
				.ToArray();
		}

		/// <summary>
		/// Unloads the assembly and its load context to free memory.
		/// </summary>
		public void Unload()
		{
			LoadContext?.Unload();
		}
	}
}
