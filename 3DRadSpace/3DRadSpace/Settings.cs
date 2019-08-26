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
            File.WriteAllText(appd + "Config.cgf", checkBox1.Checked + " " + checkBox2.Checked + " " + checkBox3.Checked);
            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
