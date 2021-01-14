using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.CodeDom.Compiler;
using Microsoft.CSharp;
using System.Reflection;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// Object allowing C# scripting
    /// </summary>
    public class Script : BaseGameObject
    {
        string Text;
        object scriptInstance;
        MethodInfo _load;
        MethodInfo _update;
        MethodInfo _draw;
        MethodInfo _end;
        /// <summary>
        /// Name of the class that the script will execute.
        /// </summary>
        public string MainClass 
        {
            get 
            {
                return _mainClass;
            }
        }
        string _mainClass;
        /// <summary>
        /// C# Code Provider. 1 global instance used for compilation.
        /// </summary>
        public static CodeDomProvider Compiler = CodeDomProvider.CreateProvider("CSharp");
        /// <summary>
        /// Main Script object constructor.
        /// </summary>
        /// <param name="name">Object name.</param>
        /// <param name="enabled">Checks if the script object will execute the provided script</param>
        /// <param name="mainclass">Entry point class name</param>
        /// <param name="code">Source code provided to the compiler.</param>
        public Script(string name,bool enabled,string mainclass,string code)
        {
            Name = name;
            Enabled = enabled;
            Text = code;
            _mainClass = mainclass;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public bool Compile(out string[] errors)
        {
            string[] Assemblies = { "System.dll", "Monogame.Framework.dll", "Lib3DRadSpace_DX.dll" ,"mscorlib.dll","netstandard.dll", "System.Collections.dll" };
            CompilerParameters parameters = new CompilerParameters(Assemblies)
            {
                MainClass = _mainClass,
                GenerateInMemory = true
            };
            CompilerResults result = Compiler.CompileAssemblyFromSource(parameters, Text);

            if(result.CompiledAssembly == null)
            {
                errors = new string[result.Errors.Count];
                for(int i =0; i < result.Errors.Count;i++)
                {
                    string a = "[ERROR]";
                    if (result.Errors[i].IsWarning) a = "[WARNING]";
                    errors[i] = a + result.Errors[i].ErrorNumber + " " + result.Errors[i].ErrorText + " Line:" + result.Errors[i].Line;
                }
                return false;
            }

            scriptInstance = result.CompiledAssembly.CreateInstance(_mainClass);
            Type scriptType = result.CompiledAssembly.GetType(_mainClass);
            _load = scriptType.GetMethod("Load");
            _update = scriptType.GetMethod("Update");
            _draw = scriptType.GetMethod("Draw");
            _end = scriptType.GetMethod("Unload");

            errors = null;
            Compiler.Dispose();
            return true;
        }
        /// <summary>
        /// Checks the scripts for errors.
        /// </summary>
        /// <param name="errors">Null if there are no errors or warnings.</param>
        /// <returns></returns>
        public bool CompileWithoutAssembly(out string[] errors)
        {
            string[] Assemblies = { "System.dll", "Monogame.Framework.dll", "Lib3DRadSpace_DX.dll", "mscorlib.dll", "netstandard.dll", "System.Collections.dll" };
            CompilerParameters parameters = new CompilerParameters(Assemblies)
            {
                MainClass = _mainClass,
                GenerateInMemory = true,
            };
            CompilerResults result = Compiler.CompileAssemblyFromSource(parameters, Text);

            if (result.Errors.Count > 0)
            {
                errors = new string[result.Errors.Count + 1];
                for (int i = 0; i < result.Errors.Count; i++)
                {
                    string a = "[ERROR]";
                    if (result.Errors[i].IsWarning) a = "[WARNING]";
                    errors[i] = a + result.Errors[i].ErrorNumber + " " + result.Errors[i].ErrorText + " Line:" + result.Errors[i].Line;
                }
                return false;
            }
            errors = null;
            Compiler.Dispose();
            return true;
        }
        /// <summary>
        /// Executes 'MainClass'.Load(ContentManager);
        /// </summary>
        /// <param name="content">ContentManager argument. Used to load models, textures, fonts, etc.</param>
        public override void Load(ContentManager content)
        {
            _load?.Invoke(scriptInstance, new object[] { content });
        }
        /// <summary>
        /// Calls 'MainClass'.Update(input,keyboard,time)
        /// </summary>
        /// <param name="input">Mouse input</param>
        /// <param name="keyboard">Keyboard input</param>
        /// <param name="time">Delta Time.</param>
        public override void Update(ref MouseState input, ref KeyboardState keyboard, GameTime time)
        {
            if(Enabled) _update?.Invoke(scriptInstance, new object[] { input, keyboard, time });
        }
        /// <summary>
        /// Calls 'MainClass'.Draw(time,frustrum,view,projection)
        /// </summary>
        /// <param name="time">Delta Time.</param>
        /// <param name="frustrum">Bounding Frustrum</param>
        /// <param name="view">View Matrix</param>
        /// <param name="projection">Projection Matrix</param>
        public override void Draw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
        {
            if(Enabled) _draw?.Invoke(scriptInstance, new object[] {time,frustrum,view,projection });
        }
        /// <summary>
        /// 
        /// </summary>
        ~Script()
        {
            _end?.Invoke(scriptInstance, null);
        }
    }
}
