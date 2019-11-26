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
                            Camera c = new Camera(Obj[1], Convert.ToBoolean(Obj[2]), new Vector3(Convert.ToSingle(Obj[3]), Convert.ToSingle(Obj[4]), Convert.ToSingle(Obj[5])),
                                new Vector3(Convert.ToSingle(Obj[6]), Convert.ToSingle(Obj[7]), Convert.ToSingle(Obj[8])),
                                new Vector3(Convert.ToSingle(Obj[9]), Convert.ToSingle(Obj[10]), Convert.ToSingle(Obj[11])),
                                Convert.ToSingle(Obj[12]), Convert.ToSingle(Obj[13]), Convert.ToSingle(Obj[14]));
                            int capacity = Convert.ToInt32(Obj[15]);
                            if (capacity > 0)
                            {
                                c.Behiavours = new List<ObjectBehiavour>(capacity);
                                for (int j = 0; j < capacity; j++)
                                {
                                    c.Behiavours.Add(new ObjectBehiavour(Convert.ToInt32(Obj[16 + j]), Convert.ToInt32(Obj[17 + (j*2)])));
                                }
                            }
                            else c.Behiavours = null;
                            a = c;
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
                    case "skycolor":
                        {
                            a = new SkyColor(Obj[1], Convert.ToBoolean(Obj[2]), new Color(
                                Convert.ToByte(Obj[3]),
                                Convert.ToByte(Obj[4]),
                                Convert.ToByte(Obj[5])
                                ));
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
            string[] ToBeSaved = new string[Game.GameObjects.Count+1];
            ToBeSaved[0] = ((int)type).ToString();
            for(int i =0; i < Game.GameObjects.Count;i++)
            {
                int j = i + 1;
                if(Game.GameObjects[i] is Camera c)
                {
                    ToBeSaved[j] = "camera " + c.Name + " " + c.Enabled + " " + Vector2String(c.Position) + " " + Vector2String(c.Rotation) +
                        " " + Vector2String(c.CameraRotation) + " " + c.FOV + " " + c.MinDrawDist + " " + c.MaxDrawDist + " ";
                    if (c.Behiavours != null)
                    {
                        ToBeSaved[j] += c.Behiavours.Count + " ";
                        for (int k = 0; k < c.Behiavours.Count; k++)
                        {
                            ToBeSaved[j] += c.Behiavours[k].ObjectID + " " + c.Behiavours[k].BehiavourID + " ";
                        }
                    }
                    else ToBeSaved[j] += '0';
                }
                if(Game.GameObjects[i] is Script s)
                {
                    ToBeSaved[j] = "script " + s.Name + " " + s.Enabled + " " + s.ClassName + " " + s.Path;
                }
                if(Game.GameObjects[i] is SkyColor sky)
                {
                    ToBeSaved[j] += "skycolor " + sky.Name + " " + sky.Enabled + " " + sky.Color.R + " " + sky.Color.G + " " + sky.Color.B;
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
