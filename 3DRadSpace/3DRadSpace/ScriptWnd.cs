using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Lib3DRadSpace_DX;
using System.Diagnostics;
using System.IO;

namespace _3DRadSpace
{
    public partial class ScriptWnd : Form
    {
        public BaseGameObject Result;

        public ScriptWnd()
        {
            InitializeComponent();
            ScriptWnd_Resize(null,null);
        }
        public ScriptWnd(Script a)
        {
            TXTBOXobject_name.Text = a.Name;
            TXTBOX_className.Text = a.MainClass;
        }

        private void ScriptWnd_Resize(object sender, EventArgs e)
        {
            scintilla1.Size = new Size(scintilla1.Size.Width, Size.Height - 10);
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            Result = new Script(TXTBOXobject_name.Text, CBOX_enabled.Checked, TXTBOX_className.Text,scintilla1.Text.Split('\r','\n'));
            DialogResult = DialogResult.OK;
            Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void helpButton_Click(object sender, EventArgs e)
        {
            //todo: open 3DRadSpace wiki page about the script object.
            //Process.Start("");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Script a = new Script(TXTBOXobject_name.Text, CBOX_enabled.Checked, TXTBOX_className.Text, scintilla1.Text.Split('\r', '\n'));
            if( a.CompileWithoutAssembly(out string[] errs) == false)
            {
                File.WriteAllLines(@"ScriptErrors.log", errs);
                Process.Start(@"ScriptErrors.log");
            }
        }
    }
}
