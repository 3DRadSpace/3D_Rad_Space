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
using _3DRadSpaceDll.OpcodeEvent;

namespace _3DRadSpace
{
    public partial class TimerW : Form
    {
        public TimerW()
        {
            InitializeComponent();
        }
        public TimerW(_3DRadSpaceDll.Timer t)
        {
            InitializeComponent();
            textBox1.Text = t.Name;
            checkBox1.Checked = t.Enabled;
            textBox2.Text = t.Period+"";
            textBox3.Text = t.Repetitions+"";
            opcodes = t.Behiavours;
            _timer = t;
        }
        public GameObject Result;
        List<OpCodeCall> opcodes = new List<OpCodeCall>();
        _3DRadSpaceDll.Timer _timer;

        private void button3_Click(object sender, EventArgs e)
        {
            Result = new _3DRadSpaceDll.Timer()
            {
                Name = Editor.ValidateTextInput(textBox1.Text),
                Enabled = checkBox1.Checked,
                Period = Convert.ToUInt32(Editor.ValidateNumberTextInput(textBox2.Text)),
                Repetitions = Convert.ToUInt32(Editor.ValidateNumberTextInput(textBox3.Text)),
                Behiavours = opcodes
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

        private void button1_Click_1(object sender, EventArgs e)
        {
            EventEditor eventEditor;
            if(_timer != null) eventEditor = new EventEditor(_timer.Behiavours,_timer.SelectedObjects);
            else eventEditor = new EventEditor(null,null);

            if(eventEditor.ShowDialog() == DialogResult.OK)
            {
                opcodes = eventEditor.Result;
            }
            eventEditor.Dispose();
        }
    }
}
