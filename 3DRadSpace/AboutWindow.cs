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
    public partial class AboutWindow : Form
    {
        public AboutWindow()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void AboutWindow_Load(object sender, EventArgs e)
        {
            pictureBox1.ImageLocation = @"data\resources\Img1.bmp";
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
