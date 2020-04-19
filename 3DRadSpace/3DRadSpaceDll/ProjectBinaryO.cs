using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpaceDll
{
    public partial class ProjectBinary
	{
		/// <summary>
		/// 
		/// </summary>
		/// <param name="file"></param>
		/// <param name="list"></param>
		public static void Save(string file,List<GameObject> list)
		{
			List<byte> result = new List<byte>();
			result.AddRange(GetStringBytes("3DRSP_bin"));
			for (int i = 0; i < list.Count; i++)
			{
				GameObject o = list[i];
				if (o is Camera c)
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
					for (int j = 0; j < c.Behiavours.Count; j++)
					{
						result.AddRange(BitConverter.GetBytes(c.Behiavours[j].ObjectID));
						result.AddRange(BitConverter.GetBytes(c.Behiavours[j].BehiavourID));
					}
				}
				if (o is Script s)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.Script));
					result.AddRange(GetStringBytes(s.Name));
					result.AddRange(BitConverter.GetBytes(s.Enabled));
					result.AddRange(GetStringBytes(s.ClassName));
					result.AddRange(GetStringBytes(s.Path));
				}
				if (o is SkyColor sc)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.Script));
					result.AddRange(GetStringBytes(sc.Name));
					result.AddRange(BitConverter.GetBytes(sc.Enabled));
					result.Add(sc.Color.R);
					result.Add(sc.Color.G);
					result.Add(sc.Color.B);
				}
				if(o is Fog f)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.Fog));
					result.AddRange(GetStringBytes(f.Name));
					result.AddRange(BitConverter.GetBytes(f.Enabled));
					result.AddRange(BitConverter.GetBytes(f.FogColor.X));
					result.AddRange(BitConverter.GetBytes(f.FogColor.Y));
					result.AddRange(BitConverter.GetBytes(f.FogColor.Z));
					result.AddRange(BitConverter.GetBytes(f.FogStart));
					result.AddRange(BitConverter.GetBytes(f.FogEnd));
				}
				if (o is Skinmesh sk)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.Skinmesh));
					result.AddRange(GetStringBytes(sk.Name));
					result.AddRange(BitConverter.GetBytes(sk.Enabled));
					result.AddRange(GetV3Bytes(sk.Position));
					result.AddRange(GetV3Bytes(sk.Rotation));
					result.AddRange(GetV3Bytes(sk.Scale));
					result.AddRange(GetBoxBytes(sk.BoundingBox));
					result.AddRange(BitConverter.GetBytes(sk.BoundingSphere.Radius));
					result.AddRange(GetStringBytes(sk.Resource));
				}
				if(o is Sprite sp)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.Sprite));
					result.AddRange(GetStringBytes(sp.Name));
					result.AddRange(BitConverter.GetBytes(sp.Enabled));
					result.AddRange(GetV2Bytes(sp.Position));
					result.AddRange(GetV2Bytes(sp.Size));
					result.AddRange(GetV2Bytes(sp.Center));
					result.AddRange(BitConverter.GetBytes(sp.Rotation));
					if(sp.SpriteSheetSection != null) result.AddRange(GetRectangleBytes((Rectangle)sp.SpriteSheetSection));
					else
					{
						Rectangle r = Rectangle.Empty;
						result.AddRange(GetRectangleBytes(r));
					}
					result.AddRange(new byte[] { sp.Mask.R, sp.Mask.G, sp.Mask.B });
					result.AddRange(BitConverter.GetBytes((int)sp.Effects));
					result.AddRange(BitConverter.GetBytes((int)sp.Layer));
					result.AddRange(GetStringBytes(sp.Resource));
				}
				if(o is TextPrint tp)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.Textprint));
					result.AddRange(GetStringBytes(tp.Name));
					result.AddRange(BitConverter.GetBytes(tp.Enabled));
					result.AddRange(GetV2Bytes(tp.Position));
					result.AddRange(GetV2Bytes(tp.Size));
					result.AddRange(GetV2Bytes(tp.Center));
					result.AddRange(BitConverter.GetBytes(tp.Rotation));
					result.AddRange(new byte[] { tp.Color.R, tp.Color.G, tp.Color.B });
					result.AddRange(BitConverter.GetBytes((int)tp.Effects));
					result.AddRange(BitConverter.GetBytes((int)tp.Layer));
					result.AddRange(GetStringBytes(tp.Text));
					result.AddRange(GetStringBytes(tp.Resource));
				}
				if(o is SoundSource ss)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.SoundSource));
					result.AddRange(GetStringBytes(ss.Name));
					result.AddRange(BitConverter.GetBytes(ss.Enabled));
					result.AddRange(BitConverter.GetBytes(ss.Volume));
					result.AddRange(BitConverter.GetBytes(ss.Pitch));
					result.AddRange(BitConverter.GetBytes(ss.Pan));
					result.AddRange(BitConverter.GetBytes((int)ss.SoundState));
					result.AddRange(GetV3Bytes(ss.Position));
					result.AddRange(BitConverter.GetBytes(ss.DopplerScale));
					result.AddRange(GetStringBytes(ss.Resource));
				}
				if (o is SoundEffect se)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.SoundEffect));
					result.AddRange(GetStringBytes(se.Name));
					result.AddRange(BitConverter.GetBytes(se.Enabled));
					result.AddRange(BitConverter.GetBytes(se.Volume));
					result.AddRange(BitConverter.GetBytes(se.Pitch));
					result.AddRange(BitConverter.GetBytes(se.Pan));
					result.AddRange(BitConverter.GetBytes((int)se.SoundState));
					result.AddRange(GetStringBytes(se.Resource));
				}
				if(o is ExitFade ef)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.ExitFade));
					result.AddRange(GetStringBytes(ef.Name));
					result.AddRange(BitConverter.GetBytes(ef.Enabled));
					result.AddRange(new byte[] { ef.Color.R, ef.Color.G, ef.Color.B });
					result.AddRange(BitConverter.GetBytes(ef.Time));
					result.AddRange(BitConverter.GetBytes(ef.FadeType));
					result.AddRange(GetStringBytes(ef.Resource));
				}
				if(o is EventOnLocation eol)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.EOL));
					result.AddRange(GetStringBytes(eol.Name)); ;
					result.AddRange(BitConverter.GetBytes(eol.Enabled));
					result.AddRange(GetBoxBytes(eol.BoundingBox));
					result.AddRange(GetSphBytes(eol.BoundingSphere));
					result.AddRange(GetPlaneBytes(eol.BoundingPlane));
					result.AddRange(OpcodeEvent.OpCodeCall.ToBytes(eol.Behiavours));
				}
				if( o is EventOnKey eok)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.EOK));
					result.AddRange(GetStringBytes(eok.Name)); ;
					result.AddRange(BitConverter.GetBytes(eok.Enabled));
					result.AddRange(BitConverter.GetBytes((int)eok.Key.Key));
					result.AddRange(BitConverter.GetBytes((int)eok.Key.State));
					result.AddRange(BitConverter.GetBytes(eok.HoldingTime));
					result.AddRange(OpcodeEvent.OpCodeCall.ToBytes(eok.Behiavours));
				}
				if(o is Timer t)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.Timer));
					result.AddRange(GetStringBytes(t.Name));
					result.AddRange(BitConverter.GetBytes(t.Enabled));
					result.AddRange(BitConverter.GetBytes(t.Period));
					result.AddRange(BitConverter.GetBytes(t.Repetitions));
					result.AddRange(OpcodeEvent.OpCodeCall.ToBytes(t.Behiavours));
				}
				if(o is Skybox sb)
				{
					result.AddRange(BitConverter.GetBytes((int)ObjectIdentifier.Skybox));
					result.AddRange(GetStringBytes(sb.Name));
					result.AddRange(BitConverter.GetBytes(sb.Enabled));
					result.AddRange(GetStringBytes(sb.Resource));
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
			Buffer.BlockCopy(BitConverter.GetBytes(b.Z), 0, result, 2 * sizeof(float), sizeof(float));
			return result;
		}
		static byte[] GetRectangleBytes(Rectangle r)
		{
			byte[] result = new byte[4 * sizeof(int)];
			Buffer.BlockCopy(BitConverter.GetBytes(r.X), 0, result, 0, sizeof(int));
			Buffer.BlockCopy(BitConverter.GetBytes(r.Y), 0, result, sizeof(int), sizeof(int));
			Buffer.BlockCopy(BitConverter.GetBytes(r.Width), 0, result, 2*sizeof(int), sizeof(int));
			Buffer.BlockCopy(BitConverter.GetBytes(r.Height), 0, result, 3*sizeof(int), sizeof(int));
			return result;
		}
		static byte[] GetBoxBytes(BoundingBox box)
		{
			byte[] result = new byte[6 * sizeof(float)];
			Buffer.BlockCopy(GetV3Bytes(box.Min), 3 * sizeof(float), result, 0, 3 * sizeof(float));
			Buffer.BlockCopy(GetV3Bytes(box.Max), 3 * sizeof(float), result, 3 * sizeof(float), 3 * sizeof(float));
			return result;
		}
		static byte[] GetSphBytes(BoundingSphere sph)
		{
			byte[] result = new byte[6 * sizeof(float)];
			Buffer.BlockCopy(GetV3Bytes(sph.Center), 3 * sizeof(float), result, 0, 3 * sizeof(float));
			Buffer.BlockCopy(BitConverter.GetBytes(sph.Radius), 3 * sizeof(float), result, 3 * sizeof(float),sizeof(float));
			return result;
		}
		static byte[] GetPlaneBytes(Plane p)
		{
			byte[] result = new byte[6 * sizeof(float)];
			Buffer.BlockCopy(GetV3Bytes(p.Normal), 3 * sizeof(float), result, 0, 3 * sizeof(float));
			Buffer.BlockCopy(BitConverter.GetBytes(p.D), 3 * sizeof(float), result, 3 * sizeof(float), sizeof(float));
			return result;
		}
	}
}
