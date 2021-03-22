using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Lib3DRadSpace_DX;
using Microsoft.Xna.Framework;

namespace _3DRadSpace
{
    public partial class CameraWnd : Form
    {
        public CameraWnd()
        {
            InitializeComponent();
            bCopy = null;
        }
        public CameraWnd(Camera cam)
        {
            InitializeComponent();

            TXTBOXobject_name.Text = cam.Name;
            CBOX_enabled.Checked = cam.Enabled;
            TB_xpos.Text = cam.Position.X + "";
            tb_ypos.Text = cam.Position.Y + "";
            tb_zpos.Text = cam.Position.Z + "";

            tb_rotX.Text = cam.Rotation.X + "";
            tb_rotY.Text = cam.Rotation.Y + "";
            tb_rotZ.Text = cam.Rotation.Z + "";

            tb_nX.Text = cam.Up.X + "";
            tb_ny.Text = cam.Up.Y + "";
            tb_nz.Text = cam.Up.Z + "";

            tb_fov.Text = cam.FOV + "";
            tb_npd.Text = cam.NearPlaneDistance + "";
            tb_fpd.Text = cam.FarPlaneDistance + "";

            checkBox1.Checked = cam.Allow2DSprites;

            bCopy = cam.Behiavours;
            for(int i =0; i < bCopy.Count;i++)
            {
                lb_behiavours.Items.Add(bCopy[i].ToString(BehiavourString));
            }
        }

        public BaseGameObject Result;
        public List<BehiavourStruct> bCopy;

        private void b_ok_Click(object sender, EventArgs e)
        {
            Result = new Camera(TXTBOXobject_name.Text, CBOX_enabled.Checked,
                 new Vector3(Convert.ToSingle(TB_xpos.Text, CultureInfo.InvariantCulture),
                    Convert.ToSingle(tb_ypos.Text, CultureInfo.InvariantCulture),
                    Convert.ToSingle(tb_zpos.Text, CultureInfo.InvariantCulture)
                ),
                new Vector3(
                    Convert.ToSingle(tb_rotX.Text, CultureInfo.InvariantCulture),
                    Convert.ToSingle(tb_rotY.Text, CultureInfo.InvariantCulture),
                    Convert.ToSingle(tb_rotZ.Text, CultureInfo.InvariantCulture)
                ),
                new Vector3(
                    Convert.ToSingle(tb_nX.Text, CultureInfo.InvariantCulture), //normal x
                    Convert.ToSingle(tb_ny.Text, CultureInfo.InvariantCulture), //normal y
                    Convert.ToSingle(tb_nz.Text, CultureInfo.InvariantCulture) //normal z
                ),Convert.ToSingle(tb_fov.Text, CultureInfo.InvariantCulture), //fov
                Convert.ToSingle(tb_fpd.Text, CultureInfo.InvariantCulture), //far plane distance
                Convert.ToSingle(tb_npd.Text, CultureInfo.InvariantCulture)) //near-plane distance
            {
                Allow2DSprites = checkBox1.Checked,
                Behiavours = bCopy
            };
            DialogResult = DialogResult.OK;
            Close();
        }

        public string BehiavourString(int id)
        {
            switch(id)
            {
                case 1: return "Chase";
                case 2: return "Look-At";
                default: return "Ignore";
            }
        }

        private void b_cancel_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
