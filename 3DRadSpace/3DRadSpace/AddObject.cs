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
                MessageBox.Show("This object can only be used with 2D projects...", "2DCamera v1.0.0", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void pictureBox10_Click(object sender, EventArgs e)
        {
            ScriptW script = new ScriptW();
            if(script.ShowDialog() == DialogResult.OK)
            {
                Result = script.Result;
            }
            script.Dispose();
            Close();
        }

        private void PictureBox15_Click(object sender, EventArgs e)
        {
            CameraW camera = new CameraW();
            if(camera.ShowDialog() == DialogResult.OK)
            {
                Result = camera.Result;
            }
            camera.Dispose();
            Close();
        }

        private void pictureBox17_Click(object sender, EventArgs e)
        {
            SkyColorW skyColor = new SkyColorW();
            if(skyColor.ShowDialog() == DialogResult.OK)
            {
                Result = skyColor.Result;
            }
            skyColor.Dispose();
            Close();
        }

        private void pictureBox19_Click(object sender, EventArgs e)
        {
            FogW fog = new FogW();
            if(fog.ShowDialog() == DialogResult.OK)
            {
                Result = fog.Result;
            }
            fog.Dispose();
            Close();
        }

        private void pictureBox16_Click(object sender, EventArgs e)
        {
            SkinmeshW skinmesh = new SkinmeshW();
            if(skinmesh.ShowDialog() == DialogResult.OK)
            {
                Result = skinmesh.Result;
            }
            skinmesh.Dispose();
            Close();
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            SpriteW sprite = new SpriteW();
            if(sprite.ShowDialog() == DialogResult.OK)
            {
                Result = sprite.Result;
            }
            sprite.Dispose();
            Close();
        }
    }
}
