using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class AddObject : Form
    {
        public AddObject()
        {
            InitializeComponent();
        }
        public object Result;
        private void pictureBox1_Click(object sender, EventArgs e)
        {
            if (_3DRadSpaceDll.Project.type == _3DRadSpaceDll.ProjectType.ThreeDimensional)
            {
                MessageBox.Show("This object can only be used with 3D projects...", "2DCamera v1.0.0", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void pictureBox10_Click(object sender, EventArgs e)
        {
            ScriptW script = new ScriptW();
            if(script.ShowDialog() == DialogResult.OK)
            {
                Result = script.Result;
            }
            Close();
        }

        private void PictureBox15_Click(object sender, EventArgs e)
        {
            CameraW camera = new CameraW();
            if(camera.ShowDialog() == DialogResult.OK)
            {
                Result = camera.Result;
            }
            Close();
        }
    }
}
