using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace _3DRadSpace
{
    public partial class HelpMenuStrip : Form
    {
        public HelpMenuStrip()
        {
            InitializeComponent();
        }
        public static string StripResult;
        private void linkLabel5_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            StripResult = null;
            Game1.Focus = true;
            Close();
        }

        private void linkLabel3_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start("https://3dradspace.000webhostapp.com/Report-a-bug/");
            StripResult = null;
            Game1.Focus = true;
            Close();
        }

        private void linkLabel4_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start("https://classdev.net/page/board/15/3d-rad-space");
            StripResult = null;
            Game1.Focus = true;
            Close();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            AboutWindow about = new AboutWindow();
            about.ShowDialog();
            StripResult = null;
            Game1.Focus = true;
            Close();
        }

        private void linkLabel2_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start("https://3dradspace.000webhostapp.com/");
            StripResult = null;
            Game1.Focus = true;
            Close();
        }

        private void HelpMenuStrip_Load(object sender, EventArgs e)
        {
            Location = new System.Drawing.Point(150, 30);
        }
    }
}
