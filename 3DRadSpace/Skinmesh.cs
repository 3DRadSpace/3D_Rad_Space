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
            File.WriteAllText(@"lastobj.data", "Skinmesh "+checkBox1.Checked+" "+textBox2.Text+" "+textBox3.Text+" "+textBox4.Text+" "+textBox5.Text+" "+textBox6.Text+" "+textBox7.Text+" "+textBox8.Text+" "+domainUpDown1.Text);
            Close();
        }
    }
}
