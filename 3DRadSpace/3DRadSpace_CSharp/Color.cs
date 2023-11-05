using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
	[StructLayout(LayoutKind.Sequential, Pack = sizeof(float), Size = 4 * sizeof(float))]
	public struct Color
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

		public override string ToString()
		{
			return "{R " + R + " G " + G + " B " + B + " A " + A + " }";
		}
	}
}
