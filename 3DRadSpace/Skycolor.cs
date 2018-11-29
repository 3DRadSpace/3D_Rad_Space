using System;
using System.IO;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class Skycolor : Form
    {
        public Skycolor()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ColorDialog color = new ColorDialog()
            {
                AllowFullOpen = true,
                AnyColor = true
            };
            color.ShowDialog();
            textBox2.Text = color.Color.R.ToString();
            textBox3.Text = color.Color.G.ToString();
            textBox4.Text = color.Color.B.ToString();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "";
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
           Game1.LastObj = "SkyColor " + textBox1.Text + " " + checkBox1.Checked.ToString() + " " + textBox2.Text + " " + textBox3.Text + " " + textBox4.Text;
            DialogResult = DialogResult.OK;
            Close();
        }

        private void Skycolor_FormClosed(object sender, FormClosedEventArgs e)
        {

        }
    }
}
