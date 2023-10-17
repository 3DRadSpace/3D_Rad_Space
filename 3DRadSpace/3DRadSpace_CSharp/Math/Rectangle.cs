using System.Runtime.InteropServices;

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

		public override bool Equals(object? obj)
		{
			if (obj is RectangleF r)
			{
				return r.Equals(obj);
			}
			return false;
		}

		public bool Equals(RectangleF other)
		{
			return X == other.X &&
				Y == other.Y &&
				Width == other.Width &&
				Height == other.Height;
		}

		public override int GetHashCode()
		{
			return HashCode.Combine(X, Y, Width, Height);
		}

		public static bool operator ==(RectangleF left, RectangleF right)
		{
			return left.Equals(right);
		}
		public static bool operator !=(RectangleF left, RectangleF right)
		{
			return !left.Equals(right);
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

		public override bool Equals(object? other)
		{
			if (other is Rectangle r)
			{
				return r.Equals(this);
			}
			return false;
		}

		public override int GetHashCode()
		{
			return HashCode.Combine(X, Y, Width, Height);
		}

		public static bool operator ==(Rectangle a, Rectangle b)
		{
			return a.Equals(b);
		}
		public static bool operator !=(Rectangle a, Rectangle b)
		{
			return !a.Equals(b);
		}
	}
}
