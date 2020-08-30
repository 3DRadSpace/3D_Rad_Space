using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using _3DRadSpaceDll;

namespace _3DRadSpace_Engine
{
    static class Program
    {
        public const string Version = "0.1.0a";
        [STAThread]
        public static void Main(string[] args)
        {
            string path = args[0];
            Application.EnableVisualStyles();
            Application.CurrentCulture = _3DRadSpaceDll.Main.Culture;
            using (Editor editor = new Editor())
            {
                editor.Run();
            }
        }
    }
}
