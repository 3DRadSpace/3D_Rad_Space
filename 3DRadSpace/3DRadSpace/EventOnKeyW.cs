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
    public partial class EventOnKeyW : Form
    {
        public EventOnKeyW()
        {
            InitializeComponent();
        }
        public EventOnKeyW(EventOnKey eok)
        {
            InitializeComponent();
            textBox1.Text = eok.Name;
            checkBox1.Checked = eok.Enabled;
            for(int i =0; i < listBox1.Items.Count;i++)
            {
                if (GetKeyFromListBox_rev(eok.Key.Key) == (string)listBox1.Items[i])
                {
                    listBox1.SelectedIndex = i;
                    break;
                }
            }
            comboBox1.SelectedIndex = (int)eok.Key.State;
            textBox2.Text = "" + eok.HoldingTime;
            _eok = eok;
        }
        public GameObject Result;
        List<OpCodeCall> opcodes = new List<OpCodeCall>();
        EventOnKey _eok;
        private void EventOnKeyW_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedIndex = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            EventOnKey k = new EventOnKey(Editor.ValidateTextInput(textBox1.Text), checkBox1.Checked, new KeyInput(GetKeyFromListBox(), GetInputStateFromComboBox()), Convert.ToUInt32(Editor.ValidateNumberTextInput(textBox2.Text)));
            k.Behiavours = opcodes;
            Result = k;
            Close();
        }

        /// <summary>
        /// This is one of the most cancerous pieces of code that exist in 3DRadSpace.
        /// </summary>
        /// <returns></returns>
        Microsoft.Xna.Framework.Input.Keys GetKeyFromListBox()
        {
            switch(listBox1.SelectedItem)
            {
                case "Q": return Microsoft.Xna.Framework.Input.Keys.Q;
                case "W": return Microsoft.Xna.Framework.Input.Keys.W;
                case "E": return Microsoft.Xna.Framework.Input.Keys.E;
                case "R": return Microsoft.Xna.Framework.Input.Keys.R;
                case "T": return Microsoft.Xna.Framework.Input.Keys.T;
                case "Y": return Microsoft.Xna.Framework.Input.Keys.Y;
                case "U": return Microsoft.Xna.Framework.Input.Keys.U;
                case "I": return Microsoft.Xna.Framework.Input.Keys.I;
                case "O": return Microsoft.Xna.Framework.Input.Keys.O;
                case "P": return Microsoft.Xna.Framework.Input.Keys.P;
                case "A": return Microsoft.Xna.Framework.Input.Keys.A;
                case "S": return Microsoft.Xna.Framework.Input.Keys.S;
                case "D": return Microsoft.Xna.Framework.Input.Keys.D;
                case "F": return Microsoft.Xna.Framework.Input.Keys.F;
                case "G": return Microsoft.Xna.Framework.Input.Keys.G;
                case "H": return Microsoft.Xna.Framework.Input.Keys.H;
                case "J": return Microsoft.Xna.Framework.Input.Keys.J;
                case "K": return Microsoft.Xna.Framework.Input.Keys.K;
                case "L": return Microsoft.Xna.Framework.Input.Keys.L;
                case "Z": return Microsoft.Xna.Framework.Input.Keys.Z;
                case "X": return Microsoft.Xna.Framework.Input.Keys.X;
                case "C": return Microsoft.Xna.Framework.Input.Keys.C;
                case "V": return Microsoft.Xna.Framework.Input.Keys.V;
                case "B": return Microsoft.Xna.Framework.Input.Keys.B;
                case "N": return Microsoft.Xna.Framework.Input.Keys.N;
                case "M": return Microsoft.Xna.Framework.Input.Keys.M;
                case "1": return Microsoft.Xna.Framework.Input.Keys.D1;
                case "2": return Microsoft.Xna.Framework.Input.Keys.D2;
                case "3": return Microsoft.Xna.Framework.Input.Keys.D3;
                case "4": return Microsoft.Xna.Framework.Input.Keys.D4;
                case "5": return Microsoft.Xna.Framework.Input.Keys.D5;
                case "6": return Microsoft.Xna.Framework.Input.Keys.D6;
                case "7": return Microsoft.Xna.Framework.Input.Keys.D7;
                case "8": return Microsoft.Xna.Framework.Input.Keys.D8;
                case "9": return Microsoft.Xna.Framework.Input.Keys.D9;
                case "0": return Microsoft.Xna.Framework.Input.Keys.D0;
                case "Left Shift": return Microsoft.Xna.Framework.Input.Keys.LeftShift;
                case "Right Shift": return Microsoft.Xna.Framework.Input.Keys.RightShift;
                case "Left Ctrl": return Microsoft.Xna.Framework.Input.Keys.LeftControl;
                case "Right Ctrl": return Microsoft.Xna.Framework.Input.Keys.RightControl;
                case "Tab": return Microsoft.Xna.Framework.Input.Keys.Tab;
                case "Up Arrow": return Microsoft.Xna.Framework.Input.Keys.Up;
                case "Down Arrow": return Microsoft.Xna.Framework.Input.Keys.Down;
                case "Left Arrow": return Microsoft.Xna.Framework.Input.Keys.Left;
                case "Right Arrow": return Microsoft.Xna.Framework.Input.Keys.Right;
                case "Enter": return Microsoft.Xna.Framework.Input.Keys.Enter;
                case "Space": return Microsoft.Xna.Framework.Input.Keys.Space;
                default: return Microsoft.Xna.Framework.Input.Keys.None;
            }
        }
        KeyInputType GetInputStateFromComboBox()
        {
            switch(comboBox1.Text)
            {
                case "Released": return KeyInputType.Released;
                case "Pressed": return KeyInputType.Pressed;
                case "Holding": return KeyInputType.Holding;
                default: return KeyInputType.Released;
            }
        }

        string GetKeyFromListBox_rev(Microsoft.Xna.Framework.Input.Keys arg)
        {
            switch (arg)
            {
                case Microsoft.Xna.Framework.Input.Keys.Q: return "Q";
                case Microsoft.Xna.Framework.Input.Keys.W: return "W";
                case  Microsoft.Xna.Framework.Input.Keys.E: return "E";
                case  Microsoft.Xna.Framework.Input.Keys.R: return "R";
                case  Microsoft.Xna.Framework.Input.Keys.T: return "T";
                case  Microsoft.Xna.Framework.Input.Keys.Y: return "Y";
                case  Microsoft.Xna.Framework.Input.Keys.U: return "U";
                case  Microsoft.Xna.Framework.Input.Keys.I: return "I";
                case  Microsoft.Xna.Framework.Input.Keys.O: return "O";
                case  Microsoft.Xna.Framework.Input.Keys.P: return "P";
                case  Microsoft.Xna.Framework.Input.Keys.A: return "A";
                case  Microsoft.Xna.Framework.Input.Keys.S: return "S";
                case  Microsoft.Xna.Framework.Input.Keys.D: return "D";
                case  Microsoft.Xna.Framework.Input.Keys.F: return "F";
                case Microsoft.Xna.Framework.Input.Keys.G: return "G";
                case Microsoft.Xna.Framework.Input.Keys.H: return "H";
                case Microsoft.Xna.Framework.Input.Keys.J: return "J";
                case Microsoft.Xna.Framework.Input.Keys.K: return "K";
                case Microsoft.Xna.Framework.Input.Keys.L: return "L";
                case Microsoft.Xna.Framework.Input.Keys.Z: return "Z";
                case Microsoft.Xna.Framework.Input.Keys.X: return "X";
                case Microsoft.Xna.Framework.Input.Keys.C: return "C";
                case Microsoft.Xna.Framework.Input.Keys.V: return "V";
                case Microsoft.Xna.Framework.Input.Keys.B: return "B";
                case Microsoft.Xna.Framework.Input.Keys.N: return "N";
                case Microsoft.Xna.Framework.Input.Keys.M: return "M";
                case Microsoft.Xna.Framework.Input.Keys.D1: return "1";
                case Microsoft.Xna.Framework.Input.Keys.D2: return "2";
                case Microsoft.Xna.Framework.Input.Keys.D3: return "3";
                case Microsoft.Xna.Framework.Input.Keys.D4: return "4";
                case Microsoft.Xna.Framework.Input.Keys.D5: return "5";
                case Microsoft.Xna.Framework.Input.Keys.D6: return "6";
                case Microsoft.Xna.Framework.Input.Keys.D7: return "7";
                case Microsoft.Xna.Framework.Input.Keys.D8: return "8";
                case Microsoft.Xna.Framework.Input.Keys.D9: return "9";
                case Microsoft.Xna.Framework.Input.Keys.D0: return "0";
                case Microsoft.Xna.Framework.Input.Keys.LeftShift: return "Left Shift";
                case Microsoft.Xna.Framework.Input.Keys.RightShift: return "Right Shift";
                case Microsoft.Xna.Framework.Input.Keys.LeftControl: return "Left Ctrl";
                case Microsoft.Xna.Framework.Input.Keys.RightControl: return "Roght Ctrl";
                case Microsoft.Xna.Framework.Input.Keys.Tab: return "Tab";
                case Microsoft.Xna.Framework.Input.Keys.Up: return "Up Arrow";
                case Microsoft.Xna.Framework.Input.Keys.Down: return "Down Arrow";
                case Microsoft.Xna.Framework.Input.Keys.Left: return "Left Arrow";
                case Microsoft.Xna.Framework.Input.Keys.Right: return "Right Arrow";
                case Microsoft.Xna.Framework.Input.Keys.Enter: return "Enter";
                case Microsoft.Xna.Framework.Input.Keys.Space: return "Space";
                default: return null;
            }
        }
        string GetInputStateFromComboBox_Rev(KeyInputType arg)
        {
            switch (arg)
            {
                case KeyInputType.Released: return "Released";
                case KeyInputType.Pressed: return "Pressed";
                case KeyInputType.Holding: return "Holding";
                default: return "Released";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //open docs...
        }

        private void button4_Click(object sender, EventArgs e)
        {
            EventEditor editor;
            if(_eok != null) editor = new EventEditor(_eok.Behiavours,_eok.SelectedObjects);
            else editor = new EventEditor(null,null);
            if(editor.ShowDialog() == DialogResult.OK)
            {
                opcodes = editor.Result;
            }
            editor.Dispose();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex != (int)KeyInputType.Holding) textBox2.Text = "0";
        }
    }
}
