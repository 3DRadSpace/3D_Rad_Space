using _3DRadSpaceDll;
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
    public partial class CounterW : Form
    {
        public CounterW()
        {
            InitializeComponent();
        }
        public CounterW(Counter counter)
        {
            InitializeComponent();
            textBox1.Text = counter.Name;
            textBox2.Text = counter.InitialValue+"";
            textBox3.Text = counter.Increment+"";
            textBox4.Text = counter.File;
        }

        public GameObject Result;

        private void button2_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //open docs
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            float i = Convert.ToSingle(textBox2.Text, Main.CultureInfo);
            Result = new Counter(i)
            {
                Name = textBox1.Text,
                Enabled = checkBox1.Checked,
                Value = i,
                Increment = Convert.ToSingle(textBox3.Text, Main.CultureInfo),
                File = textBox4.Text
            };
        }
    }
}
