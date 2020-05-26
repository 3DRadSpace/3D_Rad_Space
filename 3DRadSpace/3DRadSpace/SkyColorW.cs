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

namespace _3DRadSpace
{
    public partial class SkyColorW : Form
    {
        public SkyColorW()
        {
            InitializeComponent();
        }
        public SkyColorW(SkyColor s)
        {
            InitializeComponent();
            textBox1.Text = s.Name;
            checkBox1.Checked = s.Enabled;
            textBox2.Text = s.Color.R+"";
            textBox3.Text = s.Color.G+"";
            textBox4.Text = s.Color.B+"";
        }
        public GameObject Result;
        private void button1_Click(object sender, EventArgs e)
        {
            ColorDialog color = new ColorDialog()
            {
                AnyColor = true,
            };
            color.ShowDialog();
            textBox2.Text = color.Color.R+"";
            textBox3.Text = color.Color.G+"";
            textBox4.Text = color.Color.B+"";
            color.Dispose();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //open documentation
        }

        private void button3_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Result = null;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Result = new SkyColor(Editor.ValidateTextInput(textBox1.Text), checkBox1.Checked, new Microsoft.Xna.Framework.Color(
                Convert.ToByte(Editor.ValidateNumberTextInput(textBox2.Text), Program.CultureInfo),
                Convert.ToByte(Editor.ValidateNumberTextInput(textBox3.Text), Program.CultureInfo),
                Convert.ToByte(Editor.ValidateNumberTextInput(textBox4.Text), Program.CultureInfo)));
            Close();
        }
    }
}
