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
    public partial class GroupW : Form
    {
        public GroupW()
        {
            InitializeComponent();
            LoadItems();
        }
        public GroupW(Group group)
        {
            InitializeComponent();
            textBox1.Text = group.Name;
            LinkedObjs = group.SelectedObjects;
            LoadItems();
        }
        public GameObject Result;
        public List<int> LinkedObjs = new List<int>();
        private void button1_Click(object sender, EventArgs e)
        {
            Result = new Group()
            {
                Name = textBox1.Text,
                SelectedObjects = LinkedObjs
            };
            DialogResult = DialogResult.OK;
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Result = null;
            LinkedObjs = null;
            Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //open documentation
        }
        void LoadItems()
        {
            listBox1.Items.Clear();
            for(int i =0; i < LinkedObjs.Count;i++)
            {
                listBox1.Items.Add(Main.GameObjects[LinkedObjs[i]]+" ["+LinkedObjs[i]+"]");
            }
        }
    }
}
