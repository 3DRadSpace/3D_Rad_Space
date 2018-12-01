using System;
using System.Diagnostics;
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
        string path;
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
                Filter = "3DRadSpace Project (*.3drsp)|*.3drsp| Text File | *.txt",
                Title = "Open a 3DRadSpace project to use for your game...",
                Multiselect = true
            };
            openProject.ShowDialog();
            try
            {
                listBox1.Items.AddRange(openProject.FileNames);
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
            //3 Copy project files
                //3.1 Project Files
                //3.2 Resources
            //4 Copy game files
                //4.1 3DRadSpace Dlls
                //4.2 Monogame Dlls
            label3.Text = "Status: Checking settings...";
            if (textBox1.Text != null)
            {
                FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog()
                {
                    ShowNewFolderButton = true,
                    Description = "Find a folder for your project."
                };
                folderBrowserDialog.ShowDialog();
                path = folderBrowserDialog.SelectedPath;
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
                            File.AppendAllText("CompileErrors.txt", errordetail+ " : "+listBox1.Items[i].ToString());
                            break;
                        }
                    }
                if(listBox1.Items.Count == 0)
                {
                    errordetail = "No projects to compile";
                    error = 1;
                }
                progressBar1.Value = 25;
                Directory.CreateDirectory(path + "/" + textBox1.Text + "/projects/");
                label3.Text = "Status: Copying Projects...";
                try
                {
                    for (int i = 0; i < listBox1.Items.Count; i++)
                    {
                        string safefilename = Path.GetFileName(listBox1.Items[i].ToString());
                        File.Copy(listBox1.Items[i].ToString(), path +"/"+textBox1.Text+ "/projects/" + safefilename);
                        progressBar1.Value += 25 / listBox1.Items.Count;
                    }
                }
                catch(FileNotFoundException)
                {
                    errordetail = "A project file is missing from your computer.";
                    File.AppendAllText("CompileErrors.txt", errordetail);
                    error = 1;
                }
                label3.Text = "Status: Copying Resources...";
                
                label3.Text = "Status: Copying executables and dlls.";
                try
                {
                    File.Copy(@"3DRadSpacePlayer.exe", path + "/" + textBox1.Text + "/"+textBox1.Text+".exe");
                }
                catch(FileNotFoundException)
                {
                    errordetail = "3DRadSpacePlayer.exe is missing from your instalation.";
                    File.AppendAllText("CompileErrors.txt", errordetail);
                    error = 1;
                }
                try
                {
                    File.Copy(@"3DRadSpaceDll.dll", path+"/"+textBox1.Text + "/3DRadSpaceDll.dll");
                }
                catch(FileNotFoundException)
                {
                    errordetail = "3DRadSpaceDll.dll is missing from your instalation.";
                    File.AppendAllText("CompileErrors.txt", errordetail);
                    error = 1;
                }
                try
                {
                    File.Copy(@"MonoGame.Framework.dll", path + "/" + textBox1.Text + "/MonoGame.Framework.dll");
                    File.Copy(@"SharpDX.Direct2D1.dll", path + "/" + textBox1.Text + "/SharpDX.Direct2D1.dll");
                    File.Copy(@"SharpDX.Direct3D9.dll", path + "/" + textBox1.Text + "/SharpDX.Direct3D9.dll");
                    File.Copy(@"SharpDX.Direct3D11.dll", path + "/" + textBox1.Text + "/SharpDX.Direct3D11.dll");
                    File.Copy(@"SharpDX.dll", path + "/" + textBox1.Text + "/SharpDX.dll");
                    File.Copy(@"SharpDX.DXGI.dll", path + "/" + textBox1.Text + "/SharpDX.DXGI.dll");
                    File.Copy(@"SharpDX.MediaFoundation.dll", path + "/" + textBox1.Text + "/SharpDX.MediaFoundation.dll");
                    File.Copy(@"SharpDX.XAudio2.dll", path + "/" + textBox1.Text + "/SharpDX.XAudio2.dll");
                    File.Copy(@"SharpDX.XInput.dll", path + "/" + textBox1.Text + "/SharpDX.XInput.dll");
                }
                catch(FileNotFoundException)
                {
                    errordetail = "A Dll required for your compiled game is missing.";
                    File.AppendAllText("CompileErrors.txt", errordetail);
                    error = 1;
                }
                string safefilename2 = Path.GetFileName(listBox1.Items[0].ToString());
                string[] settings =
                {
                    "Projects/"+safefilename2,
                    @"False",
                    textBox1.Text
                };
                File.WriteAllLines(path+"/"+textBox1.Text+ "/settings.data",settings);
                progressBar1.Value += 25;
                DirectoryCopy(@"Content/", path+"/"+textBox1.Text+"/Content/", true);
                progressBar1.Value += 25;
            }
            else
            {
                errordetail = "Project name wasn't given.";
                File.AppendAllText("CompileErrors.txt", errordetail);
                error = 1;
            }
            if (error == 1)
            {
                MessageBox.Show(errordetail, "Error", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                Process.Start("CompileErrors.txt");
                label3.Text = "Status:Compilation Failed!";
            }
            else
            {
                progressBar1.Value = 100;
                label3.Text = "Status: Compilation Success!";
                MessageBox.Show(errordetail, "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            label3.Text = "Status: Ready!";
        }

        private void button5_Click(object sender, EventArgs e)
        {

        }
        /// <summary>
        /// Copy paste from MSs documentation XD
        /// </summary>
        /// <param name="sourceDirName">source folder</param>
        /// <param name="destDirName">destination</param>
        /// <param name="copySubDirs"></param>
        private static void DirectoryCopy(string sourceDirName, string destDirName, bool copySubDirs)
        {
            // Get the subdirectories for the specified directory.
            DirectoryInfo dir = new DirectoryInfo(sourceDirName);

            if (!dir.Exists)
            {
                throw new DirectoryNotFoundException(
                    "Source directory does not exist or could not be found: "
                    + sourceDirName);
            }

            DirectoryInfo[] dirs = dir.GetDirectories();
            // If the destination directory doesn't exist, create it.
            if (!Directory.Exists(destDirName))
            {
                Directory.CreateDirectory(destDirName);
            }

            // Get the files in the directory and copy them to the new location.
            FileInfo[] files = dir.GetFiles();
            foreach (FileInfo file in files)
            {
                string temppath = Path.Combine(destDirName, file.Name);
                file.CopyTo(temppath, false);
            }

            // If copying subdirectories, copy them and their contents to new location.
            if (copySubDirs)
            {
                foreach (DirectoryInfo subdir in dirs)
                {
                    string temppath = Path.Combine(destDirName, subdir.Name);
                    DirectoryCopy(subdir.FullName, temppath, copySubDirs);
                }
            }
        }
    }
}
