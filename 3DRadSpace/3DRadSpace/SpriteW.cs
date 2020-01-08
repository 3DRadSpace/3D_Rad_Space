using System;
using Microsoft.Xna.Framework;
using System.Windows.Forms;
using _3DRadSpaceDll;

namespace _3DRadSpace
{
    public partial class SpriteW : Form
    {

        public object Result;
        public SpriteW()
        {
            InitializeComponent();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Result = new Sprite(Editor.ValidateTextInput(textBox1.Text), checkBox1.Checked, Editor.ValidateTextInput(textBox2.Text),
                new Vector2(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox3.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox4.Text))),
                new Vector2(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox6.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox7.Text))),
                new Vector2(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox8.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox9.Text))),
                Convert.ToSingle(textBox5.Text)
     );
            DialogResult = DialogResult.OK;
            Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
                Title = "Find a image...",
                Multiselect = false,
            };
            if(openFile.ShowDialog() == DialogResult.OK) pictureBox1.ImageLocation = openFile.FileName;
            openFile.Dispose();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            //open docs
        }
    }
}
