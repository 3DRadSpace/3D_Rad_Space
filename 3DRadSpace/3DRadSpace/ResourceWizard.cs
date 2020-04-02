using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace _3DRadSpace
{
    public partial class ResourceWizard : Form
    {
        public ResourceWizard()
        {
            InitializeComponent();
            files = new List<string>();
        }
        List<string> files;
        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog open = new OpenFileDialog()
            {
                Title = "Add files to convert",
                Multiselect = true,
            };
            if(open.ShowDialog() == DialogResult.OK)
            {
                listBox1.Items.AddRange(open.FileNames);
                files.AddRange(open.FileNames);
            }
            open.Dispose();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex != -1)
            {
                listBox1.Items.RemoveAt(listBox1.SelectedIndex);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if(textBox1.Text == null)
            {
                MessageBox.Show("Please specify the resulting folder's name.", "Invalid data", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            Directory.CreateDirectory(Environment.CurrentDirectory + "\\ResourceTemp\\");
            Directory.CreateDirectory(Environment.CurrentDirectory + "\\Content\\"+textBox1.Text);
            for(int i =0; i < files.Count;i++)
            {
                File.Copy(listBox1.Items[i]+"", Environment.CurrentDirectory + "\\ResourceTemp\\" + Path.GetFileName(""+listBox1.Items[i]));
            }
            ProcessStartInfo runConverter = new ProcessStartInfo("XNBConverter\\Fast XNB Builder.exe"," /f \""+ Environment.CurrentDirectory + "//ResourceTemp//\"");
            runConverter.UseShellExecute = false;
            runConverter.WorkingDirectory = Environment.CurrentDirectory + "\\XNBConverter\\";
            Process p = Process.Start(runConverter);
            p.WaitForExit();
            string[] a = Directory.EnumerateFiles(Environment.CurrentDirectory + "\\XNBConverter\\Final").ToArray();
            for (int i = 0; i < a.Length; i++)
            {
                string[] extention = a[i].Split('.');
                if(extention[extention.Length-1] != "mgcontent") File.Copy(a[i],Environment.CurrentDirectory+"\\Content\\"+textBox1.Text+"\\"+Path.GetFileName(a[i]));
            }
            Directory.Delete(Environment.CurrentDirectory + "\\ResourceTemp\\",true);
        }
    }
}
