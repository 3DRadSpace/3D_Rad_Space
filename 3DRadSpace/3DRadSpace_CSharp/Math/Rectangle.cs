using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace.Math
{
	[StructLayout(LayoutKind.Sequential)]
	public struct RectangleF : IEquatable<RectangleF>
	{
		public float X;
		public float Y;
		public float Width;
		public float Height;

		public RectangleF(float x, float y, float w, float h)
		{
			X = x;
			Y = y;
			Width = w; 
			Height = h;
		}

		public bool Equals(RectangleF other)
		{
			return X == other.X &&
				Y == other.Y &&
				Width == other.Width &&
				Height == other.Height;
		}
	}

	[StructLayout(LayoutKind.Sequential)]
	public struct Rectangle : IEquatable<Rectangle>
	{
		public int X;
		public int Y;
		public int Width;
		public int Height;

		public Rectangle(int x, int y, int w, int h)
		{
			X = x;
			Y = y;
			Width = w;
			Height = h;
		}

		public bool Equals(Rectangle other)
		{
			return X == other.X &&
				Y == other.Y &&
				Width == other.Width &&
				Height == other.Height;
		}
	}
}
