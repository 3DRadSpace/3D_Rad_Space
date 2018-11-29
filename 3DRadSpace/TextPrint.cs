using System;
using System.IO;
using System.Windows.Forms;
using System.Diagnostics;
using System.Drawing;

namespace _3DRadSpace
{
    public partial class TextPrint : Form
    {
        public TextPrint()
        {
            InitializeComponent();
        }
        public Color Colour;
        private void button4_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "TextPrint " + textBox1.Text + " " + checkBox1.Checked.ToString() + " " + textBox3.Text + " " + textBox4.Text + " " + Colour.R + " " + Colour.G + " " + Colour.B + " " + textBox2.Text;
            DialogResult = DialogResult.OK;
            Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "";
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Process.Start("");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ColorDialog color = new ColorDialog()
            {
                AnyColor = true,
                FullOpen = true,
                AllowFullOpen = true
            };
            color.ShowDialog();
            Colour = color.Color;
        }
    }
}
