using System;
using _3DRadSpaceDll;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class SelectObjectDialog : Form
    {
        public SelectObjectDialog()
        {
            Result = -1;
            InitializeComponent();
        }
        public int Result;
        private void SelectObjectDialog_Load(object sender, EventArgs e)
        {
            for(int i =0; i < Game.GameObjects.Count;i++)
            {
                if(Game.GameObjects[i] != null )listBox1.Items.Add(Game.GameObjects[i]);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(listBox1.SelectedIndex >= 0)
            {
                Result = listBox1.SelectedIndex;
                Close();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Result = -1;
            Close();
        }
    }
}
