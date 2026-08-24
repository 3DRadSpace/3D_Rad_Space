using System.Runtime.InteropServices;
using Engine3DRadSpace.Logging;
using Engine3DRadSpace.Objects;
using Engine3DRadSpace.Scripting;

namespace Engine3DRadSpace.Internal;

/// <summary>
/// Manages compiled scripts and provides entry points for the native C++ host.
/// </summary>
public static class ScriptManager
{
	private static readonly Dictionary<int, ScriptInstance> _loadedScripts = new();
	private static int _nextScriptId = 1;

	/// <summary>
	/// Compiles a C# script from a file and returns a script handle.
	/// </summary>
	/// <param name="scriptPath">Path to the .cs script file.</param>
	/// <param name="className">Fully qualified class name to instantiate.</param>
	/// <returns>Script ID, or -1 on failure.</returns>
	[UnmanagedCallersOnly]
	public static int LoadScript(IntPtr scriptPath, IntPtr className, IntPtr ownerObject)
	{
		try
		{
			string? path = Marshal.PtrToStringUTF8(scriptPath);
			string? classNameStr = Marshal.PtrToStringUTF8(className);

			if (string.IsNullOrEmpty(path) || string.IsNullOrEmpty(classNameStr))
			{
				PrintWarning("Invalid script path or class name");
				return -1;
			}

			var result = CsCompiler.CompileFromFile(path);

			if (!result.Success)
			{
				string errors = string.Join("\n", result.Errors);
                PrintWarning($"Script compilation failed:\n{errors}");
				return -1;
			}

			// Try to create an instance
			object? instance;
			try
			{
				instance = result.CreateInstance(classNameStr);
			}
			catch (Exception ex)
			{
                PrintWarning($"Failed to create instance: {ex.Message}");
				result.Unload();
				return -1;
			}

			if (instance == null)
			{
                PrintWarning("Failed to create script instance");
				result.Unload();
				return -1;
			}

			int scriptId = _nextScriptId++;
			_loadedScripts[scriptId] = new ScriptInstance
			{
				Id = scriptId,
				Instance = instance,
				CompilationResult = result,
				ScriptInterface = instance as Script
			};

			// Call Start if the script implements IScript
			if (_loadedScripts[scriptId].ScriptInterface != null)
			{
				(_loadedScripts[scriptId].ScriptInterface as Script).Object = new InstIObject(ownerObject);
                _loadedScripts[scriptId].ScriptInterface!.Start();
			}

			return scriptId;
		}
		catch (Exception ex)
		{
            PrintWarning($"Exception in LoadScript: {ex.Message}");
			return -1;
		}
	}

	/// <summary>
	/// Updates a loaded script.
	/// </summary>
	/// <param name="scriptId">ID of the script to update.</param>
	/// <returns>1 on success, 0 on failure.</returns>
	[UnmanagedCallersOnly]
	public static byte UpdateScript(int scriptId)
	{
		try
		{
			if (!_loadedScripts.TryGetValue(scriptId, out var scriptInstance))
				return 0;

			scriptInstance.ScriptInterface?.Update();
			return 1;
		}
		catch(Exception ex)
		{
            PrintWarning($"Exception in UpdateScript: {ex.Message}");
			return 0;
		}
	}

	/// <summary>
	/// Unloads a script and frees its resources.
	/// </summary>
	/// <param name="scriptId">ID of the script to unload.</param>
	[UnmanagedCallersOnly]
	public static void UnloadScript(int scriptId)
	{
		try
		{
			if (!_loadedScripts.TryGetValue(scriptId, out var scriptInstance))
				return;

			scriptInstance.ScriptInterface?.End();
			scriptInstance.CompilationResult.Unload();
			_loadedScripts.Remove(scriptId);
		}
		catch
		{
			//If somehow failed, just directly remove anyway, without cleanup.
            _loadedScripts.Remove(scriptId);
        }
	}

	/// <summary>
	/// Invokes a method on a loaded script.
	/// </summary>
	/// <param name="scriptId">ID of the script.</param>
	/// <param name="methodName">Name of the method to invoke.</param>
	/// <returns>1 on success, 0 on failure.</returns>
	[UnmanagedCallersOnly]
	public static byte InvokeScriptMethod(int scriptId, IntPtr methodName)
	{
		try
		{
			if (!_loadedScripts.TryGetValue(scriptId, out var scriptInstance))
				return 0;

			string? method = Marshal.PtrToStringUTF8(methodName);
			if (string.IsNullOrEmpty(method))
				return 0;

			var type = scriptInstance.Instance.GetType();
			var methodInfo = type.GetMethod(method);
			
			if (methodInfo == null)
				return 0;

			methodInfo.Invoke(scriptInstance.Instance, null);
			return 1;
		}
		catch
		{
			return 0;
		}
	}

	/// <summary>
	/// Sets a warning message in the engine's logging system.
	/// </summary>
	private static void PrintWarning(string message)
	{
		var warning = new Warning(message, 0, 1, IntPtr.Zero);
		Warning.PrintWarning(ref warning);
	}

	private class ScriptInstance
	{
		public int Id { get; set; }
		public object Instance { get; set; } = null!;
		public CsCompiler.CompilationResult CompilationResult { get; set; } = null!;
		public IScript? ScriptInterface { get; set; }
	}

	// Additional helper methods for managed code

	/// <summary>
	/// Compiles and loads a script from source code (for use from managed code).
	/// </summary>
	public static int LoadScriptFromSource(string source, string className)
	{
		var result = CsCompiler.Compile(source);

		if (!result.Success)
		{
			throw new InvalidOperationException($"Compilation failed: {string.Join("\n", result.Errors)}");
		}

		var instance = result.CreateInstance(className);
		if (instance == null)
		{
			result.Unload();
			throw new InvalidOperationException("Failed to create script instance");
		}

		int scriptId = _nextScriptId++;
		_loadedScripts[scriptId] = new ScriptInstance
		{
			Id = scriptId,
			Instance = instance,
			CompilationResult = result,
			ScriptInterface = instance as IScript
		};

		_loadedScripts[scriptId].ScriptInterface?.Start();

		return scriptId;
	}

    [UnmanagedCallersOnly]
    public static byte CompileScript(IntPtr scriptPath, IntPtr className)
    {
        try
        {
            string? path = Marshal.PtrToStringUTF8(scriptPath);
            string? classNameStr = Marshal.PtrToStringUTF8(className);

            if (string.IsNullOrEmpty(path) || string.IsNullOrEmpty(classNameStr))
            {
                PrintWarning("Invalid script path or class name");
                return 0;
            }

			var result = CsCompiler.CompileFromFile(path);

			if (!result.Success)
			{
				string errors = string.Join("\n", result.Errors);
				PrintWarning($"Script compilation failed:\n{errors}");
				result.Unload();
				return 0;
			}

			// Try to create an instance
			object? instance;
			try
			{
				instance = result.CreateInstance(classNameStr);
			}
			catch (Exception ex)
			{
				PrintWarning($"Failed to create instance: {ex.Message}");
				result.Unload();
				return 0;
			}

			if (instance == null)
			{
				PrintWarning("Failed to create script instance");
				result.Unload();
				return 0;
			}

			result.Unload();
		}
		catch (Exception ex)
		{
			PrintWarning($"Exception in CompileScript: {ex.Message}");
			return 0;
		}

		return 1;
    }

    /// <summary>
    /// Gets the script instance by ID (for use from managed code).
    /// </summary>
    public static object? GetScriptInstance(int scriptId)
	{
		return _loadedScripts.TryGetValue(scriptId, out var instance) ? instance.Instance : null;
	}
}
