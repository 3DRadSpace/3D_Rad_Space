using System;
using System.IO;
using System.Windows.Forms;
using _3DRadSpaceDll;

namespace _3DRadSpace
{
    public partial class Settings : Form
    {
        public Settings()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string appd = Environment.ExpandEnvironmentVariables("%AppData%\\3DRadSpace");
            if (!Directory.Exists(appd))
            {
                Directory.CreateDirectory(appd);
            }
            File.WriteAllText(appd + "\\Config.cfg", checkBox1.Checked + " " + checkBox2.Checked + " " + checkBox3.Checked+ ' '+trackBar1.Value+' '+trackBar2.Value);
            DialogResult = DialogResult.OK;
            Close();
        }

        private void Settings_Load(object sender, EventArgs e)
        {
            string appd = Environment.ExpandEnvironmentVariables("%AppData%\\3DRadSpace");
            if (!File.Exists(appd + "\\Config.cfg")) return;
            string[] split = File.ReadAllText(appd + "\\Config.cfg").Split(' ');
            checkBox1.Checked = Convert.ToBoolean(split[0],Program.CultureInfo);
            checkBox2.Checked = Convert.ToBoolean(split[1],Program.CultureInfo);
            checkBox3.Checked = Convert.ToBoolean(split[2],Program.CultureInfo);
            trackBar1.Value = Convert.ToInt32(split[3],Program.CultureInfo);
            trackBar2.Value = Convert.ToInt32(split[4],Program.CultureInfo);
            trackBar1_Scroll(null, null);
            trackBar2_Scroll(null, null);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label7.Text = 0.001f*trackBar1.Value + "";
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            label8.Text = 0.1f * trackBar2.Value + "";
        }
    }
}
