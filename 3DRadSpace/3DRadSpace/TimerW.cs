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
    public partial class TimerW : Form
    {
        public TimerW()
        {
            InitializeComponent();
        }
        public GameObject Result;
        public _3DRadSpaceDll.ActionScript.OpCodeCall[] Event;
        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            Result = new _3DRadSpaceDll.Timer()
            {
                Name = Editor.ValidateTextInput(textBox1.Text),
                Enabled = checkBox1.Checked,
                Period = Convert.ToUInt32(Editor.ValidateNumberTextInput(textBox2.Text)),
                Repetitions = Convert.ToUInt32(Editor.ValidateNumberTextInput(textBox3.Text)),
            };
            DialogResult = DialogResult.OK;
            Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Result = null;
            Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            //open docs...
        }
    }
}
