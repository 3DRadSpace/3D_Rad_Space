using System;
using System.IO;
using System.Windows.Forms;

namespace _3DRadSpace
{
    public partial class EditMenuStrip : Form
    {
        public EditMenuStrip()
        {
            InitializeComponent();
        }
        public static string StripResult;
        private void linkLabel6_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            File.WriteAllText(@"lastobj.data", " ");
            Game1.Focus = true;
            StripResult = null;
            Close();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            StripResult = "1";
            ObjectsList dialog1 = new ObjectsList();
            dialog1.ShowDialog();
            Game1.Focus = true;
            Close();
        }

        private void linkLabel2_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            OpenFileDialog dialog2 = new OpenFileDialog()
            {
            Filter = "3DRadSpace Project | *.3drsp | Text File | *.txt",
            Title = "Find a 3DRadSpace project to use as a addon...",
            Multiselect = false
            };
            dialog2.ShowDialog();
            StripResult = "2 "+dialog2.FileName;
            File.WriteAllText(@"lastobj.data", " ");
            Game1.Focus = true;
            Close();
        }

        private void linkLabel3_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            File.WriteAllText(@"lastobj.data", " ");
        }

        private void linkLabel4_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            File.WriteAllText(@"lastobj.data", " ");
        }

        private void EditMenuStrip_Load(object sender, EventArgs e)
        {
            Location = new System.Drawing.Point(40, 30);
        }
    }
}
