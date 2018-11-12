using System;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace _3DRadSpace
{
    public partial class Camera : Form
    {
        public Camera()
        {
            InitializeComponent();
        }
        public bool result = false;
        public string OBJR = null;
        private void button4_Click(object sender, EventArgs e)
        {
            File.WriteAllText(@"lastobj.data", " ");
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string ObjData = "Camera " + textBox1.Text + " " + checkBox1.Checked.ToString() + " " + textBox2.Text + " " + textBox3.Text + " " + textBox4.Text + " " + textBox5.Text + " " + textBox6.Text + " " + textBox7.Text + " "+ numericUpDown1.Value.ToString() + " "+ checkBox2.Checked.ToString() +" "+textBox8.Text+ " "+ OBJR;
            File.WriteAllText(@"lastobj.data",ObjData);
            result = true;
            Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            File.WriteAllText("OBJT.data","Camera");
            OBJR ObjectRelations = new OBJR();
            ObjectRelations.ShowDialog();
            OBJR = File.ReadAllText("relation.data");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Process.Start(@"Help Files/Camera.rtf");
        }
    }
}
