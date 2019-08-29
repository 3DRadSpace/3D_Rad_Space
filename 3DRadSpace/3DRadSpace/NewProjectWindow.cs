using System;
using _3DRadSpaceDll;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class NewProjectWindow : Form
    {
        public NewProjectWindow()
        {
            InitializeComponent();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            Project.type = ProjectType.ThreeDimensional;
            Close();
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            Project.type = ProjectType.TwoDimensional;
            Close();
        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {
            Project.type = ProjectType.ScriptOnly;
            Close();
        }
    }
}
