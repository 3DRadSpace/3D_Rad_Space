using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace
{
	[StructLayout(LayoutKind.Sequential, Pack = sizeof(float), Size = 4*sizeof(float))]
	public struct Color : IEquatable<Color>
	{
		public float R;
		public float G;
		public float B;
		public float A;

		public Color(float r, float g, float b, float a = 1.0f)
		{
			R = r;
			G = g;
			B = b; 
			A = a;
		}

		public static Color FromRGB(byte r, byte g, byte b, byte a)
		{
			Color result = new Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
			return result;
		}

		public override bool Equals(object? obj)
		{
			return obj is Color color &&
				   R == color.R &&
				   G == color.G &&
				   B == color.B &&
				   A == color.A;
		}

		public bool Equals(Color other)
		{
			return this.R == other.R &&
				this.G == other.G &&
				this.B == other.B &&
				this.A == other.A;
		}

		public override int GetHashCode()
		{
			return HashCode.Combine(R, G, B, A);
		}

		public override string ToString()
		{
			return "{R " + R + " G " + G + " B " + B + " A " + A + " }";
		}

		public static bool operator ==(Color left, Color right)
		{
			return left.Equals(right);
		}

		public static bool operator !=(Color left, Color right)
		{
			return !left.Equals(right);
		}
	}
}
