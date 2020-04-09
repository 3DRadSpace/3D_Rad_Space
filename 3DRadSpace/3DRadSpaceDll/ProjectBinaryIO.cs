using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpaceDll
{
	/// <summary>
	/// Loads and saved projects in binary format
	/// </summary>
	public class ProjectBinary
	{
		enum ObjectIdentifier
		{
			Camera,
			Script,
			SkyColor,
			Fog,
			Skinmesh,
			Sprite,
			Textprint,
			SoundEffect,
			ExitFade,
			SoundSource,
			EOL,
			EOK,
			GameSettings,
			Timer
		}
		/// <summary>
		/// Loads a project.
		/// </summary>
		/// <param name="filename">Absolute path.</param>
		/// <returns></returns>
		public List<GameObject> Load(string filename)
		{
			if (!File.Exists(filename)) return null;
			List<GameObject> g = new List<GameObject>();
			byte[] buf = File.ReadAllBytes(filename);
			int l;
			if (FromNullTerminatedCharP(buf, 0, out l) != "3DRSP_bin") return null;
			for(int i =l; i < buf.Length;i++)
			{
				int objid = BitConverter.ToInt32(buf, i);
				int j = i;
				GameObject obj = null;
				switch(objid)
				{
					case (int)ObjectIdentifier.Camera:
						{
							Vector3 pos, rot, view;
							float fov, min_drw, max_drw;
							j += sizeof(int);
							int a,obj_rcount;
							string name = FromNullTerminatedCharP(buf, j,out a);
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j);
							j += 1;
							pos = V3FromByte(buf,ref j);
							rot = V3FromByte(buf,ref j);
							view = V3FromByte(buf,ref j);
							fov = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							min_drw = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							max_drw = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							obj_rcount = BitConverter.ToInt32(buf, j);
							j += sizeof(int);
							Camera c = new Camera()
							{
								Name = name,
								Enabled = enabled,
								Position = pos,
								Rotation = rot,
								CameraRotation = view,
								FOV = fov,
								MinDrawDist = min_drw,
								MaxDrawDist = max_drw,
								Behiavours = new List<ObjectBehiavour>()
							};
							for (int k = 0; k < obj_rcount; k++)
							{
								c.Behiavours.Add(new ObjectBehiavour(
									BitConverter.ToInt32(buf, j),
									BitConverter.ToInt32(buf, j + sizeof(int))));
								j += 2 * sizeof(int);
							}
							obj = c;
							break;
						}
					case (int)ObjectIdentifier.Script:
						{
							int a;
							string name = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j);
							j += 1;
							string classn = FromNullTerminatedCharP(buf, j,out a);
							j += a;
							string path = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							obj = new Script()
							{
								Name = name,
								Enabled = enabled,
								ClassName = classn,
								Path = path,
							};
							break;
						}
					case (int)ObjectIdentifier.SkyColor:
						{
							int a;
							string name = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j);
							j += 1;
							byte cr = buf[j];
							byte cg = buf[j+1];
							byte cb = buf[j+2];
							j += 3;
							obj = new SkyColor()
							{
								Name = name,
								Enabled = enabled,
								Color = new Color(cr, cg, cb),
							};
							break;
						}
					case (int)ObjectIdentifier.Fog:
						{
							int a;
							string name = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j);
							j += 1;
							byte cr = buf[j];
							byte cg = buf[j + 1];
							byte cb = buf[j + 2];
							j += 3;
							float start = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							float end = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							obj = new Fog()
							{
								Name = name,
								Enabled = enabled,
								FogColor = new Vector3(cr, cg, cb),
								FogStart = start,
								FogEnd = end
							};
							break;
						}
					case (int)ObjectIdentifier.Skinmesh:
						{
							int a;
							string name = FromNullTerminatedCharP(buf, j, out a),modelp;
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j),fog_e;
							j += 1;
							Vector3 pos, rot, scale;
							pos = V3FromByte(buf,ref j);
							rot = V3FromByte(buf, ref j);
							scale = V3FromByte(buf, ref j);
							fog_e = BitConverter.ToBoolean(buf, j);
							j++;
							BoundingBox box = BoxFromByte(buf, ref j);
							BoundingSphere sph = new BoundingSphere(Vector3.Zero, BitConverter.ToSingle(buf, j));
							j += sizeof(float);
							modelp = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							obj = new Skinmesh()
							{
								Name = name,
								Enabled = enabled,
								FogEnabled = fog_e,
								Position = pos,
								Rotation = rot,
								Scale = scale,
								BoundingBox = box,
								BoundingSphere = sph,
								Resource = modelp
							};
							break;
						}
					case (int)ObjectIdentifier.Sprite:
						{
							int a;
							string name = FromNullTerminatedCharP(buf, j, out a), path;
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j);
							j += 1;
							Vector2 pos,scale, center;
							float rot, layer;
							pos = V2FromByte(buf, ref j);
							scale = V2FromByte(buf, ref j);
							center = V2FromByte(buf, ref j);
							rot = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							Rectangle? source_r = RFromByte(buf, ref j);
							if (source_r == Rectangle.Empty) source_r = null;
							Color mask = new Color(buf[j], buf[j + 1], buf[j + 2]);
							j += 3;
							SpriteEffects ef = (SpriteEffects)BitConverter.ToInt32(buf, j);
							j += sizeof(int);
							layer = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							path = FromNullTerminatedCharP(buf, j,out a);
							j += a;
							obj = new Sprite()
							{
								Name = name,
								Enabled = enabled,
								Position = pos,
								Center = center,
								Size = scale,
								Rotation = rot,
								Effects = ef,
								Layer = layer,
								Mask = mask,
								SpriteSheetSection = source_r,
								Resource = path,
							};
							break;
						}
					case (int)ObjectIdentifier.Textprint:
						{
							int a;
							string name = FromNullTerminatedCharP(buf, j, out a), path,text;
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j);
							j += 1;
							Vector2 pos, scale, center;
							float rot, layer;
							pos = V2FromByte(buf, ref j);
							scale = V2FromByte(buf, ref j);
							center = V2FromByte(buf, ref j);
							rot = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							Rectangle? source_r = RFromByte(buf, ref j);
							if (source_r == Rectangle.Empty) source_r = null;
							Color mask = new Color(buf[j], buf[j + 1], buf[j + 2]);
							j += 3;
							SpriteEffects ef = (SpriteEffects)BitConverter.ToInt32(buf, j);
							j += sizeof(int);
							layer = BitConverter.ToSingle(buf, j);
							text = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							j += sizeof(float);
							path = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							obj = new TextPrint()
							{
								Name = name,
								Enabled = enabled,
								Position = pos,
								Center = center,
								Size = scale,
								Rotation = rot,
								Effects = ef,
								Layer = layer,
								Color = mask,
								Resource = path,
								Text = text
							};
							break;
						}
					case (int)ObjectIdentifier.SoundEffect:
						{
							int a;
							string name = FromNullTerminatedCharP(buf, j, out a), path;
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j);
							j += 1;
							float volume = BitConverter.ToSingle(buf, j) , pitch, pan;
							j += sizeof(float);
							pitch = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							pan = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							Microsoft.Xna.Framework.Audio.SoundState state = (Microsoft.Xna.Framework.Audio.SoundState)BitConverter.ToInt32(buf, j);
							j += sizeof(int);
							path = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							obj = new SoundEffect()
							{
								Name = name,
								Enabled = enabled,
								Volume = volume,
								Pitch = pitch,
								Pan = pan,
								SoundState = state,
								Resource = path,
							};
							break;
						}
					case (int)ObjectIdentifier.ExitFade:
						{
							int a;
							string name = FromNullTerminatedCharP(buf, j, out a), path;
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j);
							j += 1;
							Color c = new Color(buf[j], buf[j + 1], buf[j + 2]);
							j += 3;
							float time = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							bool fadetype = BitConverter.ToBoolean(buf, j);
							j += 1;
							path = FromNullTerminatedCharP(buf, j,out a);
							j += a;
							obj = new ExitFade()
							{
								Name = name,
								Enabled = enabled,
								Fade = c,
								Time = time,
								FadeType = fadetype,
								ProjectToLoad = path
							};
							break;
						}
					case (int)ObjectIdentifier.SoundSource:
						{
							int a;
							string name = FromNullTerminatedCharP(buf, j, out a), path;
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j);
							j += 1;
							float volume = BitConverter.ToSingle(buf, j), pitch, pan,doppler;
							j += sizeof(float);
							pitch = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							pan = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							Microsoft.Xna.Framework.Audio.SoundState state = (Microsoft.Xna.Framework.Audio.SoundState)BitConverter.ToInt32(buf, j);
							j += sizeof(int);
							Vector3 pos = V3FromByte(buf, ref j);
							doppler = BitConverter.ToSingle(buf, j);
							j += sizeof(float);
							path = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							obj = new SoundSource()
							{
								Name = name,
								Enabled = enabled,
								Volume = volume,
								Pitch = pitch,
								Pan = pan,
								SoundState = state,
								Resource = path,
								Position = pos,
								DopplerScale = doppler,
							};
							break;
						}
					case (int)ObjectIdentifier.EOL:
						{
							int a;
							string name = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j),editor_v;
							j += 1;
							BoundingBox box = BoxFromByte(buf, ref j);
							BoundingSphere sph = SphereFromByte(buf, ref j);
							Plane p = PlaneFromByte(buf, ref j);
							editor_v = BitConverter.ToBoolean(buf, j);
							j += 1;
							BoundingObject t;
							if (box != new BoundingBox(Vector3.Zero, Vector3.Zero)) t = BoundingObject.Box;
							else if (sph != new BoundingSphere(Vector3.Zero, 0)) t = BoundingObject.Sphere;
							else if (p != new Plane(Vector3.Zero, 0)) t = BoundingObject.Plane;
							else t = BoundingObject.None;
							EventOnLocation e = new EventOnLocation()
							{
								Name = name,
								Enabled = enabled,
								BoundingBox = box,
								BoundingSphere = sph,
								BoundingPlane = p,
								BoundingType = t,
								VisibleInEditor = editor_v,
							};
							e.Behiavours = OpcodeEvent.OpCodeCall.CreateFromBuffer(buf, j,out a);
							j += a;
							obj = e;
							break;
						}
					case (int)ObjectIdentifier.EOK:
						{
							int a,key,keyt;
							string name = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j);
							j += 1;
							key = BitConverter.ToInt32(buf, j);
							j += sizeof(int);
							keyt = BitConverter.ToInt32(buf, j);
							j += sizeof(int);
							uint time = BitConverter.ToUInt32(buf, j);
							j += sizeof(uint);
							EventOnKey keye = new EventOnKey()
							{
								Name = name,
								Enabled = enabled,
								Key = new KeyInput()
								{
									Key = (Microsoft.Xna.Framework.Input.Keys)key,
									State = (KeyInputType)keyt
								},
								HoldingTime = time
							};
							keye.Behiavours = OpcodeEvent.OpCodeCall.CreateFromBuffer(buf, j,out a);
							j += a;
							obj = keye;
							break;
						}
					case (int)ObjectIdentifier.Timer:
						{
							int a;
							string name = FromNullTerminatedCharP(buf, j, out a);
							j += a;
							bool enabled = BitConverter.ToBoolean(buf, j);
							j += 1;
							uint time = BitConverter.ToUInt32(buf,j), repetitions;
							j += sizeof(float);
							repetitions = BitConverter.ToUInt32(buf, j);
							j += sizeof(float);
							Timer t = new Timer()
							{
								Name = name,
								Enabled = enabled,
								Period = time,
								Repetitions = repetitions,
							};
							t.Behiavours = OpcodeEvent.OpCodeCall.CreateFromBuffer(buf, j, out a);
							j += a;
							obj = t;
							break;
						}
					default:
						break;
				}
				g.Add(obj);
			}
			return g;
		}
		bool _bytetobool(byte b)
		{
			if (b == 0) return false;
			else return true;
		}
		string FromNullTerminatedCharP(byte[] b,int start,out int length)
		{
			int a = 0;
			StringBuilder result = new StringBuilder();
			for(int i =start; b[i] != 0;i++)
			{
				a++;
				result.Append((char)b[i]);
			}
			length = a;
			return result.ToString();
		}
		Vector2 V2FromByte(byte[] buf,ref int offset)
		{
			float a, b;
			a = BitConverter.ToSingle(buf, offset);
			b = BitConverter.ToSingle(buf, offset + sizeof(float));
			offset += 2 * sizeof(float);
			return new Vector2(a, b);
		}
		Vector3 V3FromByte(byte[] buf,ref int offset)
		{
			float a, b,c;
			a = BitConverter.ToSingle(buf, offset);
			b = BitConverter.ToSingle(buf, offset + sizeof(float));
			c = BitConverter.ToSingle(buf, offset + (2*sizeof(float)));
			offset += sizeof(float) * 3;
			return new Vector3(a, b, c);
		}
		BoundingBox BoxFromByte(byte[] buf,ref int i)
		{
			return new BoundingBox(V3FromByte(buf, ref i), V3FromByte(buf, ref i));
		}
		BoundingSphere SphereFromByte(byte[] buff,ref int i)
		{
			BoundingSphere r = new BoundingSphere()
			{
				Center = V3FromByte(buff, ref i),
				Radius = BitConverter.ToSingle(buff, i)
			};
			i += sizeof(float);
			return r;
		}
		Rectangle RFromByte(byte[] buff,ref int i)
		{
			Rectangle r = new Rectangle();
			r.X = BitConverter.ToInt32(buff, i);
			i += sizeof(float);
			r.Y = BitConverter.ToInt32(buff, i);
			i += sizeof(float);
			r.Width = BitConverter.ToInt32(buff, i);
			i += sizeof(float);
			r.Height = BitConverter.ToInt32(buff, i);
			i += sizeof(float);
			return r;
		}
		Plane PlaneFromByte(byte[] buff,ref int i)
		{
			Vector3 n = V3FromByte(buff, ref i);
			float d = BitConverter.ToSingle(buff, i);
			i += sizeof(float);
			return new Plane(n, d);
		}
		/// <summary>
		/// 
		/// </summary>
		/// <param name="file"></param>
		public static void Save(string file)
		{
			List<byte> result = new List<byte>();
			for(int i =0; i < Game.GameObjects.Count;i++)
			{
				GameObject o = Game.GameObjects[i];
				if(o is Camera c)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.Camera));
					result.AddRange(GetStringBytes(c.Name));
					result.AddRange(BitConverter.GetBytes(c.Enabled));
					result.AddRange(GetV3Bytes(c.Position));
					result.AddRange(GetV3Bytes(c.Rotation));
					result.AddRange(GetV3Bytes(c.CameraRotation));
					result.AddRange(BitConverter.GetBytes(c.FOV));
					result.AddRange(BitConverter.GetBytes(c.MinDrawDist));
					result.AddRange(BitConverter.GetBytes(c.MaxDrawDist));
					result.AddRange(BitConverter.GetBytes(c.Behiavours.Count));
					for(int j =0; j < c.Behiavours.Count;j++)
					{
						result.AddRange(BitConverter.GetBytes(c.Behiavours[j].ObjectID));
						result.AddRange(BitConverter.GetBytes(c.Behiavours[j].BehiavourID));
					}
				}
				if(o is Script s)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.Script));
					result.AddRange(GetStringBytes(s.Name));
					result.AddRange(BitConverter.GetBytes(s.Enabled));
					result.AddRange(GetStringBytes(s.ClassName));
					result.AddRange(GetStringBytes(s.Path));
				}
				if(o is SkyColor sc)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.Script));
					result.AddRange(GetStringBytes(sc.Name));
					result.AddRange(BitConverter.GetBytes(sc.Enabled));
					result.Add(sc.Color.R);
					result.Add(sc.Color.G);
					result.Add(sc.Color.B);
				}
			}
		}
		static byte[] GetStringBytes(string s)
		{
			byte[] r = new byte[s.Length + 1];
			for (int i = 0; i < s.Length; i++) r[i] = (byte)s[i];
			r[s.Length] = 0;
			return r;
		}
		static byte[] GetV2Bytes(Vector2 b)
		{
			byte[] result = new byte[2 * sizeof(float)];
			Buffer.BlockCopy(BitConverter.GetBytes(b.X), 0, result, 0, sizeof(float));
			Buffer.BlockCopy(BitConverter.GetBytes(b.Y), 0, result, sizeof(float), sizeof(float));
			return result;
		}
		static byte[] GetV3Bytes(Vector3 b)
		{
			byte[] result = new byte[3 * sizeof(float)];
			Buffer.BlockCopy(BitConverter.GetBytes(b.X), 0, result, 0, sizeof(float));
			Buffer.BlockCopy(BitConverter.GetBytes(b.Y), 0, result, sizeof(float), sizeof(float));
			Buffer.BlockCopy(BitConverter.GetBytes(b.Z), 0, result, 2*sizeof(float), sizeof(float));
			return result;
		}
	}
}
