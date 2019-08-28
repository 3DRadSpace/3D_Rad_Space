using System;
using System.IO;
using System.Windows.Forms;

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
            File.WriteAllText(appd + "\\Config.cgf", checkBox1.Checked + " " + checkBox2.Checked + " " + checkBox3.Checked);
            DialogResult = DialogResult.OK;
            Close();
        }

        private void Settings_Load(object sender, EventArgs e)
        {
            string appd = Environment.ExpandEnvironmentVariables("%AppData%\\3DRadSpace");
            if (!File.Exists(appd + "\\Config.cgf")) return;
            string[] split = File.ReadAllText(appd + "\\Config.cgf").Split(' ');
            checkBox1.Checked = Convert.ToBoolean(split[0]);
            checkBox2.Checked = Convert.ToBoolean(split[1]);
            checkBox3.Checked = Convert.ToBoolean(split[2]);
        }
    }
}
