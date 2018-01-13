using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class FileMenuStrip : Form
    {
        public static string StripResult;
        public FileMenuStrip()
        {
            InitializeComponent();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            StripResult = "1";
            Game1.Focus = true;
            Close();
        }

        private void linkLabel2_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            OpenFileDialog openproject = new OpenFileDialog()
            {
                Filter = "3DRadSpace Project | *.3drsp | Text File | *.txt",
                Multiselect = false,
                CheckFileExists = true,
                InitialDirectory = @"/Projects/",
                Title = "Find a 3DRadSpace project to open..."
            };
            openproject.ShowDialog();
            if (openproject.FileName == null)
            {
                StripResult = null;
                Game1.Focus = true;
                Close();
            }
            else
            {
                StripResult = "2 " + openproject.FileName;
                Game1.Focus = true;
                Close();
            }
        }

        private void linkLabel3_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            SaveFileDialog saveFile = new SaveFileDialog()
            {
                Filter = "3DRadSpace Project | *.3drsp | Text File | *.txt",
                InitialDirectory = @"/Projects/",
                Title = "Save a 3DRadSpace project...",
                OverwritePrompt = true
            };
            saveFile.ShowDialog();
            if(saveFile.FileName == null)
            {
                StripResult = null;
                Game1.Focus = true;
                Close();
            }
            else
            {
                StripResult = "3 " + saveFile.FileName;
                Game1.Focus = true;
                Close();
            }
        }

        private void linkLabel4_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            _3DRadSpaceCompiler comp = new _3DRadSpaceCompiler();
            comp.Show();
            StripResult = null;
            Game1.Focus = true;
            Close();
        }

        private void linkLabel5_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            StripResult = null;
            Game1.Focus = true;
            Close();
        }

        private void FileMenuStrip_Activated(object sender, EventArgs e)
        {
        }

        private void linkLabel6_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Application.Exit();
        }
    }
}
