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
    public partial class SoundEffectW : Form
    {
        public object Result;
        public SoundEffectW()
        {
            InitializeComponent();
        }
        public SoundEffectW(_3DRadSpaceDll.SoundEffect sound)
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
            Result = new _3DRadSpaceDll.SoundEffect(textBox1.Text, checkBox1.Checked, textBox2.Text, trackBar1.Value)
            {
                Picth = trackBar2.Value,
                Pan = trackBar3.Value,
            };
            Close();
        }
    }
}
