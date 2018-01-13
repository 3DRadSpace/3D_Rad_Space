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
    public partial class OptionsMenuStrip : Form
    {
        public OptionsMenuStrip()
        {
            InitializeComponent();
        }
        public static string StripResult;
        private void linkLabel3_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            StripResult = null;
            Game1.Focus = true;
            Close();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Game1.notifyIcon.BalloonTipIcon = ToolTipIcon.Info;
            Game1.notifyIcon.BalloonTipText = "Please wait, searching for updates, the game editor may freeze a while.";
            Game1.notifyIcon.BalloonTipTitle = "Looking of updates...";
            Game1.notifyIcon.ShowBalloonTip(2000);
            StripResult = null;
            Game1.UpdateV(true);
            Game1.Focus = true;
            Close();
        }

        private void linkLabel2_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            OptionsDialog dialog1 = new OptionsDialog();
            dialog1.ShowDialog();
            StripResult = null;
            Game1.Focus = true;
            Close();
        }
    }
}
