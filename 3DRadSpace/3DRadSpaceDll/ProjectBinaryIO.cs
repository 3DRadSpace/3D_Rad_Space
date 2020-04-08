using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Microsoft.Xna.Framework;

namespace _3DRadSpaceDll
{
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
			for(int i =0; i < buf.Length;i++)
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
							pos = V3FromByte(buf, j);
							j += 3 * sizeof(float);
							rot = V3FromByte(buf, j);
							j += 3 * sizeof(float);
							view = V3FromByte(buf, j);
							j += 3 * sizeof(float);
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
		Vector2 V2FromByte(byte[] buf,int offset)
		{
			float a, b;
			a = BitConverter.ToSingle(buf, offset);
			b = BitConverter.ToSingle(buf, offset + sizeof(float));
			return new Vector2(a, b);
		}
		Vector3 V3FromByte(byte[] buf, int offset)
		{
			float a, b,c;
			a = BitConverter.ToSingle(buf, offset);
			b = BitConverter.ToSingle(buf, offset + sizeof(float));
			c = BitConverter.ToSingle(buf, offset + (2*sizeof(float)));
			return new Vector3(a, b, c);
		}
	}
}
