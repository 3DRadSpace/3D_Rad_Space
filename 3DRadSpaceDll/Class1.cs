using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using System.IO;
namespace _3DRadSpaceDll
{
    /// <summary>
    /// Constants and functions used by 3DRadSpace
    /// </summary>
    public class _3DRadSpaceGame
    {
        public const int MAX_OBJECTS = 300;
        public const int MAX_SCRIPTS = 100;
        /// <summary>
        /// Permamently disables an object without losing it's data.
        /// </summary>
        /// <param name="obj">Object</param>
        public static void ObjectDestroy(ref string obj)
        {
            string oldobj = obj;
            obj = null;
            obj = "DESTROYED_OBJECT " + oldobj;
        }
    }
    public class ScriptInterpeter
    {
        public static string[] Scripts = new string[_3DRadSpaceGame.MAX_SCRIPTS];
        /// <summary>
        /// Checks if a script has a error in it's code.
        /// </summary>
        /// <param name="script">The script file.</param>
        public static void Debug(string script)
        {

        }
        /// <summary>
        /// Executes a script.
        /// </summary>
        /// <param name="script">The script file.</param>
        public static bool Load(string script)
        {
            for(int i =0; i < _3DRadSpaceGame.MAX_SCRIPTS ; i++)
            {
                if(string.IsNullOrEmpty(Scripts[i]) == true)
                {
                    Scripts[i] = script;
                    return true ;
                }
            }
            return false;
        }
        public static void Run(string script)
        {

        }
    }
    /// <summary>
    /// 3DRadSpace Camera object class. This class is entirely static.
    /// </summary>
    public class Camera
    {
        /// <summary>
        /// Camera object drawing update logic functoin.
        /// </summary>
        /// <param name="Object">Camera object as a string.</param>
        /// <param name="view">view Matrix.</param>
        /// <param name="projection">projection Matrix.</param>
        public static void Update(string Object,ref Matrix view,ref Matrix projection)
        {
            if (Object.Split(' ')[2] == "True")
            {
                projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45), 800f / 480f, 0.1f, 500f);
                view = Matrix.CreateLookAt(new Vector3(0, 0, 0), new Vector3(0, 0, 0), Vector3.Up);
            }
        }
        /// <summary>
        /// Resets a camera to the settings that are given in the editor.
        /// </summary>
        /// <param name="Object">Camera object as a string</param>
        public static void DefaultSettings(ref string Object)
        {
            Object = "Camera Camera True 0 0 0 0 0 0 75 True";
        }
        /// <summary>
        /// Disables the update logic of this object type.
        /// </summary>
        /// <param name="obj">object</param>
        public static void Disable(ref string obj)
        {
            string[] newdata = obj.Split(' ');
            newdata[2] = "False";
            obj = "";
            for(int i =0; i < newdata.Length; i++)
            {
                obj += newdata[i] + " ";
            }
        }
        /// <summary>
        /// Enables/Reenables update logic of this object.
        /// </summary>
        /// <param name="obj">object.</param>
        public static void Enable(ref string obj)
        {
            string[] newdata = obj.Split(' ');
            newdata[2] = "True";
            obj = "";
            for (int i = 0; i < newdata.Length; i++)
            {
                obj += newdata[i] + " ";
            }
        }
    }
    /// <summary>
    /// 3DRadSpace Script object Class. This class is entirely static.
    /// </summary>
    public class Script
    {
        public static void Initialise(string obj)
        {
            string scriptfile = "";
            for(int i=3; i < obj.Length; i++)
            {
                scriptfile += obj.Split(' ')[i];
            }
            string scriptdata = File.ReadAllText(scriptfile);
            ScriptInterpeter.Debug(scriptdata);
            ScriptInterpeter.Load(scriptdata);
        }
        public static void Update(string obj)
        {
            if (obj.Split(' ')[2] == "True")
            {
                for (int i = 0; i < _3DRadSpaceGame.MAX_SCRIPTS; i++)
                {
                    if (ScriptInterpeter.Scripts[i] != null)
                    {
                        ScriptInterpeter.Run(ScriptInterpeter.Scripts[i]);
                    }
                }
            }
        }
        public static void Disable(ref string obj)
        {
            string[] newdata = obj.Split(' ');
            newdata[2] = "False";
            obj = "";
            for (int i = 0; i < newdata.Length; i++)
            {
                obj += newdata[i] + " ";
            }
        }
        /// <summary>
        /// Enables/Reenables update logic of this object.
        /// </summary>
        /// <param name="obj">object.</param>
        public static void Enable(ref string obj)
        {
            string[] newdata = obj.Split(' ');
            newdata[2] = "True";
            obj = "";
            for (int i = 0; i < newdata.Length; i++)
            {
                obj += newdata[i] + " ";
            }
        }
    }
    /// <summary>
    /// 3DRadSpace Sprite class. Needs to be initialised firstly (isn't entirely static)
    /// </summary>
    public class Sprite
    {
        public Texture2D sprite;
        public SpriteEffects effects;
        /// <summary>
        /// Loads the sprite image (Texture2D) used for this class.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="contentManager"></param>
        /// <returns></returns>
        public void Initialise(string obj,ContentManager contentManager)
        {
            string asset = "";
            for(int i=10; i < obj.Split(' ').Length; i++)
            {
                asset += obj.Split(' ')[i];
            }
            sprite = contentManager.Load<Texture2D>(asset);
        }
        /// <summary>
        /// Draws the object.
        /// </summary>
        /// <param name="obj">object data</param>
        /// <param name="batch">SpriteBatch used for drawing.</param>
        public void Draw(string obj, SpriteBatch batch)
        {
            if (obj.Split(' ')[2] == "True")
            {
                batch.Draw(sprite, new Vector2(0, 0), new Rectangle(0, 0, 0, 0), Color.White,0,Vector2.Zero,1,effects,0);
            }
        }
        /// <summary>
        /// Disables update logic of this object.
        /// </summary>
        /// <param name="obj">object.</param>
        public static void Disable(ref string obj)
        {
            string[] newdata = obj.Split(' ');
            newdata[2] = "False";
            obj = "";
            for (int i = 0; i < newdata.Length; i++)
            {
                obj += newdata[i] + " ";
            }
        }
        /// <summary>
        /// Enables/Reenables update logic of this object.
        /// </summary>
        /// <param name="obj">object.</param>
        public static void Enable(ref string obj)
        {
            string[] newdata = obj.Split(' ');
            newdata[2] = "True";
            obj = "";
            for (int i = 0; i < newdata.Length; i++)
            {
                obj += newdata[i] + " ";
            }
        }
    }
    /// <summary>
    /// TextPrint class. 
    /// </summary>
    public class TextPrint
    {
        SpriteFont font;
        public void Initialise(ContentManager manager,string fontloc)
        {
            font = manager.Load<SpriteFont>(fontloc);
        }
        public void Draw(SpriteBatch spriteBatch, SpriteFont spriteFont)
        {
            spriteBatch.DrawString(spriteFont, "", new Vector2(0,0),new Color(0,0,0));
        }
    }
}

