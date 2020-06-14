using System;
using System.Windows.Forms;
using _3DRadSpaceDll;
using System.Globalization;

namespace _3DRadSpace
{
#if WINDOWS || LINUX
    /// <summary>
    /// The main class.
    /// </summary>
    public static class Program
    {
        public static bool ProjectTypeScript = false;
        public static readonly int Version = 5;
        [STAThread]
        static void Main(string[] Arguments) //Command line arguments
        {
            Environment.CurrentDirectory = Application.StartupPath;
            Application.EnableVisualStyles();
            Application.CurrentCulture = CultureInfo;
            using (var Editor = new Editor())
            {
                bool EditorOpen = true;
                if (Arguments.Length > 0)
                {
                    string extention = Arguments[0].Split('.')[1];
                    if (extention == "3drsp") Editor.OpenedFile = Arguments[0];
                    else if(extention == "cs")
                    {
                        ProjectTypeScript = true;
                        EditorOpen = false;
                    }
                }
                if(EditorOpen) Editor.Run();
            }
            if(ProjectTypeScript)
            {
                ScriptW script = new ScriptW(new Script("Opened_File",true,Arguments[0],"Script"));
                script.ShowDialog();
            }
        }
        public static CultureInfo CultureInfo { get; } = new CultureInfo("EN-en"); //An fix for the culture related issues
    }
#endif
}
