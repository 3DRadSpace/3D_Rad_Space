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
    public partial class SoundEffectW : Form
    {
        public object Result;
        public SoundEffectW()
        {
            InitializeComponent();
        }
        public SoundEffectW(SoundEffect sound)
        {
            InitializeComponent();
            textBox1.Text = sound.Name;
            textBox2.Text = sound.Resource;
            checkBox1.Checked = sound.Enabled;
            trackBar1.Value = (int)sound.Volume*100;
            trackBar2.Value = (int)sound.Picth*100;
        }


        private void button3_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Result = new SoundEffect(textBox1.Text, checkBox1.Checked, textBox2.Text, trackBar1.Value)
            {
                Picth = trackBar2.Value / 100,
                Pan = trackBar3.Value / 100,
            };
            Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //open docs
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            //radioButton2.Checked = false;
            //radioButton3.Checked = false;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            //radioButton1.Checked = false;
            //radioButton3.Checked = false;
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
           //radioButton1.Checked = false;
           //radioButton2.Checked = false;
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label4.Text = trackBar1.Value + "";
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            label5.Text = trackBar2.Value / 100f + "";
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            label7.Text = trackBar3.Value / 100f + "";
        }

        private void SoundEffectW_Load(object sender, EventArgs e)
        {
            trackBar1_Scroll(null,null);
            trackBar2_Scroll(null,null);
            trackBar3_Scroll(null,null);
        }
    }
}
