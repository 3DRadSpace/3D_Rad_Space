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
    public partial class EventOnKeyW : Form
    {
        public EventOnKeyW()
        {
            InitializeComponent();
        }
        GameObject Result;
        private void EventOnKeyW_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedIndex = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Result = new EventOnKey(Editor.ValidateTextInput(textBox1.Text), checkBox1.Checked, new KeyInput(GetKeyFromListBox(), GetInputStateFromComboBox()), Convert.ToUInt32(Editor.ValidateNumberTextInput(textBox2.Text)));
            Close();
        }
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

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //open docs...
        }
    }
}
