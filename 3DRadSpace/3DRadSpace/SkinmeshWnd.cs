using Lib3DRadSpace_DX;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Xna.Framework;
using System.Threading;

namespace _3DRadSpace
{
    public partial class SkinmeshWnd : Form
    {
        public SkinmeshWnd()
        {
            InitializeComponent();
        }
        public SkinmeshWnd(Skinmesh skm)
        {
            tb_name.Text = skm.Name;
            cb_visible.Checked = skm.Visible;
            tb_asset.Text = skm.Asset;
            TB_xpos.Text = skm.Position.X + "";
            tb_ypos.Text = skm.Position.Y + "";
            tb_zpos.Text = skm.Position.Z + "";
            tb_rotX.Text = skm.RotationEuler.X + "";
            tb_rotY.Text = skm.RotationEuler.Y + "";
            tb_rotZ.Text = skm.RotationEuler.Z + "";
            tb_cx.Text = skm.RotationCenter.X + "";
            tb_cy.Text = skm.RotationCenter.Y + "";
            tb_cz.Text = skm.RotationCenter.Z + "";
            tb_sx.Text = skm.Scale.X + "";
            tb_sy.Text = skm.Scale.Y + "";
            tb_sz.Text = skm.Scale.Z + "";
        }

        bool _prevexit = false;

        private void button2_Click(object sender, EventArgs e)
        {
            Thread prevthrd = new Thread(RunPreviewer);
            prevthrd.Start();
        }
        void RunPreviewer()
        {
            using(SkinmeshPreviewer skp = new SkinmeshPreviewer(tb_asset.Text, "EngineData"))
            {
                skp.Run();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog()
            {
                Filter = "XNB Model mesh (*.XNB)|*.XNB",
                Multiselect = false,
                Title = "Select a XNB compiled mesh",
                ShowReadOnly = true
            };
            DialogResult dr = ofd.ShowDialog();
            if(dr == DialogResult.OK)
            {
                tb_asset.Text = ofd.FileName.Replace(Environment.CurrentDirectory+"\\EngineData\\", "");
            }
            ofd.Dispose();
        }

        public BaseGameObject Result;

        private void button3_Click(object sender, EventArgs e)
        {
            Result = null;
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void b_ok_Click(object sender, EventArgs e)
        {
            Result = new Skinmesh(tb_name.Text, cb_visible.Checked,tb_asset.Text,
                new Vector3(Convert.ToSingle(TB_xpos.Text), Convert.ToSingle(tb_ypos.Text), Convert.ToSingle(tb_zpos.Text)),
                new Vector3(Convert.ToSingle(tb_rotX.Text), Convert.ToSingle(tb_rotY.Text), Convert.ToSingle(tb_rotZ.Text)),
                new Vector3(Convert.ToSingle(tb_cx.Text), Convert.ToSingle(tb_cy.Text), Convert.ToSingle(tb_cz.Text)),
                new Vector3(Convert.ToSingle(tb_sx.Text), Convert.ToSingle(tb_sy.Text), Convert.ToSingle(tb_sz.Text)));
            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
