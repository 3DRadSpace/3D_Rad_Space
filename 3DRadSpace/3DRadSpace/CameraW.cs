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
            textBox2.Text = c.Position.X.ToString("0.0",Program.CultureInfo);
            textBox3.Text = c.Position.Y.ToString("0.0", Program.CultureInfo);
            textBox4.Text = c.Position.Z.ToString("0.0", Program.CultureInfo);
            textBox7.Text = c.Rotation.X.ToString("0.0", Program.CultureInfo);
            textBox6.Text = c.Rotation.Y.ToString("0.0", Program.CultureInfo);
            textBox5.Text = c.Rotation.Z.ToString("0.0", Program.CultureInfo);
            textBox10.Text = c.CameraRotation.X.ToString("0.0", Program.CultureInfo);
            textBox9.Text = c.CameraRotation.Y.ToString("0.0", Program.CultureInfo);
            textBox8.Text = c.CameraRotation.Z.ToString("0.0", Program.CultureInfo);
            numericUpDown1.Value = (decimal)c.GetFOVDegrees();
            textBox11.Text = c.MinDrawDist.ToString("0.0", Program.CultureInfo);
            textBox12.Text = c.MaxDrawDist.ToString("0.0", Program.CultureInfo);
            Behiavour = c.Behiavours;
            UpdateList();
        }
        public GameObject Result;
        public List<ObjectBehiavour> Behiavour;

        private void button6_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.Cancel;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Result = new Camera()
            {
                Name = Editor.ValidateTextInput(textBox1.Text),
                Enabled = checkBox1.Checked,
                Position = new Vector3()
                {
                    X = Convert.ToSingle(Editor.ValidateNumberTextInput(textBox2.Text), Program.CultureInfo),
                    Y = Convert.ToSingle(Editor.ValidateNumberTextInput(textBox3.Text), Program.CultureInfo),
                    Z = Convert.ToSingle(Editor.ValidateNumberTextInput(textBox4.Text), Program.CultureInfo)
                },
                Rotation = new Vector3()
                {
                    X = Convert.ToSingle(Editor.ValidateNumberTextInput(textBox7.Text), Program.CultureInfo),
                    Y = Convert.ToSingle(Editor.ValidateNumberTextInput(textBox6.Text), Program.CultureInfo),
                    Z = Convert.ToSingle(Editor.ValidateNumberTextInput(textBox5.Text), Program.CultureInfo)
                },
                CameraRotation = new Vector3()
                {
                    X = Convert.ToSingle(Editor.ValidateNumberTextInput(textBox10.Text)),
                    Y = Convert.ToSingle(Editor.ValidateNumberTextInput(textBox9.Text)),
                    Z = Convert.ToSingle(Editor.ValidateNumberTextInput(textBox8.Text))
                },
                FOV = (float)numericUpDown1.Value,
                MinDrawDist = Convert.ToSingle(Editor.ValidateNumberTextInput(textBox11.Text)),
                MaxDrawDist = Convert.ToSingle(Editor.ValidateNumberTextInput(textBox12.Text)),
                Behiavours = Behiavour,
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
            if (listBox1.SelectedIndex == -1) return;
            int obj = Behiavour[listBox1.SelectedIndex].ObjectID;
            int id = Behiavour[listBox1.SelectedIndex].BehiavourID;
            id++;
            if (id > 3) id = 0;
            // 0 - default
            // 1 - chase
            // 2 - look-at
            Behiavour[listBox1.SelectedIndex] = new ObjectBehiavour(obj, id);
            UpdateList();
        }

        private void CameraW_Load(object sender, EventArgs e)
        {

        }
    }
}
