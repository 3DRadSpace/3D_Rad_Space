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
    public partial class EOL : Form
    {
        public EOL()
        {
            InitializeComponent();
        }

        private void EOL_FormClosed(object sender, FormClosedEventArgs e)
        {
 
        }
        public int? type = null;
        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            ParametersNames();
        }
        public void SelectType()
        {
            if(type == 1) radioButton1.Checked = true;
            if(type == 2) radioButton2.Checked = true;
            if(type == 3) radioButton3.Checked = true;
            if(type == 4) radioButton4.Checked = true;
            if(type == 5) radioButton5.Checked = true;
            ParametersNames();
        }
        private void ParametersNames()
        {
            if (radioButton1.Checked == true)
            {
                textBox5.Enabled = false;
                textBox7.Enabled = true;
                textBox6.Enabled = false;
                label7.Text = "Radius";
                label6.Text = "";
                label5.Text = "";
                type = 1;
            }
            if(radioButton2.Checked == true)
            {
                textBox5.Enabled = true;
                textBox7.Enabled = true;
                textBox6.Enabled = true;
                label7.Text = "X";
                label6.Text = "Y";
                label5.Text = "Z";
                type = 2;
            }
            if (radioButton3.Checked == true)
            {
                textBox5.Enabled = true;
                textBox7.Enabled = true;
                textBox6.Enabled = false;
                label7.Text = "X";
                label6.Text = "";
                label5.Text = "Z";
                type = 3;
            }
            if (radioButton4.Checked == true)
            {
                textBox5.Enabled = false;
                textBox7.Enabled = true;
                textBox6.Enabled = true;
                label7.Text = "X";
                label6.Text = "Y";
                label5.Text = "";
                type = 4;
            }
            if (radioButton5.Checked == true)
            {
                textBox5.Enabled = false;
                textBox7.Enabled = true;
                textBox6.Enabled = false;
                label7.Text = "Radius";
                label6.Text = "";
                label5.Text = "";
                type = 5;
            }
        }

        private void EOL_Load(object sender, EventArgs e)
        {
            type = 1;
            SelectType();
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "";
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "EOL " + textBox1.Text + " " + checkBox1.Checked + " " + type +" "+ textBox2.Text + " " + textBox3.Text + " " + textBox4.Text + " " + textBox7.Text + " " + textBox6.Text + " " + textBox5.Text;
            DialogResult = DialogResult.OK;
            Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }
    }
}
