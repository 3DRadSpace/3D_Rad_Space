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
    public partial class Fog : Form
    {
        public Fog()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ColorDialog colorDialog = new ColorDialog()
            {
                AllowFullOpen = true,
                FullOpen = true,
            };
            colorDialog.ShowDialog();
            textBox4.Text = colorDialog.Color.R+"";
            textBox5.Text = colorDialog.Color.G+"";
            textBox6.Text = colorDialog.Color.B+"";
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "";
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "Fog " + _3DRadSpace_EditorClass.ValidateText(textBox1.Text) + " " +
                checkBox1.Checked+" "+
                _3DRadSpace_EditorClass.ValidateNumberBox(textBox2.Text) + " " +
                _3DRadSpace_EditorClass.ValidateNumberBox(textBox3.Text) + " " + 
                _3DRadSpace_EditorClass.ValidateNumberBox(textBox4.Text) + " " +
                _3DRadSpace_EditorClass.ValidateNumberBox(textBox5.Text) + " " +
                _3DRadSpace_EditorClass.ValidateNumberBox(textBox6.Text);
            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
