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
                Filter = "Skybox file (*.sky)|*.sky",
            };
            bool ok = true;
            if (openImage.ShowDialog() == DialogResult.OK)
            {
                string[] textures = File.ReadAllLines(openImage.FileName);
                for (int i = 0; i < 6; i++)
                {
                    _imageslist[i] = Path.GetDirectoryName(openImage.FileName) + "\\" + textures[i];
                    if (!File.Exists(_imageslist[i]))
                    {
                        MessageBox.Show("Texture file " + _imageslist[i] + " doesn't exist.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        ok = false;
                        break;
                    }
                }
            }
            if (ok)
            {
                pictureBox1.ImageLocation = _imageslist[0];
                _loaded_sky = openImage.FileName;
            }
            openImage.Dispose();
        }
        string[] _imageslist = new string[6];
        string _loaded_sky = null;
        private void button2_Click(object sender, EventArgs e)
        {
            if (File.Exists(pictureBox1.ImageLocation))
            {
                DialogResult = DialogResult.OK;
                Result = new Skybox()
                {
                    Name = textBox1.Text,
                    Enabled = checkBox1.Checked,
                    Resource = _loaded_sky
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

        int c = 0;
        private void pictureBox1_Click(object sender, EventArgs e)
        {
            if (_loaded_sky != null)
            {
                c++;
                if (c == 5) c = 0;
                pictureBox1.ImageLocation = _imageslist[c];
            }
        }
    }
}
