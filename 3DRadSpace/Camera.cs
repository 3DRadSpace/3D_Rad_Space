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
        public string OBJR = null;
        private void button4_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "";
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "Camera " + _3DRadSpace_EditorClass.ValidateText( textBox1.Text) + " " + checkBox1.Checked.ToString() + " " +  _3DRadSpace_EditorClass.ValidateNumberBox(textBox2.Text) + " " + _3DRadSpace_EditorClass.ValidateNumberBox(textBox3.Text) + " " + _3DRadSpace_EditorClass.ValidateNumberBox(textBox4.Text) + " " + _3DRadSpace_EditorClass.ValidateNumberBox(textBox5.Text) + " " + _3DRadSpace_EditorClass.ValidateNumberBox(textBox6.Text) + " " + _3DRadSpace_EditorClass.ValidateNumberBox(textBox7.Text) + " "+ numericUpDown1.Value.ToString() + " "+ checkBox2.Checked.ToString() +" "+ _3DRadSpace_EditorClass.ValidateNumberBox(textBox8.Text) + " "+ OBJR;
            DialogResult = DialogResult.OK;
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

        private void Camera_FormClosed(object sender, FormClosedEventArgs e)
        {
        }
    }
}
