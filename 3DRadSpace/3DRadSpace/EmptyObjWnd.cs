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
    public partial class EmptyObjWnd : Form
    {
        public EmptyObjWnd()
        {
            InitializeComponent();
        }
        public EmptyObjWnd(EmptyGameObject e)
        {
            InitializeComponent();

            tb_objname.Text = e.Name;
            cb_enabled.Checked = e.Enabled;

            TB_xpos.Text = e.Position.X + "";
            TB_xpos.Text = e.Position.Y + "";
            TB_xpos.Text = e.Position.Z + "";

            tb_rotX.Text = e.RotationEuler.X + "";
            tb_rotY.Text = e.RotationEuler.Y + "";
            tb_rotZ.Text = e.RotationEuler.Z + "";

            tb_sX.Text = e.Scale.X + "";
            tb_sX.Text = e.Scale.Y + "";
            tb_sX.Text = e.Scale.Z + "";
        }

        public BaseGameObject Result;

        private void b_cancel_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void b_ok_Click(object sender, EventArgs e)
        {
            Result = new EmptyGameObject(tb_objname.Text,cb_enabled.Checked,
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
                    Convert.ToSingle(tb_sX.Text, CultureInfo.InvariantCulture),
                    Convert.ToSingle(tb_sY.Text, CultureInfo.InvariantCulture),
                    Convert.ToSingle(tb_sZ.Text, CultureInfo.InvariantCulture)
                ));
            DialogResult = DialogResult.OK;
            Close();
        }

        private void b_help_Click(object sender, EventArgs e)
        {
            //Load help
        }
    }
}
