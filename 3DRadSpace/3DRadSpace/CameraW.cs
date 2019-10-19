using System;
using Microsoft.Xna.Framework;
using System.Windows.Forms;
using _3DRadSpaceDll;

namespace _3DRadSpace
{
    public partial class CameraW : Form
    {
        public CameraW()
        {
            InitializeComponent();
        }
        public object Result;
        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void button6_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.Cancel;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Result = new Camera(textBox1.Text, checkBox1.Checked, new Vector3(Convert.ToSingle(textBox2.Text), Convert.ToSingle(textBox3.Text), Convert.ToSingle(textBox4.Text)),
                new Vector3(Convert.ToSingle(textBox6.Text), Convert.ToSingle(textBox7.Text), Convert.ToSingle(textBox5.Text))
                ,new Vector3(Convert.ToSingle(textBox10.Text), Convert.ToSingle(textBox9.Text), Convert.ToSingle(textBox8.Text)),
                Convert.ToSingle(numericUpDown1.Value), Convert.ToSingle(textBox11.Text), Convert.ToSingle(textBox12.Text));
            DialogResult = DialogResult.OK;
            Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //Open docuentation.
        }
    }
}
