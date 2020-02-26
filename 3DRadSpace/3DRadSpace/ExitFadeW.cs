using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class ExitFadeW : Form
    {
        public ExitFadeW()
        {
            InitializeComponent();
        }
        public ExitFadeW(_3DRadSpaceDll.ExitFade fade)
        {
            InitializeComponent();
            textBox1.Text = fade.Name;
            textBox2.Text = fade.Fade.R + "";
            textBox3.Text = fade.Fade.G + "";
            textBox4.Text = fade.Fade.B+ "";
            textBox5.Text = fade.Time * 1000 + "";
            textBox6.Text = fade.ProjectToLoad;
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked) checkBox2.Text = "Fade In";
            else checkBox2.Text = "Fade Out";
        }

        private void ExitFadeW_Load(object sender, EventArgs e)
        {
            checkBox2_CheckedChanged(null,null);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            ColorDialog color = new ColorDialog()
            {
                AllowFullOpen = true,
                AnyColor = true
            };
            if(color.ShowDialog() == DialogResult.OK)
            {
                textBox2.Text = color.Color.R + "";
                textBox3.Text = color.Color.G + "";
                textBox4.Text = color.Color.B + "";
            }
            color.Dispose();
        }
    }
}
