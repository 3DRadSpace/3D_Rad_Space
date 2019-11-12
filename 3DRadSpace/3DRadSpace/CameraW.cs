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
            Behiavour = new List<ObjectBehiavour>();
            InitializeComponent();
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
            Result = new Camera(textBox1.Text, checkBox1.Checked, new Vector3(Convert.ToSingle(textBox2.Text, a), Convert.ToSingle(textBox3.Text, a), Convert.ToSingle(textBox4.Text, a)),
                new Vector3(Convert.ToSingle(textBox6.Text, a), Convert.ToSingle(textBox7.Text, a), Convert.ToSingle(textBox5.Text, a))
                , new Vector3(Convert.ToSingle(textBox10.Text, a), Convert.ToSingle(textBox9.Text, a), Convert.ToSingle(textBox8.Text, a)),
                Convert.ToSingle(numericUpDown1.Value), Convert.ToSingle(textBox11.Text, a), Convert.ToSingle(textBox12.Text, a))
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
                case 1:  return "Chase";
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
