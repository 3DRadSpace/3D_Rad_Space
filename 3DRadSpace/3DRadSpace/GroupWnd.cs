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
	public partial class GroupWnd : Form
	{
		public GroupWnd()
		{
			InitializeComponent();
		}
		public GroupWnd(Group g)
		{
			InitializeComponent();
			tb_objname.Text = g.Name;
			cb_enabled.Checked = g.Enabled;
			TB_xpos.Text = g.Position.X+"";
			TB_xpos.Text = g.Position.Y+"";
			TB_xpos.Text = g.Position.Z+"";
			//Using euler angles from a quaternion can result in precision loss???
			tb_rotX.Text = g.RotationEuler.X + "";
			tb_rotY.Text = g.RotationEuler.Y + "";
			tb_rotZ.Text = g.RotationEuler.Z + "";
			tb_sX.Text = g.Scale.X + "";
			tb_sX.Text = g.Scale.Y + "";
			tb_sX.Text = g.Scale.Z + "";

			listBox1.Items.Clear();
			for(int i =0; i < g.Behiavours.Count;i++)
			{
				listBox1.Items.Add(g.Behiavours.ToString());
			}
		}

		public BaseGameObject Result;
		List<int> LinkedObjects;

		private void b_ok_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.OK;
			Result = new Group(tb_objname.Text, cb_enabled.Checked,
				new Vector3(
					Convert.ToSingle(TB_xpos.Text, CultureInfo.InvariantCulture),
					Convert.ToSingle(tb_ypos.Text, CultureInfo.InvariantCulture),
					Convert.ToSingle(tb_zpos.Text, CultureInfo.InvariantCulture)
				),
				new Vector3(
					Convert.ToSingle(tb_rotX.Text, CultureInfo.InvariantCulture),
					Convert.ToSingle(tb_rotY.Text, CultureInfo.InvariantCulture),
					Convert.ToSingle(tb_rotZ.Text, CultureInfo.InvariantCulture)
				),
				new Vector3(
					Convert.ToSingle(tb_rotX.Text, CultureInfo.InvariantCulture),
					Convert.ToSingle(tb_rotY.Text, CultureInfo.InvariantCulture),
					Convert.ToSingle(tb_rotZ.Text, CultureInfo.InvariantCulture)
				), 
			LinkedObjects);
			DialogResult = DialogResult.OK;
			Close();
		}

		private void b_cancel_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
			Result = null;
			Close();
		}

        private void button1_Click(object sender, EventArgs e)
        {
			//Open docs
        }
    }
}
