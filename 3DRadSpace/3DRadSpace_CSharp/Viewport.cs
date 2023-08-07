using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace
{
	[StructLayout(LayoutKind.Sequential)]
	public struct Viewport : IEquatable<Viewport>
	{
		public Viewport(Math.RectangleF r, float mind, float maxd)
		{
			ScreenRectangle = r;
			MinDepth = mind;
			MaxDepth = maxd;
		}

		public Math.RectangleF ScreenRectangle;

		public float MinDepth;
		public float MaxDepth;

		public bool Equals(Viewport other)
		{
			return ScreenRectangle == other.ScreenRectangle &&
			MinDepth == other.MinDepth &&
			MaxDepth == other.MaxDepth;
		}

		public override bool Equals(object? obj)
		{
			return obj is Viewport && Equals((Viewport)obj);
		}

		public static bool operator ==(Viewport left, Viewport right)
		{
			return left.Equals(right);
		}

		public static bool operator !=(Viewport left, Viewport right)
		{
			return !(left == right);
		}

		public override int GetHashCode()
		{
			return HashCode.Combine(ScreenRectangle, MinDepth, MaxDepth);
		}
	}
}
