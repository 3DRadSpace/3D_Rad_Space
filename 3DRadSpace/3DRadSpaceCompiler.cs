using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace _3DRadSpace
{
    public partial class _3DRadSpaceCompiler : Form
    {
        public _3DRadSpaceCompiler()
        {
            InitializeComponent();
        }

        private void _3DRadSpaceCompiler_Load(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            progressBar1.Maximum = 100;
            progressBar1.Minimum = 0;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog iconDialog = new OpenFileDialog()
            {
                Filter = "Icon File (.ico) | *.ico",
                Title = "Select a icon to use for your project...",
                Multiselect = false,
            };
            iconDialog.ShowDialog();
            try
            {
                pictureBox1.ImageLocation = iconDialog.FileName;
            }
            catch { } //Do nothin'
        }

        private void button2_Click(object sender, EventArgs e)
        {
            OpenFileDialog openProject = new OpenFileDialog()
            {
                Filter = "3DRadSpace Project | *.3drsp | Text File | *.txt",
                Title = "Open a 3DRadSpace project to use for your game...",
                Multiselect = false
            };
            openProject.ShowDialog();
            try
            {
                listBox1.Items.Add(openProject.FileName);
            }
            catch { } //Do nothing again, error messages are annoying tbh
        }

        private void button3_Click(object sender, EventArgs e)
        {
            listBox1.Items.Remove(listBox1.SelectedItem);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            int error = 0;
            string errordetail = "Your game was compiled!";
            //1 Check settings
            //2 Create Folders
            //3 Copy game files
            //4 Copy project files
            label3.Text = "Status: Checking settings...";
            if (textBox1.Text != null)
            {
                FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog()
                {
                    ShowNewFolderButton = true,
                    Description = "Find a folder for your project."
                };
                folderBrowserDialog.ShowDialog();
                string temp = folderBrowserDialog.SelectedPath + textBox1.Text;
                textBox1.Text = temp;
                    for (int i = 0; i < listBox1.Items.Count; i++)
                    {
                        if (File.Exists(listBox1.Items[i].ToString()))
                        {
                            continue;
                        }
                        else
                        {
                            errordetail = "A project file is missing from your computer.";
                            error = 1;
                            break;
                        }
                    }
                progressBar1.Value = 25;
                try
                {
                    for (int i = 0; i < listBox1.Items.Count; i++)
                    {
                        string[] filename = listBox1.Items[i].ToString().Split('/');
                        string safefilename = filename[filename.Length - 1];
                        File.Copy(listBox1.Items[i].ToString(), textBox1.Text + "/projects/" + safefilename);
                        progressBar1.Value += 25 / listBox1.Items.Count;
                    }
                }
                catch
                {
                    errordetail = "A project file is missing from your computer.";
                    error = 1;
                }
                File.Copy(@"3DRadSpace_Player.exe", textBox1.Text + "/" + textBox1.Text + ".exe");
                
            }
            else
            {
                errordetail = "Project name wasn't given.";
                error = 1;
            }
            if (error == 1) MessageBox.Show(errordetail, "Error", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            else MessageBox.Show(errordetail, "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void button5_Click(object sender, EventArgs e)
        {

        }
    }
}
