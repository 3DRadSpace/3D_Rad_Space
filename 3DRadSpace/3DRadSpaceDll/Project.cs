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
		public static ProjectType type { get; set; }
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
								path += Obj[j]+' ';
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
					case "fog":
						{
							a = new Fog(Obj[0], Convert.ToBoolean(Obj[2]), new Color(
								Convert.ToByte(Obj[3]),
								Convert.ToByte(Obj[4]),
								Convert.ToByte(Obj[5])
								),
								Convert.ToSingle(Obj[6]), Convert.ToSingle(Obj[7]));
							break;
						 }
					case "skinmesh":
						{
							string path = "";
							for(int j = 20;j < Obj.Length;j++)
							{
								path += Obj[j] + ' ';
							}
							a = new Skinmesh(Obj[0], Convert.ToBoolean(Obj[2]), path,
								new Vector3(Convert.ToSingle(Obj[3]),Convert.ToSingle(Obj[4]),Convert.ToSingle(Obj[5]))
								, new Vector3(Convert.ToSingle(Obj[6]),Convert.ToSingle(Obj[7]),Convert.ToSingle(Obj[8]))
								, new Vector3(Convert.ToSingle(Obj[9]),Convert.ToSingle(Obj[10]),Convert.ToSingle(Obj[11])),
								Convert.ToBoolean(Obj[12]),new BoundingBox(
									new Vector3(Convert.ToSingle(Obj[13]),Convert.ToSingle(Obj[14]),Convert.ToSingle(Obj[15]))
									,new Vector3(Convert.ToSingle(Obj[16]),Convert.ToSingle(Obj[17]),Convert.ToSingle(Obj[18])))
									,new BoundingSphere(Vector3.Zero,Convert.ToSingle(Obj[19])));
							break;
						}
					case "sprite":
						{
							string path = "";
							for (int j = 19; j < Obj.Length; j++)
							{
								path += Obj[j] + " ";
							}
							Sprite s = new Sprite(Obj[1], Convert.ToBoolean(Obj[2]), path,
								new Vector2(Convert.ToInt32(Obj[3]), Convert.ToInt32(Obj[4])), new Vector2(Convert.ToInt32(Obj[5]), Convert.ToInt32(Obj[6])),
								new Vector2(Convert.ToInt32(Obj[7]), Convert.ToInt32(Obj[8])), Convert.ToSingle(Obj[9]),
								new Rectangle(Convert.ToInt32(Obj[10]),Convert.ToInt32(Obj[11]),Convert.ToInt32(Obj[12]),Convert.ToInt32(Obj[13]))
								, new Color(Convert.ToByte(Obj[14]), Convert.ToByte(Obj[15]), Convert.ToByte(Obj[16])), (SpriteEffects)Convert.ToInt32(Obj[17]),Convert.ToInt32(Obj[18]));
							if (s.SpriteSheetSection.Value.Width + s.SpriteSheetSection.Value.Height == 0) s.SpriteSheetSection = null;
							a = s;
							break;
						}
					case "textprint":
						{
							string text = "";
							// 0xFE is used as a constant to divide different texts, like the /0 in C char buffers (strings)
							int j = 15;
							for ( ; Obj[j] != "" + (char)0xfe; j++)
							{
								text += Obj[j] + ' ';
							}
							string font = "";
							for (j += 1; j < Obj.Length;j++)
							{
								font += Obj[j]+' ';
							}
							font = font.Remove(font.Length - 1);
							a = new TextPrint(Obj[1], Convert.ToBoolean(Obj[2]), font, text,
								new Vector2(Convert.ToSingle(Obj[3]), Convert.ToSingle(Obj[4])),
								new Vector2(Convert.ToSingle(Obj[5]), Convert.ToSingle(Obj[6])), Convert.ToSingle(Obj[7]),
								new Vector2(Convert.ToSingle(Obj[8]), Convert.ToSingle(Obj[9])),
								new Color(Convert.ToByte(Obj[10]), Convert.ToByte(Obj[11]), Convert.ToByte(Obj[12])),
								(SpriteEffects)(Convert.ToInt32(Obj[13])),Convert.ToInt32(Obj[14]));
							break;
						}
					case "soundeffect":
						{
							string path = "";
							for(int j =7; j < Obj.Length;j++)
							{
								path += Obj[j] + ' ';
							}
							a = new SoundEffect(Obj[1], Convert.ToBoolean(Obj[2]), path, Convert.ToSingle(Obj[3]))
							{
								Pitch = Convert.ToSingle(Obj[4]),
								Pan = Convert.ToSingle(Obj[5]),
								SoundState = (Microsoft.Xna.Framework.Audio.SoundState)Convert.ToInt32(Obj[6])
							};
							break;
						}
					case "exitfade":
						{
							string path = "";
							for (int j = 8; j < Obj.Length; j++)
							{
								path += Obj[j] + ' ';
							}
							a = new ExitFade()
							{
								Name = Obj[1],
								Enabled = Convert.ToBoolean(Obj[2]),
								Fade = new Color(
									Convert.ToByte(Obj[3]), Convert.ToByte(Obj[4]), Convert.ToByte(Obj[5])
								),
								Time = Convert.ToInt32(Obj[6]),
								FadeType = Convert.ToBoolean(Obj[7]),
								ProjectToLoad = path
							};
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
			for (int i = 0; i < Game.GameObjects.Count; i++)
			{
				int j = i + 1;
				if (Game.GameObjects[i] is Camera c)
				{
					ToBeSaved[j] = "camera " + c.Name + ' ' + c.Enabled + ' ' + Vector2String(c.Position) + ' ' + Vector2String(c.Rotation) +
						' ' + Vector2String(c.CameraRotation) + ' ' + c.FOV + ' ' + c.MinDrawDist + ' ' + c.MaxDrawDist + ' ';
					if (c.Behiavours != null)
					{
						ToBeSaved[j] += c.Behiavours.Count + ' ';
						for (int k = 0; k < c.Behiavours.Count; k++)
						{
							ToBeSaved[j] += c.Behiavours[k].ObjectID + ' ' + c.Behiavours[k].BehiavourID + ' ';
						}
					}
					else ToBeSaved[j] += '0';
				}
				if (Game.GameObjects[i] is Script s)
				{
					ToBeSaved[j] = "script " + s.Name + ' ' + s.Enabled + ' ' + s.ClassName + ' ' + s.Path;
				}
				if (Game.GameObjects[i] is SkyColor sky)
				{
					ToBeSaved[j] = "skycolor " + sky.Name + ' ' + sky.Enabled + ' ' + sky.Color.R + ' ' + sky.Color.G + ' ' + sky.Color.B;
				}
				if (Game.GameObjects[i] is Fog fog)
				{
					ToBeSaved[j] = "fog " + fog.Name + ' ' + fog.Enabled + ' ' + fog.FogColor.X + ' ' + fog.FogColor.Y + ' ' + fog.FogColor.Z + ' ' + fog.FogStart + ' ' + fog.FogEnd;
				}
				if (Game.GameObjects[i] is Skinmesh skinmesh)
				{
					ToBeSaved[j] = "skinmesh " + skinmesh.Name + ' ' + skinmesh.Enabled + ' ' + Vector2String(skinmesh.Position) + ' ' +
						Vector2String(skinmesh.Rotation) + ' ' + Vector2String(skinmesh.Scale) + ' ' + skinmesh.FogEnabled + ' ' +
						Vector2String(skinmesh.BoundingBox.Min) + ' ' + Vector2String(skinmesh.BoundingBox.Max) + skinmesh.BoundingSphere.Radius + ' ' + skinmesh.Resource;
				}
				if (Game.GameObjects[i] is Sprite sprite)
				{
					string rectangle_string = "0 0 0 0";
					if (sprite.SpriteSheetSection.HasValue)
					{
						rectangle_string = sprite.SpriteSheetSection.Value.X + " " + sprite.SpriteSheetSection.Value.Y + ' ' + sprite.SpriteSheetSection.Value.Width + ' ' + sprite.SpriteSheetSection.Value.Height;
					}
					ToBeSaved[j] = "sprite " + sprite.Name + ' ' + sprite.Enabled + ' ' + Vector2String(sprite.Position) + ' ' + Vector2String(sprite.Size) + ' ' + Vector2String(sprite.Center) +
						' '+sprite.Rotation+ ' '  + rectangle_string + ' ' + sprite.Mask.R + ' ' + sprite.Mask.G + ' ' + sprite.Mask.B + ' ' + (int)(sprite.Effects) + ' ' + sprite.Layer + ' ' + sprite.Resource;
				}
				if (Game.GameObjects[i] is TextPrint textPrint)
				{
					ToBeSaved[j] = "textprint " + textPrint.Name + ' ' + textPrint.Enabled + ' ' + Vector2String(textPrint.Position) + ' ' + Vector2String(textPrint.Size) + ' ' + textPrint.Rotation +
						' ' + Vector2String(textPrint.Center) + ' ' + textPrint.Color.R + ' ' + textPrint.Color.G + ' ' + textPrint.Color.B + ' ' + (int)(textPrint.Effects) + ' ' + textPrint.Layer + ' ' + textPrint.Text + ' ' + (char)0xfe + ' ' + textPrint.Resource;
				}
				if(Game.GameObjects[i] is SoundEffect sound)
				{
					ToBeSaved[j] = "soundeffect " + sound.Name + ' ' + sound.Enabled + ' ' + sound.Volume + ' ' + sound.Pitch + ' ' + sound.Pan + ' '+sound.SoundState+' ' + sound.Resource;
				}
				if(Game.GameObjects[i] is ExitFade fade)
				{
					ToBeSaved[j] = "exitfade " + fade.Name + ' ' + fade.Enabled + ' ' + fade.Fade.R + ' ' + fade.Fade.G + ' ' + fade.Fade.B + ' ' + fade.Time + ' ' + fade.FadeType;
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
		/// <summary>
		/// Clears native memory used by the game.
		/// <para>This will put pressure to the C#'s garbage collection system.</para>
		/// </summary>
		public static void UnloadObjects()
		{
			for (int i = 0; i < Game.GameObjects.Count; i++)
			{
				if (Game.GameObjects[i] is Sprite sp)
				{
					sp.Dispose();
				}
				if (Game.GameObjects[i] is TextPrint tp)
				{
					tp.Dispose();
				}
			}
			Game.GameObjects.Clear();
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
