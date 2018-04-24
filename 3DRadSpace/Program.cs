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
        /// Loaded file in startup. Used single time.
        /// </summary>
        static string[] file;
        [STAThread]
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main(string[] args)
        {
            Environment.CurrentDirectory = Application.StartupPath;//if you remove this, crashes will happen if you open a project directly with 3drsp.
            Application.EnableVisualStyles();
            using (var game = new Game1())
            {
                try
                {
                    if (args[0] != null)
                    {
                        file = File.ReadAllLines(args[0]);
                    }
                    for(int i =0; i < file.Length; i++)
                    {
                        if(string.IsNullOrEmpty(file[i]) != true)
                        {
                            game.ObjectsData[i] = file[i];
                        }
                    }
                }
                catch { }
                game.Run();
            };
        }
    }
#endif
}
