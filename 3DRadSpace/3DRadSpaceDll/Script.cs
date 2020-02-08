using System;
using System.Reflection;
using System.IO;
using System.Diagnostics;
using System.CodeDom.Compiler;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// C# Script class.
    /// </summary>
    public class Script : GameObject
    {
        /// <summary>
        /// Compiled CLR assembly
        /// </summary>
        private Assembly _assembly;
        private MethodInfo _start, _run, _end,_draw;
        /// <summary>
        /// Instance of the user-scripted class.
        /// </summary>
        private object _script_object;
        /// <summary>
        /// Checks if compilation succeded.
        /// </summary>
        public bool CompilationStatus { get; private set; }
        /// <summary>
        /// Time for compilation.
        /// </summary>
        public TimeSpan CompilationTime { get; private set; }
        /// <summary>
        /// Path to source code to be compiled and run.
        /// </summary>
        public string Path { get; set; }
        /// <summary>
        /// Script entry class.
        /// </summary>
        public string ClassName { get; set; }
        /// <summary>
        /// Script object main constructor.
        /// </summary>
        /// <param name="name">Object name</param>
        /// <param name="enabled">Checks if scripts will be run</param>
        /// <param name="scriptpath">Path to the file that will be compiled.</param>
        /// <param name="ClassN">Class name.</param>
        public Script(string name, bool enabled, string scriptpath,string ClassN)
        {
            Name = name;
            Enabled = enabled;
            Path = scriptpath;
            ClassName = ClassN;
        }
        /// <summary>
        /// Compiles code in order to make it usable.
        /// </summary>
        public bool Compile(bool ShowErrors)
        {
            File.Delete(@"ScriptCompilationErrors.log");
            //Create a benchmark, to report how much time did the compilation require.
            Stopwatch benchmark = Stopwatch.StartNew();
            //Firstly, check for invalid inputs.
            if (ClassName == null) throw new ArgumentNullException("ClassName", "There's no main class set up.");
            if (!File.Exists(Path)) throw new FileNotFoundException("Script source file doesn't exist.");
            //Assemblies to import.
            CompilerParameters parameters = new CompilerParameters(
                new[] { "3DRadSpaceDll.dll",
                "Monogame.Framework.Dll",
                "mscorlib.dll",
                "System.dll",
                "netstandard.dll",
                "System.Collections.dll",
                "System.Windows.Forms.dll" } )
            {
                MainClass = ClassName,
                GenerateInMemory = true,
                GenerateExecutable = false,
            };
            //Start compiling the code...
            CodeDomProvider Compiler = CodeDomProvider.CreateProvider("CSharp");
            
            CompilerResults results = Compiler.CompileAssemblyFromFile(parameters,System.IO.Path.GetFullPath(Path)); //Not using GetFullPath creates problems... Are you fcking kidding me?
            //If there are errors...
            if (results.Errors.Count > 0)
            {
                foreach (CompilerError error in results.Errors)
                {
                    File.AppendAllText(@"ScriptCompilationErrors.log", error.ErrorNumber + ".)"+_errorType(error.IsWarning)+":" + error.ErrorText + " at line " + error.Line + " column " + error.Column + " \r\n");
                }
                if(ShowErrors)Process.Start(@"ScriptCompilationErrors.log");
                //Stop the benchmark and report.
                benchmark.Stop();
                CompilationTime = benchmark.Elapsed;
                Compiler.Dispose();
                return false;
            }
            else
            {
                //If compilation succeded, save the compiled assembly.
                _assembly = results.CompiledAssembly;
                //Stop the benchmark and report.
                benchmark.Stop();
                CompilationStatus = true;
                CompilationTime = benchmark.Elapsed;
                Compiler.Dispose();
                return true;
            }
        }
        private string _errorType(bool IsWarning)
        {
            if (IsWarning == true) return "Warning";
            else return "Error";
        }
        /// <summary>
        /// Initiailze the object by compiling the linked source.
        /// </summary>
        /// <param name="content">Content manager. Not used.</param>
        public override void Load(ContentManager content)
        {
            CompilationStatus = Compile(false);
            if (CompilationStatus == true)
            {
                Type s = _assembly.GetType(ClassName);
                _script_object = _assembly.CreateInstance(ClassName); //Create script instance.
                _start = s.GetMethod("Start");
                _run = s.GetMethod("Run");
                _draw = s.GetMethod("Draw");
                _end = s.GetMethod("End");
                Start();
            }
            base.Load(content);
        }
        /// <summary>
        /// Executes [ClassName].Start(), where ClassName is part of the the compiled code.
        /// </summary>
        public void Start()
        {
            _start.Invoke(_script_object, null);
        }
        /// <summary>
        /// Executes [ClassName].Run(), where ClassName is part of the compiled source code.
        /// </summary>
        public void Run(MouseState mouse, KeyboardState keyboard, GameTime time)
        {
            _run.Invoke(_script_object, new object[] { mouse, keyboard, time });
        }
        /// <summary>
        /// Executes [ClassName].End(), where ClassName is part of the compiled source.
        /// </summary>
        public void End()
        {
            _end.Invoke(_script_object, null);
        }
        /// <summary>
        /// Runs the script code.
        /// </summary>
        /// <param name="mouse">Used by the user if the case.</param>
        /// <param name="keyboard">Used by the user if the case.</param>
        /// <param name="time">Used by the user if the case.</param>
        public override void Update(MouseState mouse, KeyboardState keyboard, GameTime time)
        {
            Run(mouse,keyboard,time);
            base.Update(mouse, keyboard, time);
        }
        /// <summary>
        /// Runs the script code dedicated to drawing.
        /// </summary>
        /// <param name="spriteBatch">Used by the user if the case.</param>
        /// <param name="view">User by the user if the case again.</param>
        /// <param name="projection">User by the user, if the case...</param>
        public override void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            _draw.Invoke(_script_object, new object[] { spriteBatch, view, projection });
            base.Draw(spriteBatch, view, projection);
        }
    }
}
