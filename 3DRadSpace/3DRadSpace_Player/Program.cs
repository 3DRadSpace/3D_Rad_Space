using System;

namespace _3DRadSpace_Player
{
#if WINDOWS || LINUX
    /// <summary>
    /// The main class.
    /// </summary>
    public static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            using (var Game = new Game1())
            {
                Game.Run();
            }
        }
    }
#endif
}
