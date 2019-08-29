using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Project class for reading and saving projects.
    /// </summary>
    public static class Project
    {
        /// <summary>
        /// Type of the project to open.
        /// </summary>
        public static ProjectType type;
        /// <summary>
        /// Opens a project
        /// </summary>
        /// <param name="filename">File to open</param>
        /// <returns>Returns the objects.</returns>
        public static List<object> Open(string filename)
        {
            List<object> result = new List<object>();
            string[] Data = File.ReadAllLines(filename); //Read the file
            type = (ProjectType)Convert.ToInt32(Data[0]);
            for (int i =1; i < Data.Length;i++) //Loop each line
            {
                //Split the current line
                string[] Obj = Data[i].Split(' ');
                object a; //Object to be added.
                switch(Obj[0]) //Identify the current object.
                {
                    case "camera":
                        {
                            a = new Camera(Obj[1], Convert.ToBoolean(Obj[2]), new Vector3(Convert.ToSingle(Obj[3]), Convert.ToSingle(Obj[4]), Convert.ToSingle(Obj[5])),
                                new Vector3(Convert.ToSingle(Obj[6]), Convert.ToSingle(Obj[7]), Convert.ToSingle(Obj[8])),
                                new Vector3(Convert.ToSingle(Obj[9]), Convert.ToSingle(Obj[10]), Convert.ToSingle(Obj[11])),
                                Convert.ToSingle(Obj[12]), Convert.ToSingle(Obj[13]), Convert.ToSingle(Obj[14]));
                            break;
                        }
                    case "script":
                        {
                            string path = "";
                            for(int j =4;j < Obj.Length;j++)
                            {
                                path += Obj[i];
                            }
                            a = new Script(Obj[1], Convert.ToBoolean(Obj[2]), path, Obj[3]);
                            break;
                        }
                    default:
                        {
                            throw new FormatException("Unknown object found. Line :" + i + " Identifier:" + Obj[0]);
                        }
                }
                result.Add(a);
            }
            return result;
        }
        /// <summary>
        /// Saves a 3DRSP project
        /// </summary>
        /// <param name="filename">File path</param>
        public static void Save(string filename)
        {
            string[] ToBeSaved = new string[Game.GameObjects.Count];
            ToBeSaved[0] = type.ToString();
            for(int i =1; i < Game.GameObjects.Count;i++)
            {
                if(Game.GameObjects[i] is Camera c)
                {
                    ToBeSaved[i] = "camera " + c.Name + " " + c.Enabled + " " + Vector2String(c.Position) + " " + Vector2String(c.CameraTarget) +
                        " " + c.CameraRotation + " " + c.FOV + " " + c.MinDrawDist + " " + c.MaxDrawDist;
                }
                if(Game.GameObjects[i] is Script s)
                {
                    ToBeSaved[i] = "script " + s.Name + " " + s.Enabled + " " + s.ClassName + " " + s.Path;
                }
            }
            File.WriteAllLines(filename, ToBeSaved);
        }
        /// <summary>
        /// Converts a vector to a string in the format needed for 3DRSP projects
        /// </summary>
        /// <param name="pos">3D Vector to be converted</param>
        /// <returns>The needed string</returns>
        public static string Vector2String(Vector3 pos)
        {
            return pos.X + " " + pos.Y + " " + pos.Z;
        }
        /// <summary>
        /// Converts a vector to a string in the format needed for 3DRSP projects
        /// </summary>
        /// <param name="pos">2D Vector to be converted</param>
        /// <returns>The needed string</returns>
        public static string Vector2String(Vector2 pos)
        {
            return pos.X + " " + pos.Y;
        }
    }
    /// <summary>
    /// Project types for the editor.
    /// </summary>
    public enum ProjectType
    {
        /// <summary>
        /// Strictly 2D.
        /// </summary>
        TwoDimensional = 0,
        /// <summary>
        /// 3D
        /// </summary>
        ThreeDimensional = 1,
        /// <summary>
        /// Code only
        /// </summary>
        ScriptOnly = 2
    }
}
