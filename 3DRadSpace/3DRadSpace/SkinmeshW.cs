using System;
using System.IO;
using System.Windows.Forms;
using _3DRadSpaceDll;

namespace _3DRadSpace
{
    public partial class SkinmeshW : Form
    {
        public object Result;
        public SkinmeshW(Skinmesh sk)
        {

        }
        public SkinmeshW()
        {
            InitializeComponent();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Skinmesh r = new Skinmesh("", false, "");
            Result = r;
            Close();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            //open docs
        }

        private void button6_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            listBox2.Items.Clear();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            int index = listBox1.SelectedIndex;
            listBox1.Items.RemoveAt(index);
            listBox2.Items.RemoveAt(index);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //open parameters wizard
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog openf = new OpenFileDialog()
            {
                Title = "Find a shader...",
                Filter = "Shaders (*.fx;*fxo)|*.fx;*.fxo)"
            };
            if( openf.ShowDialog() == DialogResult.OK)
            {

            }
            openf.Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openmesh = new OpenFileDialog()
            {
                Title = "Find a 3D Model for the Skinmesh object",
                Filter = "Compiled XNB mesh resource(*.xnb)|*.xnb"
            };
            if (openmesh.ShowDialog() == DialogResult.OK)
            {
                
            }
            openmesh.Dispose();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if(radioButton1.Checked == true)
            {
                radioButton2.Checked = false;
                radioButton3.Checked = false;
            }
        }
        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton2.Checked == true)
            {
                radioButton1.Checked = false;
                radioButton3.Checked = false;
            }
        }
        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton3.Checked == true)
            {
                radioButton1.Checked = false;
                radioButton2.Checked = false;
            }
        }
    }
}
