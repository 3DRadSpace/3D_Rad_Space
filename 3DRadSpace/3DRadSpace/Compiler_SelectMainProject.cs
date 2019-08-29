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
    public partial class Compiler_SelectMainProject : Form
    {
        public Compiler_SelectMainProject()
        {
            InitializeComponent();
        }
        public string Result;
        private void Compiler_SelectMainProject_Load(object sender, EventArgs e)
        {
            pictureBox1.Image = SystemIcons.Information.ToBitmap();
            //listBox1.Items.Clear();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (Result == null) return;
            DialogResult = DialogResult.OK;
            Close();
        }

        private void Compiler_SelectMainProject_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (DialogResult == DialogResult.Cancel) return;
            if (Result == null) e.Cancel = true;
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(listBox1.SelectedIndex != -1)
            Result = listBox1.Items[listBox1.SelectedIndex].ToString();
        }
    }
}
