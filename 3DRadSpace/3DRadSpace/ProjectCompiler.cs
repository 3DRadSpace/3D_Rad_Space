using System;
using System.Diagnostics;
using System.Windows.Forms;
using System.IO;

namespace _3DRadSpace
{
    public partial class ProjectCompiler : Form
    {
        public ProjectCompiler()
        {
            InitializeComponent();
        }
        string Path, MainProject, IconPath;
        private void button6_Click(object sender, EventArgs e)
        {
            //open documentation
        }

        private void button7_Click(object sender, EventArgs e)
        {
            ///Step 1: Ask for folder
            label3.Text = "Status: Waiting for user input...";
            FolderBrowserDialog folderBrowser = new FolderBrowserDialog()
            {
                ShowNewFolderButton = true,
                Description = "Select a folder where your game will get compiled..."
            };
            ///Make a stopwatch to measure the `compilation` time
            Stopwatch timer;
            ///Step 2: validate input
            if (folderBrowser.ShowDialog() == DialogResult.OK)
            {
                label3.Text = "Status: Validating input...";
                progressBar1.Value += 12;
                timer = Stopwatch.StartNew();
                Path = folderBrowser.SelectedPath;
                string Error = null;
                if (string.IsNullOrEmpty(textBox1.Text)) Error += "You didn't specify a name for the project. \r\n";
                if (string.IsNullOrEmpty(textBox2.Text)) Error += "You didn't specify the content directory. \r\n";
                if (!File.Exists(IconPath)) Error += "Icon file doesn't exist. \r\n";
                if (string.IsNullOrEmpty(MainProject)) Error += "Main Project isn't defined.";
                for (int i = 0; i < listBox1.Items.Count; i++)
                {
                    if (!File.Exists(listBox1.Items[i].ToString())) Error += "File " + listBox1.Items[i] + " doesn't exist \r\n";
                }
                if (Error != null)
                {
                    label3.Text = "Status: Errors during compilation...";
                    MessageBox.Show(Error, "Compilation Erorrs", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    label3.Text = "Status: Ready...";
                    folderBrowser.Dispose();
                    return;
                }
                progressBar1.Value += 12;
            }
            else
            {
                label3.Text = "Status: Ready...";
                folderBrowser.Dispose();
                return;
            }
            ///Step 3: Create necesarry folders...
            label3.Text = "Status: Creating folders...";
            Directory.CreateDirectory(Path + "//Projects//");
            Directory.CreateDirectory(Path + "//" + textBox2.Text);
            Directory.CreateDirectory(Path + "//Scripts");
            progressBar1.Value += 12;
            ///Step 4: Copy DLLs & Executables
            try
            {
                label3.Text = "Status: Copying assemblies...";
                File.Copy(@"3DRadSpace_Player.exe", Path + "//" + textBox1.Text + ".exe");
                File.Copy(IconPath, Path + "//Icon.ico");
                File.Copy(@"3DRadSpaceDll.dll", Path + "//3DRadSpaceDll.dll");
                File.Copy(@"MonoGame.Framework.dll", Path + "//MonoGame.Framework.dll");
                File.Copy(@"SharpDX.Direct2D1.dll", Path + "//SharpDX.Direct2D1.dll");
                File.Copy(@"SharpDX.Direct3D11.dll", Path + "//SharpDX.Direct3D11.dll");
                File.Copy(@"SharpDX.dll", Path + "//SharpDX.dll");
                File.Copy(@"SharpDX.DXGI.dll", Path + "//SharpDX.DXGI.dll");
                File.Copy(@"SharpDX.MediaFoundation.dll", Path + "//SharpDX.MediaFoundation.dll");
                File.Copy(@"SharpDX.XAudio2.dll", Path + "//SharpDX.XAudio2.dll");
                File.Copy(@"SharpDX.XInput.dll", Path + "//SharpDX.XInput.dll");
                progressBar1.Value += 12;
            }
            catch (FileNotFoundException ex)
            {
                label3.Text = "Status: Errors during compilation...";
                MessageBox.Show("The following file is missing: " + ex.FileName, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                label3.Text = "Status: Ready...";
                folderBrowser.Dispose();
                return;
            }
            ///Step 5: Copy Content.
            try
            {
                label3.Text = "Status: Copying content (models,images,etc) ...";
                string[] Content = Directory.GetFiles(@"Content");
                for (int i = 0; i < Content.Length; i++)
                {
                    File.Copy(Content[i], Path + "//" + textBox2.Text + "//" + System.IO.Path.GetFileName(Content[i]));
                    progressBar1.Value += 12 / Content.Length;
                }
            }
            catch (FileNotFoundException ex)
            {
                label3.Text = "Status: Errors during compilation...";
                MessageBox.Show("The following project file is missing: " + ex.FileName, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                label3.Text = "Status: Ready...";
            }
            ///Step 6: Create config file
            label3.Text = "Status: Creating project configuration...";
            File.WriteAllLines(Path+"//GameConfig.cfg",new []{ textBox1.Text,textBox2.Text,MainProject});
            progressBar1.Value += 12;
            ///Step 7: Copy Projects.
            label3.Text = "Status: Copying projects...";
            for(int i =0; i < listBox1.Items.Count; i++)
            {
                File.Copy(listBox1.Items[i].ToString(), Path + "//Projects//" + System.IO.Path.GetFileName(listBox1.Items[i].ToString()));
                progressBar1.Value += 12 / listBox1.Items.Count;
            }
            //Step 8: Copy scripts
            label3.Text = "Status: Copying scripts...";
            string[] scripts = Directory.GetFiles(@"Scripts");
            for(int i =0; i < scripts.Length; i++)
            {
                File.Copy(scripts[i], Path + "//Scripts//" + System.IO.Path.GetFileName(scripts[i]));
                progressBar1.Value += 12 / scripts.Length;
            }
            //Step 9: Finish
            label3.Text = "Status: Finished!";
            progressBar1.Value = 100;
            timer.Stop();
            DialogResult f = MessageBox.Show("Compilation finished! Time:"+ timer.Elapsed.Seconds + "s "+timer.Elapsed.Milliseconds+"ms \r\n Do you want to open the compiled game's folder?", "Compilation success!", MessageBoxButtons.YesNo, MessageBoxIcon.Asterisk);
            if(f == DialogResult.Yes)
            {
                Process.Start(Path);
            }
            folderBrowser.Dispose();

        }

        private void button2_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
                Title = "Open a 3DRadSpace project",
                Filter = "3DRadSpace Project (*.3drsp)|*.3drsp",
                Multiselect = false
            };
            DialogResult b = openFile.ShowDialog();
            if (b == DialogResult.OK)
            {
                listBox1.Items.Add(openFile.FileName);
            }
            openFile.Dispose();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            listBox1.Items.Remove(listBox1.SelectedItem);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openIcon = new OpenFileDialog()
            {
                Filter = "Icon (*.ico)|*.ico",
                Multiselect = false
            };
            if(openIcon.ShowDialog() == DialogResult.OK)
            {
                pictureBox1.ImageLocation = openIcon.FileName;
                IconPath = openIcon.FileName;
            }
            openIcon.Dispose();
        }

        private void ProjectCompiler_Load(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            progressBar1.Minimum = 0;
            progressBar1.Maximum = 100;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (listBox1.Items.Count > 0)
            {
                Compiler_SelectMainProject mainProject = new Compiler_SelectMainProject();
                mainProject.listBox1.Items.AddRange(listBox1.Items);
                if (mainProject.ShowDialog() == DialogResult.OK)
                {
                    MainProject = mainProject.Result;
                }
                mainProject.Dispose();
            }
        }
    }
}
