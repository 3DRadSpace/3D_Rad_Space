using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace _3DRadSpace
{
    public partial class OptionsDialog : Form
    {
        public OptionsDialog()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string[] settings = {checkBox1.Checked.ToString(),checkBox2.Checked.ToString() };
            File.WriteAllLines(@"settings.data",settings);
            Game1.notifyIcon.BalloonTipIcon = ToolTipIcon.Info;
            Game1.notifyIcon.BalloonTipText = "New settings are saved.";
            Game1.notifyIcon.BalloonTipTitle = "Information";
            Game1.notifyIcon.ShowBalloonTip(2000);
            Close();
        }

        private void OptionsDialog_Load(object sender, EventArgs e)
        {
           string[] settings = File.ReadAllLines(@"settings.data");
            bool[] settingsbool = { Convert.ToBoolean(settings[0]), Convert.ToBoolean(settings[1]) };
            checkBox1.Checked = settingsbool[0];
            checkBox2.Checked = settingsbool[1];
        }
    }
}
