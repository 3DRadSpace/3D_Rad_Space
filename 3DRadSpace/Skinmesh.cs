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
            File.WriteAllText(@"lastobj.data", " ");
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            File.WriteAllText(@"lastobj.data", "Skinmesh "+textBox1.Text+" "+checkBox1.Checked+" "+textBox2.Text+" "+textBox3.Text+" "+textBox4.Text+" "+textBox5.Text+" "+textBox6.Text+" "+textBox7.Text+" "+domainUpDown1.SelectedIndex+" "+textBox8.Text);
            Close();
        }

        private void Skinmesh_Load(object sender, EventArgs e)
        {
            domainUpDown1.SelectedIndex = 0;
        }
    }
}
