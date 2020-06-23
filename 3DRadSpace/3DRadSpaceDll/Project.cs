using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

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
			if (Data[0] != "3DRSP_text") return result; //Check if project is valid.
			for (int i =1; i < Data.Length;i++) //Loop each line
			{
				//Split the current line
				string[] Obj = Data[i].Split(' ');
				GameObject a; //Object to be added.
				switch(Obj[0]) //Identify the current object.
				{
					case "fpvcam":
						{
							FPVCamera c = new FPVCamera(Obj[1], Convert.ToBoolean(Obj[2],Main.CultureInfo), new Vector3(Convert.ToSingle(Obj[3],Main.CultureInfo), Convert.ToSingle(Obj[4],Main.CultureInfo), Convert.ToSingle(Obj[5],Main.CultureInfo)),
								new Vector2(Convert.ToSingle(Obj[6],Main.CultureInfo), Convert.ToSingle(Obj[7], Main.CultureInfo)),
								new Vector3(Convert.ToSingle(Obj[8], Main.CultureInfo), Convert.ToSingle(Obj[9], Main.CultureInfo), Convert.ToSingle(Obj[10], Main.CultureInfo)),
								MathHelper.ToRadians(Convert.ToSingle(Obj[11], Main.CultureInfo)), Convert.ToSingle(Obj[12], Main.CultureInfo), Convert.ToSingle(Obj[13], Main.CultureInfo),
								(Keys)Convert.ToInt32(Obj[14], Main.CultureInfo),(Keys)Convert.ToInt32(Obj[15]),(Keys)Convert.ToInt32(Obj[16], Main.CultureInfo),(Keys)Convert.ToInt32(Obj[17], Main.CultureInfo),
								Convert.ToSingle(Obj[18]),Convert.ToSingle(Obj[19], Main.CultureInfo));
							a = c;
							break;
						}
					case "camera":
						{
							Camera c = new Camera(Obj[1], Convert.ToBoolean(Obj[2], Main.CultureInfo), new Vector3(Convert.ToSingle(Obj[3], Main.CultureInfo), Convert.ToSingle(Obj[4], Main.CultureInfo), Convert.ToSingle(Obj[5], Main.CultureInfo)),
								new Vector3(Convert.ToSingle(Obj[6], Main.CultureInfo), Convert.ToSingle(Obj[7], Main.CultureInfo), Convert.ToSingle(Obj[8], Main.CultureInfo)),
								new Vector3(Convert.ToSingle(Obj[9], Main.CultureInfo), Convert.ToSingle(Obj[10], Main.CultureInfo), Convert.ToSingle(Obj[11], Main.CultureInfo)),
								Convert.ToSingle(Obj[12], Main.CultureInfo), Convert.ToSingle(Obj[13], Main.CultureInfo), Convert.ToSingle(Obj[14], Main.CultureInfo));
							int capacity = Convert.ToInt32(Obj[15], Main.CultureInfo);
							if (capacity > 0)
							{
								c.Behiavours = new List<ObjectBehiavour>(capacity);
								for (int j = 0; j < capacity; j++)
								{
									c.Behiavours.Add(new ObjectBehiavour(Convert.ToInt32(Obj[16 + j], Main.CultureInfo), Convert.ToInt32(Obj[17 + (j*2)], Main.CultureInfo)));
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
							a = new Script(Obj[1], Convert.ToBoolean(Obj[2], Main.CultureInfo), path, Obj[3]);
							break;
						}
					case "skycolor":
						{
							a = new SkyColor(Obj[1], Convert.ToBoolean(Obj[2], Main.CultureInfo), new Color(
								Convert.ToByte(Obj[3], Main.CultureInfo),
								Convert.ToByte(Obj[4], Main.CultureInfo),
								Convert.ToByte(Obj[5], Main.CultureInfo)
								));
							break;
						}
					case "fog":
						{
							a = new Fog(Obj[0], Convert.ToBoolean(Obj[2], Main.CultureInfo), new Color(
								Convert.ToByte(Obj[3], Main.CultureInfo),
								Convert.ToByte(Obj[4], Main.CultureInfo),
								Convert.ToByte(Obj[5], Main.CultureInfo)
								),
								Convert.ToSingle(Obj[6], Main.CultureInfo), Convert.ToSingle(Obj[7], Main.CultureInfo));
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
							a = new Skinmesh(Obj[1], Convert.ToBoolean(Obj[2], Main.CultureInfo), path,
								new Vector3(Convert.ToSingle(Obj[3], Main.CultureInfo),Convert.ToSingle(Obj[4], Main.CultureInfo),Convert.ToSingle(Obj[5], Main.CultureInfo))
								, new Vector3(Convert.ToSingle(Obj[6], Main.CultureInfo),Convert.ToSingle(Obj[7], Main.CultureInfo),Convert.ToSingle(Obj[8], Main.CultureInfo))
								, new Vector3(Convert.ToSingle(Obj[9], Main.CultureInfo),Convert.ToSingle(Obj[10], Main.CultureInfo),Convert.ToSingle(Obj[11], Main.CultureInfo)),
								Convert.ToBoolean(Obj[12], Main.CultureInfo),new BoundingBox(
									new Vector3(Convert.ToSingle(Obj[13], Main.CultureInfo),Convert.ToSingle(Obj[14], Main.CultureInfo),Convert.ToSingle(Obj[15], Main.CultureInfo))
									,new Vector3(Convert.ToSingle(Obj[16], Main.CultureInfo),Convert.ToSingle(Obj[17], Main.CultureInfo),Convert.ToSingle(Obj[18], Main.CultureInfo)))
									,new BoundingSphere(Vector3.Zero,Convert.ToSingle(Obj[19], Main.CultureInfo)));
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
							Sprite s = new Sprite(Obj[1], Convert.ToBoolean(Obj[2], Main.CultureInfo), path,
								new Vector2(Convert.ToInt32(Obj[3], Main.CultureInfo), Convert.ToInt32(Obj[4], Main.CultureInfo)), new Vector2(Convert.ToInt32(Obj[5], Main.CultureInfo), Convert.ToInt32(Obj[6], Main.CultureInfo)),
								new Vector2(Convert.ToInt32(Obj[7], Main.CultureInfo), Convert.ToInt32(Obj[8], Main.CultureInfo)), Convert.ToSingle(Obj[9], Main.CultureInfo),
								new Rectangle(Convert.ToInt32(Obj[10], Main.CultureInfo),Convert.ToInt32(Obj[11], Main.CultureInfo),Convert.ToInt32(Obj[12], Main.CultureInfo),Convert.ToInt32(Obj[13], Main.CultureInfo))
								, new Color(Convert.ToByte(Obj[14], Main.CultureInfo), Convert.ToByte(Obj[15], Main.CultureInfo), Convert.ToByte(Obj[16], Main.CultureInfo)), (SpriteEffects)Convert.ToInt32(Obj[17], Main.CultureInfo),Convert.ToInt32(Obj[18], Main.CultureInfo));
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
							a = new TextPrint(Obj[1], Convert.ToBoolean(Obj[2], Main.CultureInfo), font, text,
								new Vector2(Convert.ToSingle(Obj[3], Main.CultureInfo), Convert.ToSingle(Obj[4], Main.CultureInfo)),
								new Vector2(Convert.ToSingle(Obj[5], Main.CultureInfo), Convert.ToSingle(Obj[6], Main.CultureInfo)), Convert.ToSingle(Obj[7], Main.CultureInfo),
								new Vector2(Convert.ToSingle(Obj[8], Main.CultureInfo), Convert.ToSingle(Obj[9], Main.CultureInfo)),
								new Color(Convert.ToByte(Obj[10], Main.CultureInfo), Convert.ToByte(Obj[11], Main.CultureInfo), Convert.ToByte(Obj[12], Main.CultureInfo)),
								(SpriteEffects)(Convert.ToInt32(Obj[13], Main.CultureInfo)),Convert.ToSingle(Obj[14], Main.CultureInfo));
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
							a = new SoundEffect(Obj[1], Convert.ToBoolean(Obj[2], Main.CultureInfo), path, Convert.ToSingle(Obj[3], Main.CultureInfo))
							{
								Pitch = Convert.ToSingle(Obj[4], Main.CultureInfo),
								Pan = Convert.ToSingle(Obj[5], Main.CultureInfo),
								SoundState = (Microsoft.Xna.Framework.Audio.SoundState)Convert.ToInt32(Obj[6], Main.CultureInfo)
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
								Enabled = Convert.ToBoolean(Obj[2], Main.CultureInfo),
								Color = new Color(
									Convert.ToByte(Obj[3], Main.CultureInfo), Convert.ToByte(Obj[4], Main.CultureInfo), Convert.ToByte(Obj[5], Main.CultureInfo)
								),
								Time = Convert.ToInt32(Obj[6], Main.CultureInfo),
								FadeType = Convert.ToBoolean(Obj[7], Main.CultureInfo),
								Resource = path
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
								Enabled = Convert.ToBoolean(Obj[2], Main.CultureInfo),
								Volume = Convert.ToSingle(Obj[3], Main.CultureInfo),
								Pitch = Convert.ToSingle(Obj[4], Main.CultureInfo),
								Pan = Convert.ToSingle(Obj[5], Main.CultureInfo),
								SoundState = (Microsoft.Xna.Framework.Audio.SoundState)Convert.ToInt32(Obj[6], Main.CultureInfo),
								Position = new Vector3(
									Convert.ToSingle(Obj[7], Main.CultureInfo), Convert.ToSingle(Obj[8], Main.CultureInfo), Convert.ToSingle(Obj[9], Main.CultureInfo)
									),
								DopplerScale = Convert.ToSingle(Obj[10], Main.CultureInfo),
								Resource = path,
							};
							break;
						}
					case "eol":
						{
							a = new EventOnLocation()
							{
								Name = Obj[1],
								Enabled = Convert.ToBoolean(Obj[2], Main.CultureInfo),
								BoundingBox = new BoundingBox(new Vector3(
									Convert.ToSingle(Obj[3], Main.CultureInfo), Convert.ToSingle(Obj[4], Main.CultureInfo), Convert.ToSingle(Obj[5], Main.CultureInfo))
								, new Vector3(
									Convert.ToSingle(Obj[6], Main.CultureInfo), Convert.ToSingle(Obj[7], Main.CultureInfo), Convert.ToSingle(Obj[8], Main.CultureInfo))),
								BoundingSphere = new BoundingSphere(new Vector3(
									Convert.ToSingle(Obj[9], Main.CultureInfo), Convert.ToSingle(Obj[10], Main.CultureInfo), Convert.ToSingle(Obj[11], Main.CultureInfo)),
									Convert.ToSingle(Obj[12], Main.CultureInfo)),
								BoundingPlane = new Plane(new Vector4(
									Convert.ToSingle(Obj[13], Main.CultureInfo), Convert.ToSingle(Obj[14], Main.CultureInfo), Convert.ToSingle(Obj[15], Main.CultureInfo), Convert.ToSingle(Obj[16], Main.CultureInfo))),
								VisibleInEditor = Convert.ToBoolean(Obj[17], Main.CultureInfo),
								Behiavours = OpcodeEvent.OpCodeCall.CreateFromString(18, Obj, Obj.Length)
							};
							break;
						}
					case "eok":
						{
							a = new EventOnKey()
							{
								Name = Obj[1],
								Enabled = Convert.ToBoolean(Obj[2], Main.CultureInfo),
								Key = new KeyInput((Microsoft.Xna.Framework.Input.Keys)Convert.ToInt32(Obj[3], Main.CultureInfo),
								(KeyInputType)Convert.ToInt32(Obj[4], Main.CultureInfo)),
								HoldingTime = Convert.ToUInt32(Obj[5], Main.CultureInfo),
								Behiavours = OpcodeEvent.OpCodeCall.CreateFromString(6, Obj, Obj.Length)
							};
							break;
						}
					case "gamesettings":
						{
							a = null;
							GSettings = new GameSettings()
							{
								Fullscreen = Convert.ToBoolean(Obj[1], Main.CultureInfo),
								MaximumFramerate = Convert.ToInt32(Obj[2], Main.CultureInfo),
								GameScreen = new Point(Convert.ToInt32(Obj[3], Main.CultureInfo),Convert.ToInt32(Obj[4], Main.CultureInfo))
							};
							break;
						}
					case "timer":
						{
							a = new Timer()
							{
								Name = Obj[1],
								Enabled = Convert.ToBoolean(Obj[2], Main.CultureInfo),
								Period = Convert.ToUInt32(Obj[3], Main.CultureInfo),
								Repetitions = Convert.ToUInt32(Obj[4], Main.CultureInfo),
								Behiavours = OpcodeEvent.OpCodeCall.CreateFromString(5, Obj, Obj.Length)
							};
							break;
						}
					case "skybox":
						{
							string path = "";
							for(int k =3; k < Obj.Length;k++)
							{
								path += Obj[k] + ' ';
							}
							path = path.Remove(path.Length - 1);
							a = new Skybox()
							{
								Name = Obj[1],
								Enabled = Convert.ToBoolean(Obj[2], Main.CultureInfo),
								Resource = path
							};
							break;
						}
					case "counter":
						{
							string file;
							a = null;
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
			ToBeSaved[0] = "3DRSP_text";
			for (int i = 0; i < Game.GameObjects.Count; i++)
			{
				int j = i + 1;
				if (Game.GameObjects[i] is FPVCamera fpv)
				{
					ToBeSaved[j] = "fpvcam " + fpv.Name + ' ' + fpv.Enabled + ' ' + Vector2String(fpv.Position) + ' ' + Vector2String(fpv.CamScreenCoords) +
						' ' + Vector2String(fpv.CameraRotation) + ' ' + MathHelper.ToDegrees(fpv.FOV) + ' ' + fpv.MinDrawDist + ' ' + fpv.MaxDrawDist +
						' ' + ((int)fpv.Forward) + ' ' + ((int)fpv.Left) + ' ' + ((int)fpv.Backward) + ' ' + ((int)fpv.Right) +
						' ' + fpv.MovementSpeed + ' ' + fpv.Sensibility.ToString(Main.CultureInfo);
				}
				if (Game.GameObjects[i] is Camera c)
				{
					if(!(Game.GameObjects[i] is FPVCamera))
					ToBeSaved[j] = "camera " + c.Name + ' ' + c.Enabled + ' ' + Vector2String(c.Position) + ' ' + Vector2String(c.Rotation) +
						' ' + Vector2String(c.CameraRotation) + ' ' + MathHelper.ToDegrees(c.FOV) + ' ' + c.MinDrawDist + ' ' + c.MaxDrawDist + ' ';
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
					ToBeSaved[j] = "fog " + fog.Name + ' ' + fog.Enabled + ' ' + Vector2String(fog.FogColor) + ' ' + fog.FogStart + ' ' + fog.FogEnd;
				}
				if (Game.GameObjects[i] is Skinmesh skinmesh)
				{
					ToBeSaved[j] = "skinmesh " + skinmesh.Name + ' ' + skinmesh.Enabled + ' ' + Vector2String(skinmesh.Position) + ' ' +
						Vector2String(skinmesh.Rotation) + ' ' + Vector2String(skinmesh.Scale) + ' ' + skinmesh.FogEnabled + ' ' +
						Vector2String(skinmesh.BoundingBox.Min) + ' ' + Vector2String(skinmesh.BoundingBox.Max) +' ' + skinmesh.BoundingSphere.Radius + ' ' + skinmesh.Resource;
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
					if(!(Game.GameObjects[i] is SoundSource ))
						ToBeSaved[j] = "soundeffect " + sound.Name + ' ' + sound.Enabled + ' ' + sound.Volume + ' ' + sound.Pitch + ' ' +sound.Pan + ' '+(int)sound.SoundState+' ' + sound.Resource;
				}
				if(Game.GameObjects[i] is ExitFade fade)
				{
					ToBeSaved[j] = "exitfade " + fade.Name + ' ' + fade.Enabled + ' ' + fade.Color.R + ' ' + fade.Color.G + ' ' + fade.Color.B + ' ' + fade.Time + ' ' + fade.FadeType;
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
				if(Game.GameObjects[i] is Skybox sb)
				{
					ToBeSaved[j] = "skybox " + sb.Name + ' ' + sb.Enabled + ' ' + sb.Resource;
				}
				if(Game.GameObjects[i] is Counter cpp)
				{
					ToBeSaved[j] = "counter " + cpp.Name + ' ' + cpp.Enabled + ' ' + cpp.InitialValue + ' ' + cpp.Increment + ' ' + cpp.FileIOSafe;
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
				if (Game.GameObjects[i] is Script sc) sc.End();
				if (Game.GameObjects[i] is Sprite sp) sp.Dispose();
				if (Game.GameObjects[i] is TextPrint tp) tp.Dispose();
				if (Game.GameObjects[i] is Skybox sb) sb.Dispose();
				if (Game.GameObjects[i] is Counter c) c.SaveFile();
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
