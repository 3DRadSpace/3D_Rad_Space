using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using _3DRadSpaceDll;

namespace _3DRadSpace
{
    public partial class FogW : Form
    {
        public FogW()
        {
            InitializeComponent();
        }
        public FogW(Fog fog)
        {
            InitializeComponent();
            textBox1.Text = fog.Name;
            checkBox1.Checked = fog.Enabled;
            textBox2.Text = fog.FogColor.X+"";
            textBox3.Text = fog.FogColor.Y+"";
            textBox4.Text = fog.FogColor.Z+"";
            textBox5.Text = fog.FogStart + "";
            textBox6.Text = fog.FogEnd + "";
        }
        public object Result;
        private void button1_Click(object sender, EventArgs e)
        {
            ColorDialog colorD = new ColorDialog()
            {
                AnyColor = true,
                AllowFullOpen = true,
            };
            if(colorD.ShowDialog() == DialogResult.OK)
            {
                textBox2.Text = colorD.Color.R+"";
                textBox3.Text = colorD.Color.G+"";
                textBox4.Text = colorD.Color.B+"";
            }
            colorD.Dispose();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Result = new Fog(Editor.ValidateTextInput(textBox1.Text), checkBox1.Checked,
                new Microsoft.Xna.Framework.Color(
                    Convert.ToByte(Editor.ValidateNumberTextInput(textBox2.Text)),
                    Convert.ToByte(Editor.ValidateNumberTextInput(textBox3.Text)),
                    Convert.ToByte(Editor.ValidateNumberTextInput(textBox4.Text))),
                    Convert.ToSingle(Editor.ValidateNumberTextInput(textBox5.Text)),
                    Convert.ToSingle(Editor.ValidateNumberTextInput(textBox6.Text))
                );
        }

        private void button4_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Result = null;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //open docs
        }
    }
}
