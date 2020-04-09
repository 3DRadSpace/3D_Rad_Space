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

		/// <summary>
		/// Used in editor
		/// </summary>
		public static GameSettings GSettings { get; private set; }

		/// <summary>
		/// Opens a project
		/// </summary>
		/// <param name="filename">File to open</param>
		/// <returns>Returns the objects.</returns>
		public static List<GameObject> Open(string filename)
		{
			List<GameObject> result = new List<GameObject>();
			string[] Data = File.ReadAllLines(filename); //Read the file
			if (Data[0] != "3DRSP_text") return null;
			for (int i =1; i < Data.Length;i++) //Loop each line
			{
				//Split the current line
				string[] Obj = Data[i].Split(' ');
				GameObject a; //Object to be added.
				switch(Obj[0]) //Identify the current object.
				{
					case "camera":
						{
							Camera c = new Camera(Obj[1], SafeConverter.BoolFromString(Obj[2]), new Vector3(SafeConverter.FloatFromString(Obj[3]), SafeConverter.FloatFromString(Obj[4]), SafeConverter.FloatFromString(Obj[5])),
								new Vector3(SafeConverter.FloatFromString(Obj[6]), SafeConverter.FloatFromString(Obj[7]), SafeConverter.FloatFromString(Obj[8])),
								new Vector3(SafeConverter.FloatFromString(Obj[9]), SafeConverter.FloatFromString(Obj[10]), SafeConverter.FloatFromString(Obj[11])),
								SafeConverter.FloatFromString(Obj[12]), SafeConverter.FloatFromString(Obj[13]), SafeConverter.FloatFromString(Obj[14]));
							int capacity = SafeConverter.IntFromString(Obj[15]);
							if (capacity > 0)
							{
								c.Behiavours = new List<ObjectBehiavour>(capacity);
								for (int j = 0; j < capacity; j++)
								{
									c.Behiavours.Add(new ObjectBehiavour(SafeConverter.IntFromString(Obj[16 + j]), SafeConverter.IntFromString(Obj[17 + (j*2)])));
								}
							}
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
							path = path.Remove(path.Length - 1);
							a = new Script(Obj[1], SafeConverter.BoolFromString(Obj[2]), path, Obj[3]);
							break;
						}
					case "skycolor":
						{
							a = new SkyColor(Obj[1], SafeConverter.BoolFromString(Obj[2]), new Color(
								Convert.ToByte(Obj[3]),
								Convert.ToByte(Obj[4]),
								Convert.ToByte(Obj[5])
								));
							break;
						}
					case "fog":
						{
							a = new Fog(Obj[0], SafeConverter.BoolFromString(Obj[2]), new Color(
								Convert.ToByte(Obj[3]),
								Convert.ToByte(Obj[4]),
								Convert.ToByte(Obj[5])
								),
								SafeConverter.FloatFromString(Obj[6]), SafeConverter.FloatFromString(Obj[7]));
							break;
						 }
					case "skinmesh":
						{
							string path = "";
							for(int j = 20;j < Obj.Length;j++)
							{
								path += Obj[j] + ' ';
							}
							path = path.Remove(path.Length - 1);
							a = new Skinmesh(Obj[1], SafeConverter.BoolFromString(Obj[2]), path,
								new Vector3(SafeConverter.FloatFromString(Obj[3]),SafeConverter.FloatFromString(Obj[4]),SafeConverter.FloatFromString(Obj[5]))
								, new Vector3(SafeConverter.FloatFromString(Obj[6]),SafeConverter.FloatFromString(Obj[7]),SafeConverter.FloatFromString(Obj[8]))
								, new Vector3(SafeConverter.FloatFromString(Obj[9]),SafeConverter.FloatFromString(Obj[10]),SafeConverter.FloatFromString(Obj[11])),
								SafeConverter.BoolFromString(Obj[12]),new BoundingBox(
									new Vector3(SafeConverter.FloatFromString(Obj[13]),SafeConverter.FloatFromString(Obj[14]),SafeConverter.FloatFromString(Obj[15]))
									,new Vector3(SafeConverter.FloatFromString(Obj[16]),SafeConverter.FloatFromString(Obj[17]),SafeConverter.FloatFromString(Obj[18])))
									,new BoundingSphere(Vector3.Zero,SafeConverter.FloatFromString(Obj[19])));
							break;
						}
					case "sprite":
						{
							string path = "";
							for (int j = 19; j < Obj.Length; j++)
							{
								path += Obj[j] + " ";
							}
							path = path.Remove(path.Length - 1);
							Sprite s = new Sprite(Obj[1], SafeConverter.BoolFromString(Obj[2]), path,
								new Vector2(SafeConverter.IntFromString(Obj[3]), SafeConverter.IntFromString(Obj[4])), new Vector2(SafeConverter.IntFromString(Obj[5]), SafeConverter.IntFromString(Obj[6])),
								new Vector2(SafeConverter.IntFromString(Obj[7]), SafeConverter.IntFromString(Obj[8])), SafeConverter.FloatFromString(Obj[9]),
								new Rectangle(SafeConverter.IntFromString(Obj[10]),SafeConverter.IntFromString(Obj[11]),SafeConverter.IntFromString(Obj[12]),SafeConverter.IntFromString(Obj[13]))
								, new Color(Convert.ToByte(Obj[14]), Convert.ToByte(Obj[15]), Convert.ToByte(Obj[16])), (SpriteEffects)SafeConverter.IntFromString(Obj[17]),SafeConverter.IntFromString(Obj[18]));
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
							a = new TextPrint(Obj[1], SafeConverter.BoolFromString(Obj[2]), font, text,
								new Vector2(SafeConverter.FloatFromString(Obj[3]), SafeConverter.FloatFromString(Obj[4])),
								new Vector2(SafeConverter.FloatFromString(Obj[5]), SafeConverter.FloatFromString(Obj[6])), SafeConverter.FloatFromString(Obj[7]),
								new Vector2(SafeConverter.FloatFromString(Obj[8]), SafeConverter.FloatFromString(Obj[9])),
								new Color(Convert.ToByte(Obj[10]), Convert.ToByte(Obj[11]), Convert.ToByte(Obj[12])),
								(SpriteEffects)(SafeConverter.IntFromString(Obj[13])),SafeConverter.IntFromString(Obj[14]));
							break;
						}
					case "soundeffect":
						{
							string path = "";
							for(int j =7; j < Obj.Length;j++)
							{
								path += Obj[j] + ' ';
							}
							path = path.Remove(path.Length - 1);
							a = new SoundEffect(Obj[1], SafeConverter.BoolFromString(Obj[2]), path, SafeConverter.FloatFromString(Obj[3]))
							{
								Pitch = SafeConverter.FloatFromString(Obj[4]),
								Pan = SafeConverter.FloatFromString(Obj[5]),
								SoundState = (Microsoft.Xna.Framework.Audio.SoundState)SafeConverter.IntFromString(Obj[6])
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
							path = path.Remove(path.Length - 1);
							a = new ExitFade()
							{
								Name = Obj[1],
								Enabled = SafeConverter.BoolFromString(Obj[2]),
								Fade = new Color(
									Convert.ToByte(Obj[3]), Convert.ToByte(Obj[4]), Convert.ToByte(Obj[5])
								),
								Time = SafeConverter.IntFromString(Obj[6]),
								FadeType = SafeConverter.BoolFromString(Obj[7]),
								ProjectToLoad = path
							};
							break;
						}
					case "soundsource":
						{
							string path = "";
							for (int j = 11; j < Obj.Length; j++)
							{
								path += Obj[j] + ' ';
							}
							path = path.Remove(path.Length - 1);
							a = new SoundSource()
							{
								Name = Obj[1],
								Enabled = SafeConverter.BoolFromString(Obj[2]),
								Volume = SafeConverter.FloatFromString(Obj[3]),
								Pitch = SafeConverter.FloatFromString(Obj[4]),
								Pan = SafeConverter.FloatFromString(Obj[5]),
								SoundState = (Microsoft.Xna.Framework.Audio.SoundState)SafeConverter.IntFromString(Obj[6]),
								Position = new Vector3(
									SafeConverter.FloatFromString(Obj[7]), SafeConverter.FloatFromString(Obj[8]), SafeConverter.FloatFromString(Obj[9])
									),
								DopplerScale = SafeConverter.FloatFromString(Obj[10]),
								Resource = path,
							};
							break;
						}
					case "eol":
						{
							a = new EventOnLocation()
							{
								Name = Obj[1],
								Enabled = SafeConverter.BoolFromString(Obj[2]),
								BoundingBox = new BoundingBox(new Vector3(
									SafeConverter.FloatFromString(Obj[3]), SafeConverter.FloatFromString(Obj[4]), SafeConverter.FloatFromString(Obj[5]))
								, new Vector3(
									SafeConverter.FloatFromString(Obj[6]), SafeConverter.FloatFromString(Obj[7]), SafeConverter.FloatFromString(Obj[8]))),
								BoundingSphere = new BoundingSphere(new Vector3(
									SafeConverter.FloatFromString(Obj[9]), SafeConverter.FloatFromString(Obj[10]), SafeConverter.FloatFromString(Obj[11])),
									SafeConverter.FloatFromString(Obj[12])),
								BoundingPlane = new Plane(new Vector4(
									SafeConverter.FloatFromString(Obj[13]), SafeConverter.FloatFromString(Obj[14]), SafeConverter.FloatFromString(Obj[15]), SafeConverter.FloatFromString(Obj[16]))),
								VisibleInEditor = SafeConverter.BoolFromString(Obj[17]),
								Behiavours = OpcodeEvent.OpCodeCall.CreateFromString(18, Obj, Obj.Length)
							};
							break;
						}
					case "eok":
						{
							a = new EventOnKey()
							{
								Name = Obj[1],
								Enabled = SafeConverter.BoolFromString(Obj[2]),
								Key = new KeyInput((Microsoft.Xna.Framework.Input.Keys)SafeConverter.IntFromString(Obj[3]),
								(KeyInputType)SafeConverter.IntFromString(Obj[4])),
								HoldingTime = Convert.ToUInt32(Obj[5]),
								Behiavours = OpcodeEvent.OpCodeCall.CreateFromString(6, Obj, Obj.Length)
							};
							break;
						}
					case "gamesettings":
						{
							a = null;
							GSettings = new GameSettings()
							{
								Fullscreen = SafeConverter.BoolFromString(Obj[1]),
								MaximumFramerate = SafeConverter.IntFromString(Obj[2]),
								GameScreen = new Point(SafeConverter.IntFromString(Obj[3]),SafeConverter.IntFromString(Obj[4]))
							};
							break;
						}
					case "timer":
						{
							a = new Timer()
							{
								Name = Obj[1],
								Enabled = SafeConverter.BoolFromString(Obj[2]),
								Period = Convert.ToUInt32(Obj[3]),
								Repetitions = Convert.ToUInt32(Obj[4]),
								Behiavours = OpcodeEvent.OpCodeCall.CreateFromString(5, Obj, Obj.Length)
							};
							break;
						}
					default:
						{
							throw new FormatException("Unknown object found. Line :" + i + " Identifier:" + Obj[0]);
						}
				}
				if(a != null) result.Add(a);
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
			ToBeSaved[0] = "";
			for (int i = 0; i < Game.GameObjects.Count; i++)
			{
				int j = i + 1;
				if (Game.GameObjects[i] is Camera c)
				{
					ToBeSaved[j] = "camera " + c.Name + ' ' + c.Enabled + ' ' + Vector2String(c.Position) + ' ' + Vector2String(c.Rotation) +
						' ' + Vector2String(c.CameraRotation) + ' ' + SafeConverter.FloatToString(MathHelper.ToDegrees(c.FOV)) + ' ' + c.MinDrawDist + ' ' + c.MaxDrawDist + ' ';
					if (c.Behiavours != null)
					{
						ToBeSaved[j] += c.Behiavours.Count + " ";
						for (int k = 0; k < c.Behiavours.Count; k++)
						{
							ToBeSaved[j] += c.Behiavours[k].ObjectID + " " + c.Behiavours[k].BehiavourID + ' ';
						}
					}
					else ToBeSaved[j] += "0";
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
					ToBeSaved[j] = "fog " + fog.Name + ' ' + fog.Enabled + ' ' + Vector2String(fog.FogColor) + ' ' + SafeConverter.FloatToString(fog.FogStart) + ' ' + SafeConverter.FloatToString(fog.FogEnd);
				}
				if (Game.GameObjects[i] is Skinmesh skinmesh)
				{
					ToBeSaved[j] = "skinmesh " + skinmesh.Name + ' ' + skinmesh.Enabled + ' ' + Vector2String(skinmesh.Position) + ' ' +
						Vector2String(skinmesh.Rotation) + ' ' + Vector2String(skinmesh.Scale) + ' ' + skinmesh.FogEnabled + ' ' +
						Vector2String(skinmesh.BoundingBox.Min) + ' ' + Vector2String(skinmesh.BoundingBox.Max) +' ' + SafeConverter.FloatToString(skinmesh.BoundingSphere.Radius) + ' ' + skinmesh.Resource;
				}
				if (Game.GameObjects[i] is Sprite sprite)
				{
					string rectangle_string = "0 0 0 0";
					if (sprite.SpriteSheetSection.HasValue)
					{
						rectangle_string = sprite.SpriteSheetSection.Value.X + " " + sprite.SpriteSheetSection.Value.Y + ' ' + sprite.SpriteSheetSection.Value.Width + ' ' + sprite.SpriteSheetSection.Value.Height;
					}
					ToBeSaved[j] = "sprite " + sprite.Name + ' ' + sprite.Enabled + ' ' + Vector2String(sprite.Position) + ' ' + Vector2String(sprite.Size) + ' ' + Vector2String(sprite.Center) +
						' '+ SafeConverter.FloatToString(sprite.Rotation)+ ' '  + rectangle_string + ' ' + sprite.Mask.R + ' ' + sprite.Mask.G + ' ' + sprite.Mask.B + ' ' + (int)(sprite.Effects) + ' ' + SafeConverter.FloatToString(sprite.Layer) + ' ' + sprite.Resource;
				}
				if (Game.GameObjects[i] is TextPrint textPrint)
				{
					ToBeSaved[j] = "textprint " + textPrint.Name + ' ' + textPrint.Enabled + ' ' + Vector2String(textPrint.Position) + ' ' + Vector2String(textPrint.Size) + ' ' + textPrint.Rotation +
						' ' + Vector2String(textPrint.Center) + ' ' + textPrint.Color.R + ' ' + textPrint.Color.G + ' ' + textPrint.Color.B + ' ' + (int)(textPrint.Effects) + ' ' + SafeConverter.FloatToString(textPrint.Layer) + ' ' + textPrint.Text + ' ' + (char)0xfe + ' ' + textPrint.Resource;
				}
				if(Game.GameObjects[i] is SoundEffect sound)
				{
					if(!(Game.GameObjects[i] is SoundSource ))
						ToBeSaved[j] = "soundeffect " + sound.Name + ' ' + sound.Enabled + ' ' + SafeConverter.FloatToString(sound.Volume) + ' ' + SafeConverter.FloatToString(sound.Pitch) + ' ' + SafeConverter.FloatToString(sound.Pan) + ' '+(int)sound.SoundState+' ' + sound.Resource;
				}
				if(Game.GameObjects[i] is ExitFade fade)
				{
					ToBeSaved[j] = "exitfade " + fade.Name + ' ' + fade.Enabled + ' ' + fade.Fade.R + ' ' + fade.Fade.G + ' ' + fade.Fade.B + ' ' + SafeConverter.FloatToString((float)fade.Time) + ' ' + fade.FadeType;
				}
				if(Game.GameObjects[i] is EventOnLocation eol)
				{
					string beh = null;
					for(int k =0; k < eol.Behiavours.Count;k++)
					{
						beh += eol.Behiavours[k].ToString();
					}
					ToBeSaved[j] = "eol " + eol.Name + ' ' + eol.Enabled + ' ' + Box2str(eol.BoundingBox) + ' ' + Sph2str(eol.BoundingSphere) + ' ' + Plane2str(eol.BoundingPlane) + ' ' + eol.VisibleInEditor + ' ' + beh;
				}
				if (Game.GameObjects[i] is EventOnKey eok)
				{
					string beh = null;
					for (int k = 0; k < eok.Behiavours.Count; k++)
					{
						beh += eok.Behiavours[k].ToString();
					}
					ToBeSaved[j] = "eok " + eok.Name + ' ' + eok.Enabled + ' ' + (int)eok.Key.Key + ' ' + (int)eok.Key.State + ' ' + eok.HoldingTime + ' ' + beh;
				}
				if (Game.GameObjects[i] is SoundSource sounds)
				{
					ToBeSaved[j] = "soundsource " + sounds.Name + ' ' + sounds.Enabled + ' ' + sounds.Volume + ' ' + sounds.Pitch + ' ' + sounds.Pan + ' ' + (int)sounds.SoundState + ' '+Vector2String(sounds.Position)+' '+sounds.DopplerScale+' ' + sounds.Resource;
				}
				if(Game.GameObjects[i] is Timer timer)
				{
					string beh = null;
					for (int k = 0; k < timer.Behiavours.Count; k++)
					{
						beh += timer.Behiavours[k].ToString();
					}
					ToBeSaved[j] = "timer " + timer.Name + ' ' + timer.Enabled + ' ' + timer.Period + ' ' + timer.Repetitions + ' ' + beh;
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
			return SafeConverter.FloatToString(pos.X) + " " + SafeConverter.FloatToString(pos.Y) + " " + SafeConverter.FloatToString(pos.Z);
		}
		/// <summary>
		/// Converts a vector to a string in the format needed for 3DRSP projects
		/// </summary>
		/// <param name="pos">2D Vector to be converted</param>
		/// <returns>The needed string</returns>
		public static string Vector2String(Vector2 pos)
		{
			return SafeConverter.FloatToString(pos.X) + " " + SafeConverter.FloatToString(pos.Y); ;
		}
		/// <summary>
		/// Used in I/O
		/// </summary>
		/// <param name="box">Bounding sphere</param>
		/// <returns></returns>
		public static string Box2str(BoundingBox box)
		{
			return Vector2String(box.Min) + ' ' + Vector2String(box.Max);
		}
		/// <summary>
		/// Used in I/O
		/// </summary>
		/// <param name="sph">Bounding sphere</param>
		/// <returns></returns>
		public static string Sph2str(BoundingSphere sph)
		{
			return sph.Center.X + " " + sph.Center.Y + ' ' + sph.Center.Z + ' ' + sph.Radius;
		}
		/// <summary>
		/// Used in I/O
		/// </summary>
		/// <param name="p">Bounding plane</param>
		/// <returns></returns>
		public static string Plane2str(Plane p)
		{
			return Vector2String(p.Normal)+ ' ' + p.D;
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
