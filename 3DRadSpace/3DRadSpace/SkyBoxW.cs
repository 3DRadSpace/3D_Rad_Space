using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using _3DRadSpaceDll;
using System.IO;

namespace _3DRadSpace
{
    public partial class SkyBoxW : Form
    {
        public SkyBoxW()
        {
            InitializeComponent();
        }
        public SkyBoxW(Skybox sb)
        {
            InitializeComponent();
            textBox1.Text = sb.Name;
            checkBox1.Checked = sb.Enabled;
            pictureBox1.ImageLocation = sb.Resource;
        }
        public GameObject Result;
        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openImage = new OpenFileDialog()
            {
                Multiselect = false,
            };
            if(openImage.ShowDialog() == DialogResult.OK)
            {
                string f = "Content\\Skybox\\" + Path.GetFileName(openImage.FileName);
                File.Copy(openImage.FileName, f,true);
                pictureBox1.ImageLocation = f;
            }
            openImage.Dispose();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (File.Exists(pictureBox1.ImageLocation))
            {
                DialogResult = DialogResult.OK;
                Result = new Skybox()
                {
                    Name = textBox1.Text,
                    Enabled = checkBox1.Checked,
                    Resource = pictureBox1.ImageLocation
                };
                Close();
            }
            else MessageBox.Show("You need to load a image.", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }
    }
}
