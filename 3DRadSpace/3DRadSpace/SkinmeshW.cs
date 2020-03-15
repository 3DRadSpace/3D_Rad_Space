using System;
using System.IO;
using System.Windows.Forms;
using _3DRadSpaceDll;
using Microsoft.Xna.Framework;

namespace _3DRadSpace
{
    public partial class SkinmeshW : Form
    {
        public GameObject Result;
        public SkinmeshW(Skinmesh sk)
        {
            InitializeComponent();
            textBox1.Text = sk.Name;
            checkBox1.Checked = sk.Enabled;
            textBox2.Text = sk.Resource;
            textBox3.Text = ""+sk.Position.X;
            textBox4.Text = ""+sk.Position.Y;
            textBox5.Text = ""+sk.Position.Z;
            textBox8.Text = ""+sk.Rotation.X;
            textBox7.Text = ""+sk.Rotation.Y;
            textBox6.Text = ""+sk.Rotation.Z;
            textBox11.Text = "" + sk.Scale.X;
            textBox10.Text = "" + sk.Scale.Y;
            textBox9.Text = "" + sk.Scale.Z;
            textBox12.Text = sk.BoundingSphere.Radius+"";
            textBox13.Text = sk.BoundingBox.Min.X+"";
            textBox14.Text = sk.BoundingBox.Min.Y+"";
            textBox15.Text = sk.BoundingBox.Min.Z+"";
            textBox18.Text = sk.BoundingBox.Max.X + "";
            textBox17.Text = sk.BoundingBox.Max.Y + "";
            textBox16.Text = sk.BoundingBox.Max.Z + "";
        }
        public SkinmeshW()
        {
            InitializeComponent();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Skinmesh r = new Skinmesh(Editor.ValidateTextInput(textBox1.Text) , checkBox1.Checked, textBox2.Text,
                new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox3.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox4.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox5.Text)))
               ,new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox8.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox7.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox6.Text)))
               ,new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox11.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox10.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox9.Text)))
                ,checkBox2.Checked,new BoundingBox(
                    new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox13.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox14.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox15.Text)))
                    ,new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox18.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox17.Text)), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox16.Text))))
                ,new BoundingSphere(Vector3.Zero,Convert.ToSingle(Editor.ValidateNumberTextInput(textBox12.Text))));
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
