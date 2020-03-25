using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using _3DRadSpaceDll.ActionScript;

namespace _3DRadSpace
{
    public partial class EventEditor : Form
    {
        public EventEditor()
        {
            Result = new List<OpCodeCall>();
            InitializeComponent();
        }

        public List<OpCodeCall> Result;

        private void EventEditor_Load(object sender, EventArgs e)
        {
            HideAll();
            for (int i=0; i <= 11;i++)
            {
                comboBox1.Items.Add(OpCodeCall.GetOpcodeText((Opcode)i));
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //No paranthesis in switch-case kinda gay
            switch (comboBox1.SelectedIndex)
            {
                case (int)Opcode.NOP:
                    HideAll();
                    break;
                case (int)Opcode.Start:
                case (int)Opcode.Stop:
                case (int)Opcode.Toggle:
                case (int)Opcode.Show:
                case (int)Opcode.Hide:
                    ShowIDField();
                    break;
                case (int)Opcode.SetPos:
                case (int)Opcode.AddPos:
                case (int)Opcode.SetRot:
                case (int)Opcode.AddRot:
                    ShowIDAndPosFields();
                    break;
                case (int)Opcode.ExecuteScript:
                    ShowScriptButton();
                    break;
                default: break;
            }
        }
        void HideAll()
        {
            label3.Visible = false;
            label4.Visible = false;
            label5.Visible = false;
            label6.Visible = false;
            textBox1.Visible = false;
            textBox2.Visible = false;
            textBox3.Visible = false;
            textBox4.Visible = false;
            button6.Visible = false;
        }
        void ShowIDField()
        {
            label3.Visible = false;
            label4.Visible = false;
            label5.Visible = true;
            label6.Visible = false;
            textBox1.Visible = false;
            textBox2.Visible = false;
            textBox3.Visible = true;
            textBox4.Visible = false;
            button6.Visible = false;
        }
        void ShowIDAndPosFields()
        {
            label3.Visible = true;
            label4.Visible = true;
            label5.Visible = true;
            label6.Visible = true;
            textBox1.Visible = true;
            textBox2.Visible = true;
            textBox3.Visible = true;
            textBox4.Visible = true;
            button6.Visible = false;
        }
        void ShowScriptButton()
        {
            label3.Visible = false;
            label4.Visible = false;
            label5.Visible = false;
            label6.Visible = false;
            textBox1.Visible = false;
            textBox2.Visible = false;
            textBox3.Visible = false;
            textBox4.Visible = false;
            button6.Visible = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }
    }
}
