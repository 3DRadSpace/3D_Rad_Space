using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace _3DRadSpace
{
    public partial class OBJR : Form
    {
        public OBJR()
        {
            InitializeComponent();
        }
        private void OBJR_Load(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            string ObjectType;
            ObjectType = File.ReadAllText(@"OBJT.data");
            string[] Objects;
            Objects = File.ReadAllLines(@"Projects/backup.3drsp");
            listBox1.Items.AddRange(Objects);
            if (ObjectType == "Camera")
            {
                label1.Text = "Object Type : Camera";
                label1.ForeColor = Color.Green;
                ObjectType = "Camera";
                comboBox1.Items.Clear();
                object[] CamRel = {"Follow","Look At","Ignore"};
                comboBox1.Items.AddRange(CamRel);
            }
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            File.WriteAllText("relation.data", "");
            Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (comboBox1.SelectedItem != null)
            {
                string obj = listBox1.SelectedItem.ToString() + comboBox1.SelectedItem.ToString();
                obj = obj.Replace(' ', '-');
                listBox2.Items.Add(obj);
            }
            else MessageBox.Show("No relation defined...", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            listBox2.Items.Remove(listBox2.SelectedItem);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string Data = "";
            foreach (var item in listBox2.Items)
            {
                Data += item+"/";
            }
        File.WriteAllText("relation.data",Data);
        Close();
        }
    }
}
