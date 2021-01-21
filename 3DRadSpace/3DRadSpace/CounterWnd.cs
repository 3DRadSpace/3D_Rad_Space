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

namespace _3DRadSpace
{
    public partial class CounterWnd : Form
    {
        public CounterWnd()
        {
            InitializeComponent();
        }

        public CounterWnd(Counter c)
        {
            TXTBOXobject_name.Text = c.Name;
            TB_initialv.Text = c.Value + "";
            tb_inc.Text = c.Increment + "";
            CBOX_enabled.Checked = c.Enabled;
            cb_savefile.Checked = c.SaveToDrive;
            tb_filename.Text = c.Asset;
        }

        public BaseGameObject Result;

        private void b_ok_Click(object sender, EventArgs e)
        {
            string fn = null;
            if(!string.IsNullOrEmpty(tb_filename.Text)) fn = tb_filename.Text;
            DialogResult = DialogResult.OK;
            Result = new Counter(TXTBOXobject_name.Text, CBOX_enabled.Checked, Convert.ToSingle(TB_initialv.Text, CultureInfo.CurrentCulture), Convert.ToSingle(tb_inc.Text,CultureInfo.CurrentCulture), fn);
            Close();
        }

        private void b_cancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Result = null;
            Close();
        }

        private void Help_Click(object sender, EventArgs e)
        {
            //open docs
        }
    }
}
