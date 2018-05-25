using System;
using System.IO;
using System.Windows.Forms;
using System.Diagnostics;

namespace _3DRadSpace
{
    public partial class Sprite : Form
    {
        public Sprite()
        {
            InitializeComponent();
        }
        private string spriteasset = null;
        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
               Filter = "Image Files(*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG",
               Title = "Select an image...",
               Multiselect = false,
            };
            DialogResult img = openFile.ShowDialog();
            if(img == DialogResult.OK)
            {
                try
                {
                    File.Copy(openFile.FileName, @"Content/sprites/" + openFile.SafeFileName);
                    pictureBox1.ImageLocation = openFile.FileName;
                    spriteasset = openFile.SafeFileName;
                }
                catch
                {
                    
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Process.Start(@"Help Files/Sprite.rtf");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            File.WriteAllText(@"lastobject.data"," ");
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            File.WriteAllText(@"lastobject.data","Sprite "+textBox1.Text+" "+checkBox1.Checked+" "+textBox2.Text+" "+textBox3.Text+" "+textBox5.Text+" "+textBox7+" "+textBox4+" "+textBox6.Text+" "+numericUpDown1.Value+" "+spriteasset);
            Close();
        }
    }
}
