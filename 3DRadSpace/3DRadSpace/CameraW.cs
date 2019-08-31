using System;
using Microsoft.Xna.Framework;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class CameraW : Form
    {
        public CameraW()
        {
            InitializeComponent();
        }
        object Result;
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
           // Result = new Camera(textBox1.Text,checkBox1.Checked,new Microsoft.Xna.Framework.Vector3())
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //Open docuentation.
        }
    }
}
