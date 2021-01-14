using System;
using System.IO;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public static class Program
    {
        public static string Version;
        [STAThread]
        public static void Main(string[] args)
        {
            Environment.CurrentDirectory = Application.StartupPath;
            Application.EnableVisualStyles();
            bool script = false;
            string file = null;
            if(args.Length > 0)
            {
                if (File.Exists(args[0]))
                {
                    file = args[0];
                    string[] ext = file.Split(',');
                    if (ext[ext.Length - 1] == ".cs") script = true;
                }
            }
            if(!script) using (Main main = new Main(file)) main.Run();
            else
            {
                ScriptWnd wnd = new ScriptWnd(new Lib3DRadSpace_DX.Script("Script", true, "Script", File.ReadAllText(file)));
                wnd.ShowDialog();
            }
        }
    }
}
