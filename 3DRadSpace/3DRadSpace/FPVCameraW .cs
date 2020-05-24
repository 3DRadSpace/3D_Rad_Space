using System;
using Microsoft.Xna.Framework;
using System.Windows.Forms;
using _3DRadSpaceDll;
using System.Globalization;
using System.Collections.Generic;

namespace _3DRadSpace
{
    public partial class FPVCameraW : Form
    {
        public FPVCameraW()
        {
            Result = null;
            Behiavour = new List<ObjectBehiavour>();
            InitializeComponent();
        }
        public FPVCameraW(FPVCamera c)
        {
            InitializeComponent();
            textBox1.Text = c.Name;
            checkBox1.Checked = c.Enabled;
            textBox2.Text = ""+c.Position.X);
            textBox3.Text = ""+c.Position.Y);
            textBox4.Text = ""+c.Position.Z);
            textBox7.Text = ""+c.Rotation.X);
            textBox6.Text = ""+c.Rotation.Y);
            textBox10.Text = ""+c.CameraRotation.X);
            textBox9.Text = ""+c.CameraRotation.Y);
            textBox8.Text = ""+c.CameraRotation.Z);
            numericUpDown1.Value = (decimal)c.GetFOVDegrees();
            textBox11.Text = ""+c.MinDrawDist);
            textBox12.Text = ""+c.MaxDrawDist);
            comboBox1.SelectedItem = EventOnKeyW.GetKeyFromListBox_rev(c.Forward);
            comboBox2.SelectedItem = EventOnKeyW.GetKeyFromListBox_rev(c.Backward);
            comboBox3.SelectedItem = EventOnKeyW.GetKeyFromListBox_rev(c.Right);
            comboBox4.SelectedItem = EventOnKeyW.GetKeyFromListBox_rev(c.Left);
            textBox5.Text = ""+c.Sensibility);
            textBox13.Text = ""+c.MovementSpeed);
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
            Result = new FPVCamera()
            {
                Name = textBox1.Text,
                Enabled = checkBox1.Checked,
                Position = new Vector3(Convert.ToSingle(textBox2.Text),
                                        Convert.ToSingle(textBox3.Text),
                                        Convert.ToSingle(textBox4.Text)),
                CamScreenCoords = new Vector2(Convert.ToSingle(textBox7.Text),
                                        Convert.ToSingle(textBox6.Text)),
                CameraRotation = new Vector3(Convert.ToSingle(textBox10.Text),
                                            Convert.ToSingle(textBox9.Text),
                                            Convert.ToSingle(textBox8.Text)),
                FOV = MathHelper.ToRadians((float)numericUpDown1.Value),
                MinDrawDist = Convert.ToSingle(textBox11.Text),
                MaxDrawDist = Convert.ToSingle(textBox12.Text),
                Sensibility = Convert.ToSingle(textBox5.Text),
                MovementSpeed = Convert.ToSingle(textBox13.Text),
                Forward = EventOnKeyW.GetKeyFromListBox((string)comboBox1.SelectedItem),
                Backward = EventOnKeyW.GetKeyFromListBox((string)comboBox2.SelectedItem),
                Right = EventOnKeyW.GetKeyFromListBox((string)comboBox3.SelectedItem),
                Left = EventOnKeyW.GetKeyFromListBox((string)comboBox4.SelectedItem)
            };
            DialogResult = DialogResult.OK;
            Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //Open docuentation.
        }

        private void FPVCameraW_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedIndex = 0;
            comboBox2.SelectedIndex = 1;
            comboBox3.SelectedIndex = 3;
            comboBox4.SelectedIndex = 2;
        }
    }
}
