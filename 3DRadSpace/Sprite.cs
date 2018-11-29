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
                    try
                    {
                        pictureBox1.ImageLocation = openFile.FileName;
                    }
                    catch (FileNotFoundException)
                    {
                        MessageBox.Show("The selected file does not exist.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    finally
                    {
                        File.Copy(openFile.FileName, @"./Content/sprites/" + openFile.SafeFileName);
                        spriteasset = openFile.SafeFileName;
                    }
                }
                catch(IOException)
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
            Game1.LastObj = "";
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "Sprite " + textBox1.Text + " " + checkBox1.Checked + " " + textBox2.Text + " " + textBox3.Text + " " + textBox5.Text + " " + textBox7 + " " + textBox4 + " " + textBox6.Text + " " + spriteasset;
            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
