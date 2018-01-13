using System;
using System.Windows.Forms;
using System.IO;

namespace _3DRadSpace
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
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            using (var game = new Game1())
            {   
                game.Run();
            }
        }
    }
#endif
}
