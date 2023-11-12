using System.Runtime.InteropServices;

namespace Engine3DRadSpace
{
	[StructLayout(LayoutKind.Sequential)]
	public struct Viewport
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
	}
}
