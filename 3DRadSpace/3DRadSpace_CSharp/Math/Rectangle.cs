using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace.Math
{
	[StructLayout(LayoutKind.Sequential)]
	public struct RectangleF
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
	}

	[StructLayout(LayoutKind.Sequential)]
	public struct Rectangle
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
	}
}
