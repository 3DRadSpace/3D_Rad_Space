using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

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
	};
}
