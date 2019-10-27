using System;
using Microsoft.Xna.Framework;
using System.Windows.Forms;
using _3DRadSpaceDll;
using System.Globalization;

namespace _3DRadSpace
{
    public partial class CameraW : Form
    {
        public CameraW()
        {
            InitializeComponent();
        }
        public object Result;
        public object[] AttachedObjs;
        public int[] AttachedBehiavour;
        private void button1_Click(object sender, EventArgs e)
        {
            SelectObjectDialog selectObject = new SelectObjectDialog();
            selectObject.ShowDialog();
            _ = listBox1.Items.Add(_3DRadSpaceDll.Game.FindObject(selectObject.Result));
            selectObject.Dispose();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.Cancel;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            IFormatProvider a = CultureInfo.CurrentCulture;
            Result = new Camera(textBox1.Text, checkBox1.Checked, new Vector3(Convert.ToSingle(textBox2.Text,a), Convert.ToSingle(textBox3.Text,a), Convert.ToSingle(textBox4.Text,a)),
                new Vector3(Convert.ToSingle(textBox6.Text,a), Convert.ToSingle(textBox7.Text,a), Convert.ToSingle(textBox5.Text,a))
                ,new Vector3(Convert.ToSingle(textBox10.Text,a), Convert.ToSingle(textBox9.Text,a), Convert.ToSingle(textBox8.Text,a)),
                Convert.ToSingle(numericUpDown1.Value), Convert.ToSingle(textBox11.Text,a), Convert.ToSingle(textBox12.Text,a));
            DialogResult = DialogResult.OK;
            Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //Open docuentation.
        }
    }
}
