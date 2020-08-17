using System;

namespace _3DRadSpace_Player
{
    /// <summary>
    /// The main class.
    /// </summary>
    public static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] Args)
        {
            string debugp = null;
            if (Args.Length > 0)
            {
                debugp = Args[0];
            }
            using (var Game = new Game1(debugp))
            {
                Game.Run();
            }
        }
    }
}
