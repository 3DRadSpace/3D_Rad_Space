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
        public FPVCameraW(Camera c)
        {
            InitializeComponent();
            textBox1.Text = c.Name;
            checkBox1.Checked = c.Enabled;
            textBox2.Text = SafeConverter.FloatToString(c.Position.X);
            textBox3.Text = SafeConverter.FloatToString(c.Position.Y);
            textBox4.Text = SafeConverter.FloatToString(c.Position.Z);
            textBox7.Text = SafeConverter.FloatToString(c.Rotation.X);
            textBox6.Text = SafeConverter.FloatToString(c.Rotation.Y);
            textBox10.Text = SafeConverter.FloatToString(c.CameraRotation.X);
            textBox9.Text = SafeConverter.FloatToString(c.CameraRotation.Y);
            textBox8.Text = SafeConverter.FloatToString(c.CameraRotation.Z);
            numericUpDown1.Value = (decimal)c.GetFOVDegrees();
            textBox11.Text = SafeConverter.FloatToString(c.MinDrawDist);
            textBox12.Text = SafeConverter.FloatToString(c.MaxDrawDist);
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
                Position = new Vector3(SafeConverter.FloatFromString(textBox2.Text),
                                        SafeConverter.FloatFromString(textBox3.Text),
                                        SafeConverter.FloatFromString(textBox4.Text)),
                CamScreenCoords = new Vector2(SafeConverter.FloatFromString(textBox7.Text),
                                        SafeConverter.FloatFromString(textBox6.Text)),
                CameraRotation = new Vector3(SafeConverter.FloatFromString(textBox10.Text),
                                            SafeConverter.FloatFromString(textBox9.Text),
                                            SafeConverter.FloatFromString(textBox8.Text)),
                FOV = SafeConverter.FloatFromString(textBox10.Text),
                MinDrawDist = SafeConverter.FloatFromString(textBox11.Text),
                MaxDrawDist = SafeConverter.FloatFromString(textBox12.Text),
                Sensibility = SafeConverter.FloatFromString(textBox5.Text),
                MovementSpeed = SafeConverter.FloatFromString(textBox13.Text)
            };
            DialogResult = DialogResult.OK;
            Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //Open docuentation.
        }
    }
}
