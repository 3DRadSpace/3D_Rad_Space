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
        [STAThread]
        public static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.CurrentCulture = _3DRadSpaceDll.Main.Culture;
            using (Editor editor = new Editor())
                editor.Run();
        }
    }
}
