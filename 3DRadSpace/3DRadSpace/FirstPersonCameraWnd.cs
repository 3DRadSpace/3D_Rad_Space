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
    public partial class FirstPersonCameraWnd : Form
    {
        public FirstPersonCameraWnd()
        {
            InitializeComponent();
        }
        public FirstPersonCameraWnd(FirstPersonCamera cam)
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

            tb_nX.Text = cam.Normal.X + "";
            tb_ny.Text = cam.Normal.Y + "";
            tb_nz.Text = cam.Normal.Z + "";

            tb_fov.Text = cam.FOV + "";
            tb_npd.Text = cam.NearPlaneDistance + "";
            tb_fpd.Text = cam.FarPlaneDistance + "";

            tb_mass.Text = cam.Mass + "";
            tb_sensibility.Text = cam.Sensibility + "";

            tb_standingspeed.Text = cam.MovmentSpeed + "";
            tb_sprintspeed.Text = cam.SprintSpeed + "";
            tb_crouchingspeed.Text = cam.CrouchingSpeed + "";
            tb_pronespeed.Text = cam.ProneSpeed + "";

            tb_standingheight.Text = cam.Height + "";
            tb_crouchheight.Text = cam.CrouchingSpeed + "";
            tb_pronespeed.Text = cam.ProneSpeed + "";
            tb_jumpingheight.Text = cam.JumpingHeight + "";

            COMBO_forward.Text = InputHelper.GetStringFromKey(cam.Key_Forward);
            COMBO_backward.Text = InputHelper.GetStringFromKey(cam.Key_Backwards);
            COMBO_left.Text = InputHelper.GetStringFromKey(cam.Key_Left);
            COMBO_right.Text = InputHelper.GetStringFromKey(cam.Key_Right);
            COMBO_jump.Text = InputHelper.GetStringFromKey(cam.Key_Jump);
            COMBO_sprint.Text = InputHelper.GetStringFromKey(cam.Key_Sprint);
            COMBO_crouch.Text = InputHelper.GetStringFromKey(cam.Key_Crouch);
            COMBO_prone.Text = InputHelper.GetStringFromKey(cam.Key_Prone);
        }

        public BaseGameObject Result;

        private void b_ok_Click(object sender, EventArgs e)
        {
            Result = new FirstPersonCamera(TXTBOXobject_name.Text, CBOX_enabled.Checked,
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
                ), Convert.ToSingle(tb_npd.Text, CultureInfo.InvariantCulture), //near plane distance
                Convert.ToSingle(tb_fpd.Text, CultureInfo.InvariantCulture), //far plane distance
                Convert.ToSingle(tb_fov.Text, CultureInfo.InvariantCulture), //fov

                Convert.ToSingle(tb_mass.Text, CultureInfo.InvariantCulture), //mass
                Convert.ToSingle(tb_standingspeed, CultureInfo.InvariantCulture), //standing speed
                Convert.ToSingle(tb_sprintspeed, CultureInfo.InvariantCulture), //sprinting speed
                Convert.ToSingle(tb_crouchingspeed, CultureInfo.InvariantCulture), //crouching movement speed
                Convert.ToSingle(tb_pronespeed, CultureInfo.InvariantCulture), // prone stance movement speed
                Convert.ToSingle(tb_standingheight, CultureInfo.InvariantCulture), //standing height
                Convert.ToSingle(tb_crouchheight, CultureInfo.InvariantCulture), //crouching stance height
                Convert.ToSingle(tb_proneheight, CultureInfo.InvariantCulture), //prone height
                Convert.ToSingle(tb_jumpingheight,CultureInfo.InvariantCulture), //jumping height
                Convert.ToSingle(tb_sensibility, CultureInfo.InvariantCulture), // mouse sensibility
                InputHelper.GetKeyFromString(COMBO_forward.Text), // forward key
                InputHelper.GetKeyFromString(COMBO_backward.Text), // forward key
                InputHelper.GetKeyFromString(COMBO_right.Text), //right movement key
                InputHelper.GetKeyFromString(COMBO_left.Text), //left movement key
                InputHelper.GetKeyFromString(COMBO_crouch.Text), //crouch key
                InputHelper.GetKeyFromString(COMBO_prone.Text), //crouch key
                InputHelper.GetKeyFromString(COMBO_sprint.Text), //sprinting key
                InputHelper.GetKeyFromString(COMBO_jump.Text));//crouch key
            DialogResult = DialogResult.OK;
            Close();
        }

        private void b_cancel_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
