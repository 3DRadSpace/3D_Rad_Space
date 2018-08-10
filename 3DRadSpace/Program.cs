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
        static string[] file;
        [STAThread]
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main(string[] args)
        {
            Environment.CurrentDirectory = Application.StartupPath;
            Application.EnableVisualStyles();
            using (var game = new Game1())
            {
                try
                {
                    if (args[0] != null)
                    {
                        file = File.ReadAllLines(args[0]);
                    }
                    if (args[0].Split('.')[1].ToLower() == "3drss")
                    {
                        Script script = new Script();
                        script.richTextBox1.Text = "";
                        for (int i = 0; i < file.Length; i++)
                        {
                            script.richTextBox1.Text += file[i] + "\r\n";
                        }
                        script.ShowDialog();
                        return;
                    }
                    else
                    {
                        for (int i = 0; i < file.Length; i++)
                        {
                            if (string.IsNullOrEmpty(file[i]) != true)
                            {
                                game.ObjectsData[i] = file[i];
                            }
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
