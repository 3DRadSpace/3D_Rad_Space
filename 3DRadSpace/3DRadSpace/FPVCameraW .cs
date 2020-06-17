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
            textBox2.Text = c.Position.X.ToString(Main.CultureInfo);
            textBox3.Text = c.Position.Y.ToString( Main.CultureInfo);
            textBox4.Text = c.Position.Z.ToString( Main.CultureInfo);
            textBox7.Text = c.Rotation.X.ToString( Main.CultureInfo);
            textBox6.Text = c.Rotation.Y.ToString( Main.CultureInfo);
            textBox10.Text = c.CameraRotation.X.ToString( Main.CultureInfo);
            textBox9.Text = c.CameraRotation.Y.ToString( Main.CultureInfo);
            textBox8.Text = c.CameraRotation.Z.ToString( Main.CultureInfo);
            numericUpDown1.Value = (decimal)c.GetFOVDegrees();
            textBox11.Text = c.MinDrawDist.ToString( Main.CultureInfo);
            textBox12.Text = c.MaxDrawDist.ToString( Main.CultureInfo);
            comboBox1.SelectedItem = EventOnKeyW.GetKeyFromListBox_rev(c.Forward);
            comboBox2.SelectedItem = EventOnKeyW.GetKeyFromListBox_rev(c.Backward);
            comboBox3.SelectedItem = EventOnKeyW.GetKeyFromListBox_rev(c.Right);
            comboBox4.SelectedItem = EventOnKeyW.GetKeyFromListBox_rev(c.Left);
            textBox5.Text = c.Sensibility.ToString( Main.CultureInfo);
            textBox13.Text = c.MovementSpeed.ToString( Main.CultureInfo);
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
                Position = new Vector3(Convert.ToSingle(textBox2.Text, Main.CultureInfo),
                                        Convert.ToSingle(textBox3.Text, Main.CultureInfo),
                                        Convert.ToSingle(textBox4.Text,Main.CultureInfo)),
                CamScreenCoords = new Vector2(Convert.ToSingle(textBox7.Text, Main.CultureInfo),
                                        Convert.ToSingle(textBox6.Text, Main.CultureInfo)),
                CameraRotation = new Vector3(Convert.ToSingle(textBox10.Text, Main.CultureInfo),
                                            Convert.ToSingle(textBox9.Text, Main.CultureInfo),
                                            Convert.ToSingle(textBox8.Text, Main.CultureInfo)),
                FOV = MathHelper.ToRadians((float)numericUpDown1.Value),
                MinDrawDist = Convert.ToSingle(textBox11.Text, Main.CultureInfo),
                MaxDrawDist = Convert.ToSingle(textBox12.Text, Main.CultureInfo),
                Sensibility = Convert.ToSingle(textBox5.Text, Main.CultureInfo),
                MovementSpeed = Convert.ToSingle(textBox13.Text, Main.CultureInfo),

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
