using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using System.IO;
using System.CodeDom.Compiler;
using System.Diagnostics;
using System.Reflection;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Constants and functions used by 3DRadSpace
    /// </summary>
    public class _3DRadSpaceGame
    {
        /// <summary>
        /// Defines maximum number of objects. Only used in 3DRadSpace Player and in 3DRadSpace Editor.
        /// </summary>
        public const int MAX_OBJECTS = 300;
        /// <summary>
        /// Defines maximum number of scripts. Only used in 3DRadSpace Player and in 3DRadSpace Editor.
        /// </summary>
        public const int MAX_SCRIPTS = 100;
        /// <summary>
        /// Maximum variables in the project.
        /// </summary>
        public const int MAX_VARIABLES = 200;
        /// <summary>
        /// Converts a Vector3 to a Vector2.
        /// </summary>
        /// <param name="vec">Vector3 to be converted.</param>
        /// <returns></returns>
        public static Vector2 Vector3ToVector2(Vector3 vec) => new Vector2(vec.X, vec.Y);
    }
    /// <summary>
    /// 3DRadSpace Script Interpeter class
    /// </summary>
    public class ScriptInterpeter
    {
        /// <summary>
        /// Compiled scripts.
        /// </summary>
        public static Assembly[] scripts = new Assembly[_3DRadSpaceGame.MAX_SCRIPTS];
        /// <summary>
        /// Checks if a script has a error in it's code.
        /// </summary>
        /// <param name="script">The script file.</param>
        public static int Debug(string script)
        {
            int i = 0;
            File.Delete(@"compile_errors.txt");
            CodeDomProvider codeDomProvider = CodeDomProvider.CreateProvider("CSharp");
            CompilerParameters parameters = new CompilerParameters();
            if (codeDomProvider.Supports(GeneratorSupport.EntryPointMethod)) parameters.MainClass = "Script";
            parameters.GenerateExecutable = false;
            parameters.GenerateInMemory = true;
            parameters.ReferencedAssemblies.Add("3DRadSpaceDll.dll");
            parameters.ReferencedAssemblies.Add("System.dll");
            parameters.ReferencedAssemblies.Add("System.Windows.Forms.dll");
            parameters.ReferencedAssemblies.Add("System.Console.dll");
            parameters.ReferencedAssemblies.Add("mscorlib.dll");
            parameters.ReferencedAssemblies.Add("netstandard.dll");
            CompilerResults results = codeDomProvider.CompileAssemblyFromFile(parameters, script);
            CompilerErrorCollection errors = results.Errors;
            for (int j = 0; j < errors.Count; j++)
            {
                File.AppendAllText(@"compile_errors.txt", errors[i].ErrorText + " Line:" + errors[i].Line + " Is warning:" + errors[i].IsWarning+" \r\n");
            }
            if (errors.HasErrors == false)
            {
                Assembly compiledcode = results.CompiledAssembly;
                for (i=0; i < _3DRadSpaceGame.MAX_SCRIPTS; i++)
                {
                    if (scripts[i] == null)
                    {
                        scripts[i] = compiledcode;
                        break;
                    }
                }
            }
            else
            {
                Process.Start(@"compile_errors.txt");
                throw new ScriptError(File.ReadAllText(@"compile_errors.txt"));
            }
            return i;
    }
        /// <summary>
        /// Starts running a script.
        /// </summary>
        /// <param name="ScriptID">Script's unique unsigned number identifier.</param>
        public static void Run(int ScriptID)
        {
            Type type = scripts[ScriptID].GetType("Script");
            MethodInfo Main = type.GetMethod("Main");
            Main.Invoke(null, null);
        }
    }
    
    /// <summary>
    /// 3DRadSpace Base Object Class
    /// </summary>
    public class GameObject
    {
        /// <summary>
        /// The object's name.
        /// </summary>
        public string name = "";
        /// <summary>
        /// If true the object will update each time when Update() or Draw() is called.
        /// </summary>
        public bool IsActive = false;
        /// <summary>
        /// Position of the object.
        /// </summary>
        public Vector3 Pos = Vector3.Zero;
        /// <summary>
        /// Rotation In Quaternion of the object.
        /// </summary>
        public Quaternion Rotation = Quaternion.Identity;
        /// <summary>
        /// Resource file.
        /// </summary>
        public string resource = "";
        /// <summary>
        /// Returns a string that represents the current object.
        /// </summary>
        /// <returns>Returns a string that represents the current object.</returns>
        public override string ToString()
        {
            return name + " " + IsActive + " " + Pos.X + " " + Pos.Y + " " + Pos.Z + " " + Rotation.X + " " + Rotation.Y + " " + Rotation.Z + " " + Rotation.W + " " + resource;
        }
        /// <summary>
        /// Disables the object instance from updating.
        /// </summary>
        public void Disable() => IsActive = false;
        /// <summary>
        /// Enables the object, allowing it to update it's properties when Update() or Draw() is called.
        /// </summary>
        public void Enable() => IsActive = true;

    }
    /// <summary>
    /// 3DRadSpace Camera object class.
    /// </summary>
    public class Camera : GameObject
    {
        /// <summary>
        /// Camera look at point.
        /// </summary>
        public Vector3 look_at = new Vector3(0, 0, 0);
        /// <summary>
        /// Camera field of view.
        /// </summary>
        public float FOV = MathHelper.ToRadians(45);
        /// <summary>
        /// Maximum render distance.
        /// </summary>
        public float MaxViewDistance = 500f;
        /// <summary>
        /// Camera object constructor.
        /// </summary>
        /// <param name= "objn">Object name.</param>
        /// <param name= "isactive">Object name.</param>
        /// <param name="pos">Camera position.</param>
        /// <param name="lookat">Camera look at 3D point.</param>
        /// <param name="FieldOfView">Field Of View in Radians</param>
        /// <param name="MaxRenderDistance">Maximum render distance</param>
        public Camera(string objn, bool isactive, Vector3 pos,Vector3 lookat,float FieldOfView = 45f * 3.1415926f / 180f, float MaxRenderDistance = 500f)
        {
            name = objn;
            IsActive = isactive;
            Pos = pos;
            look_at = lookat;
            FOV = FieldOfView;
            MaxViewDistance = MaxRenderDistance;
        }
        /// <summary>
        /// Camera object drawing update logic functoin.
        /// </summary>
        /// <param name="view">affected view Matrix.</param>
        /// <param name="projection">affected projection Matrix.</param>
        public void Update(ref Matrix view,ref Matrix projection)
        {
            if (IsActive == true)
            {
                projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45), 800f / 480f, 0.1f, 500f);
                view = Matrix.CreateLookAt(Pos, look_at, Vector3.Up);
            }
        }

    }
    /// <summary>
    /// 3DRadSpace Script object Class. This class is entirely static.
    /// </summary>
    public class Script : GameObject
    {
        /// <summary>
        /// Path to the script.
        /// </summary>
        public string path;
        /// <summary>
        /// Loaded script file.
        /// </summary>
        int ScriptID = Int32.MaxValue;
        /// <summary>
        /// Loads and tests a script for errors then runs it.
        /// </summary>
        /// <param name= "objn">Object name.</param>
        /// <param name= "isactive">If the script is executed.</param>
        /// <param name="file">Script file to be loaded.</param>
        public Script(string objn, bool isactive, string file)
        {
            ScriptInterpeter.Debug(file);
        }
        /// <summary>
        /// Updates the script.
        /// </summary>
        public void Update()
        {
            ScriptInterpeter.Run(ScriptID);
        }
    }
    /// <summary>
    /// 3DRadSpace Sprite class. Needs to be initialised firstly (isn't entirely static)
    /// </summary>
    public class Sprite : GameObject
    {
        /// <summary>
        /// Loaded Sprite image.
        /// </summary>
        public Texture2D sprite;
        /// <summary>
        /// Sprite's size.
        /// </summary>
        public Vector2 Scale = new Vector2(1, 1);
        /// <summary>
        /// Sprite effects applied to the sprite.
        /// </summary>
        public SpriteEffects effects;
        /// <summary>
        /// Sprite constructor.
        /// </summary>
        /// <param name= "objn">Object name.</param>
        /// <param name= "isactive">If this sprite will be drawn</param>
        /// <param name="asset">Sprite to be loaded.</param>
        /// <param name="manager">Content manager</param>
        /// <param name="pos">Sprite's location. Z can have any value.</param>
        /// <param name="scale">Sprite's location</param>
        public Sprite(string objn, bool isactive, string asset,ContentManager manager,Vector3 pos, Vector2 scale)
        {
            name = objn;
            IsActive = isactive;
            Pos = pos;
            Scale = scale;
            resource = asset;
        }
        /// <summary>
        /// Draws the object.
        /// </summary>
        /// <param name="batch">SpriteBatch used for drawing.</param>
        public void Draw(SpriteBatch batch)
        {
            if (IsActive == true)
            {
                batch.Draw(sprite, new Rectangle((int)Pos.X, (int)Pos.Y, (int)Scale.X, (int)Scale.Y),new Color(255, 255, 255));
            }
        }
    }
    /// <summary>
    /// TextPrint class. 
    /// </summary>
    public class TextPrint : GameObject
    {
        /// <summary>
        /// Textprint's font.
        /// </summary>
        public SpriteFont font;
        /// <summary>
        /// TextPrint's text
        /// </summary>
        public string Text = "";
        /// <summary>
        /// Text Color.
        /// </summary>
        public Color color;
        /// <summary>
        /// Initialises a new TextPrint Object.
        /// </summary>
        /// <param name= "objn">Object name.</param>
        /// <param name= "isactive">If the text will be drawn.</param>
        /// <param name="manager">Content manager.</param>
        /// <param name="fontloc">Font file.</param>
        /// <param name="position">Position. Z can be any value.</param>
        /// <param name="text">Text to display.</param>
        /// <param name="colour">Text's colour.</param>
        public TextPrint(string objn, bool isactive, ContentManager manager, string fontloc, Vector3 position, string text, Color colour)
        {
            name = objn;
            IsActive = isactive;
            font = manager.Load<SpriteFont>(fontloc);
            Pos = position;
            Text = text;
            color = colour;
        }
        /// <summary>
        /// Initialises a new TextPrint Object.
        /// </summary>
        /// <param name= "objn">Object name.</param>
        /// <param name= "isactive">If the text will be drawn.</param>
        /// <param name="manager">Content manager.</param>
        /// <param name="position">Position. Z can be any value.</param>
        /// <param name="text">Text to display.</param>
        /// <param name="colour">Text's colour.</param>
        public TextPrint(string objn, bool isactive, ContentManager manager, Vector3 position, string text, Color colour)
        {
            name = objn;
            IsActive = isactive;
            font = manager.Load<SpriteFont>("DefaultFont");
            Pos = position;
            Text = text;
            color = colour;
        }
        /// <summary>
        /// Draws the text.
        /// </summary>
        /// <param name="spriteBatch">spritebatch.</param>
        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.DrawString(font,Text, new Vector2(Pos.X,Pos.Y),new Color(0,0,0));
        }
    }

    /// <summary>
    /// 3D Rad Space Script Error Exception
    /// </summary>
    [Serializable]
    public class ScriptError : Exception
    {
        /// <summary>
        /// Intilialises a ScriptError exception that can be thrown.
        /// </summary>
        /// <param name="message">Error message.</param>
        public ScriptError(string message) : base(message) { }
        /// <summary>
        /// Initialises a ScriptError from an other Exception
        /// </summary>
        /// <param name="message">Error message</param>
        /// <param name="inner">Base exception</param>
        public ScriptError(string message, Exception inner) : base(message, inner) { }
        /// <summary>
        /// I don't know what is this supposed to do :/ .
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        protected ScriptError(
          System.Runtime.Serialization.SerializationInfo info,
          System.Runtime.Serialization.StreamingContext context) : base(info, context) { }
    }
    /// <summary>
    /// 3DRadSpace Skinmesh Class.
    /// </summary>
    public class SkinMesh : GameObject
    {
        /// <summary>
        /// Loaded model that is drawn.
        /// </summary>
        public Model model;
        /// <summary>
        /// Skinmesh object constructor
        /// </summary>
        /// <param name="objn">Object Name</param>
        /// <param name="isactive">If the object will be drawn every frame.</param>
        /// <param name="res">Resource file.</param>
        /// <param name="location">Position</param>
        /// <param name="rotation">Rotation Quaternion</param>
        public SkinMesh(string objn, bool isactive, string res, Vector3 location, Vector3 rotation)
        {
            name = objn;
            IsActive = isactive;
            resource = res;
            Pos = location;
            Rotation = Quaternion.CreateFromYawPitchRoll(rotation.Y, rotation.X, rotation.Z);
        }
        /// <summary>
        /// Loads a 3d Model so drawing the model can be done.
        /// </summary>
        /// <param name="manager">Content manager</param>
        public void Initialize(ContentManager manager)
        {
            try
            {
                model = manager.Load<Model>(resource);
            }
            catch
            {
                model = manager.Load<Model>("error");
            }
        }
        /// <summary>
        /// Draws the skinmesh object.
        /// </summary>
        /// <param name="view">View Matrix</param>
        /// <param name="projection">Projection Matrix</param>
        public void Draw(Matrix view,Matrix projection)
        {
            Matrix world = Matrix.CreateTranslation(Pos);
            Matrix rotation = Matrix.CreateFromQuaternion(Rotation);
            foreach (ModelMesh mesh in model.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.World = rotation * world;
                   // effect.EnableDefaultLighting();
                    effect.View = view;
                    effect.Projection = projection;
                    effect.TextureEnabled = true;
                }
                mesh.Draw();
            }
        }
    }
    /// <summary>
    /// SkyColor object.
    /// </summary>
    public class SkyColor : GameObject
    {
        /// <summary>
        /// Colour of the game backround.
        /// </summary>
        public Color Color = Color.Black;
        /// <summary>
        /// SkyColor constructor.
        /// </summary>
        /// <param name="objn">Object Name</param>
        /// <param name="isactive">Is the colour displayed?</param>
        /// <param name="colour">The color that will be used.</param>
        public SkyColor(string objn, bool isactive,Color colour)
        {
            name = objn;
            IsActive = isactive;
            Color = colour;
        }
    }
    /// <summary>
    /// Fog object.
    /// </summary>
    public class Fog : GameObject
    {
        /// <summary>
        /// Start Fog Distance.
        /// </summary>
        public float Start;
        /// <summary>
        /// End Fog Distance.
        /// </summary>
        public float End;
        /// <summary>
        /// Fog object Constructor.
        /// </summary>
        /// <param name="objn">Object Name.</param>
        /// <param name="active">Is active</param>
        /// <param name="color">Colour as Vector3. X = Red, Y = Green, Z = Blue</param>
        /// <param name="start">Start distance</param>
        /// <param name="end">End distance</param>
        public Fog(string objn, bool active, Vector3 color, float start = 250,float end = 500)
        {
            name = objn;
            IsActive = active;
            Pos = color;
            Start = start;
            End = end;
        }
    }
}

