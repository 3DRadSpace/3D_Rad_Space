using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Engine3DRadSpace
{
	public class Game
	{
		bool _valid;
		bool _running = true;

		double u_dt = 0;
		double d_dt = 0;

		protected List<Tuple<int, object>> objects;

		public Game(string title, uint width = 800, uint height = 600, bool fullscreen = false)
		{
			objects = new List<Tuple<int, object>>();
			Window = new Window(title, width, height);
			Device = new GraphicsDevice(Window.NativeHandle, width, height);
		}

		public Window Window;
		public GraphicsDevice Device;

	}
}
