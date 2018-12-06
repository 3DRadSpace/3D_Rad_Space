using System;
using System.IO;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class Skinmesh : Form
    {
        public Skinmesh()
        {
            InitializeComponent();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "";
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Game1.LastObj = "Skinmesh "+ _3DRadSpace_EditorClass.ValidateText(textBox1.Text)+" "+checkBox1.Checked+" "+ _3DRadSpace_EditorClass.ValidateNumberBox(textBox2.Text)+" "+ _3DRadSpace_EditorClass.ValidateNumberBox(textBox3.Text)+" "+ _3DRadSpace_EditorClass.ValidateNumberBox(textBox4.Text)+" "+ _3DRadSpace_EditorClass.ValidateNumberBox(textBox5.Text)+" "+ _3DRadSpace_EditorClass.ValidateNumberBox(textBox6.Text)+" "+ _3DRadSpace_EditorClass.ValidateNumberBox(textBox7.Text)+" "+domainUpDown1.SelectedIndex+" "+textBox8.Text;
            DialogResult = DialogResult.OK;
            Close();
        }

        private void Skinmesh_Load(object sender, EventArgs e)
        {
            domainUpDown1.SelectedIndex = 0;
        }

        private void Skinmesh_FormClosed(object sender, FormClosedEventArgs e)
        {

        }
    }
}
