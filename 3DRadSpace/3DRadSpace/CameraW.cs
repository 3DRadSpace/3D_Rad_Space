using System;
using Microsoft.Xna.Framework;
using System.Windows.Forms;
using _3DRadSpaceDll;
using System.Globalization;
using System.Collections.Generic;

namespace _3DRadSpace
{
    public partial class CameraW : Form
    {
        public CameraW()
        {
            Result = null;
            Behiavour = new List<ObjectBehiavour>();
            InitializeComponent();
        }
        public CameraW(Camera c)
        {
            InitializeComponent();
            textBox1.Text = c.Name;
            checkBox1.Checked = c.Enabled;
            textBox2.Text = c.Position.X.ToString();
            textBox3.Text = c.Position.Y.ToString();
            textBox4.Text = c.Position.Z.ToString();
            textBox7.Text = c.Rotation.X.ToString();
            textBox6.Text = c.Rotation.Y.ToString();
            textBox5.Text = c.Rotation.Z.ToString();
            textBox10.Text = c.CameraRotation.X.ToString();
            textBox9.Text = c.CameraRotation.Y.ToString();
            textBox8.Text = c.CameraRotation.Z.ToString();
            numericUpDown1.Value = (decimal)c.GetFOVDegrees();
            textBox11.Text = c.MinDrawDist.ToString();
            textBox12.Text = c.MaxDrawDist.ToString();
            Behiavour = c.Behiavours;
            UpdateList();
        }
        public object Result;
        public List<ObjectBehiavour> Behiavour;
        private void button1_Click(object sender, EventArgs e)
        {
            SelectObjectDialog selectObject = new SelectObjectDialog();
            selectObject.ShowDialog();
            Behiavour.Add(new ObjectBehiavour(selectObject.Result));
            UpdateList();
            selectObject.Dispose();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.Cancel;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            IFormatProvider a = CultureInfo.CurrentCulture;
            Result = new Camera(Editor.ValidateTextInput(textBox1.Text), checkBox1.Checked, new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox2.Text), a), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox3.Text), a), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox4.Text), a)),
                new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox7.Text), a), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox6.Text), a), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox5.Text), a))
                , new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox10.Text), a), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox9.Text), a), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox8.Text), a)),
                Convert.ToSingle(numericUpDown1.Value), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox11.Text), a), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox12.Text), a))
            {
                Behiavours = Behiavour
            };
            DialogResult = DialogResult.OK;
            Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //Open docuentation.
        }
        void UpdateList()
        {
            listBox1.Items.Clear();
            for(int i =0; i < Behiavour.Count;i++)
            {
                listBox1.Items.Add(_3DRadSpaceDll.Game.GameObjects[Behiavour[i].ObjectID] + " ["+ GetBehiavourText(Behiavour[i].BehiavourID)+ "]");
            }
        }
        string GetBehiavourText(int id)
        {
            switch(id)
            {
                case 1: return "Chase";
                case 2: return "Look-At";
                default: return "Ignore";
            }
        }

        private void listBox1_Click(object sender, EventArgs e)
        {
            int id = Behiavour[listBox1.SelectedIndex].BehiavourID;
            id++;
            if (id > 3) id = 0;
            // 0 - default
            // 1 - chase
            // 2 - look-at
            Behiavour[listBox1.SelectedIndex].BehiavourID = id;
            UpdateList();
        }
    }
}
