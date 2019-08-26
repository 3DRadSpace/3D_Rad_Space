using _3DRadSpaceDll;
using System;
using System.IO;
using System.Diagnostics;
using System.Net;
using Microsoft.Xna.Framework;
using System.Windows.Forms;


namespace _3DRadSpace
{
    partial class Editor : Microsoft.Xna.Framework.Game
    {
        void newProject(object a,EventArgs e)
        {
            NewProjectWindow projectWindow = new NewProjectWindow();
            projectWindow.ShowDialog();
            Program.ProjectTypeScript = true;
            ApplyProjectType();
        }
        void openProject(object a,EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
                Title = "Open a 3DRadSpace project",
                Filter = "3DRadSpace Project (*.3drsp) | (.*3drsp)",
                Multiselect = false
            };
            DialogResult b = openFile.ShowDialog();
            if(b == DialogResult.OK)
            {
                _3DRadSpaceDll.Game.GameObjects = Project.Open(openFile.FileName);
                UpdateObjects();
            }
        }
        void saveProject(object a,EventArgs e)
        {
            if (OpenedFile != null) Project.Save(OpenedFile);
            else
            {
                SaveFileDialog saveFile = new SaveFileDialog()
                {
                    Filter = "3DRadSpace Project (*.3drsp) | (.*3drsp)",
                    Title = "Save a 3DRadSpace project",
                    OverwritePrompt = true,
                };
                if (saveFile.ShowDialog() == DialogResult.OK)
                {
                    Project.Save(saveFile.FileName);
                    OpenedFile = saveFile.FileName;
                }
            }
        }
        void saveProjectAs(object a,EventArgs e)
        {
            SaveFileDialog saveFile = new SaveFileDialog()
            {
                Filter = "3DRadSpace Project (*.3drsp) | (.*3drsp)",
                Title = "Save a 3DRadSpace project",
                OverwritePrompt = true,
            };
            if (saveFile.ShowDialog() == DialogResult.OK)
            {
                Project.Save(saveFile.FileName);
                OpenedFile = saveFile.FileName;
            }
        }
        void playProject(object a,EventArgs e)
        {
            saveProject(null, null);
            ProcessStartInfo process = new ProcessStartInfo(@"3DRadSpacePlayer.exe", OpenedFile);
        }
        void exitEditor(object a,EventArgs e)
        {
            Application.Exit();
        }
        void compileProject(object a,EventArgs e)
        {
            ProjectCompiler compiler = new ProjectCompiler();
            compiler.ShowDialog();
        }
        void addObject(object a,EventArgs e)
        {
            AddObject add = new AddObject();
            add.ShowDialog();
            UpdateObjects();
        }
        void addAddon(object a,EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
                Title = "Add a 3DRadSpace project as a addon",
                Filter = "3DRadSpace Project (*.3drsp) | (.*3drsp)",
                Multiselect = false
            };
            DialogResult b = openFile.ShowDialog();
            if (b == DialogResult.OK)
            {
                _3DRadSpaceDll.Game.GameObjects = Project.Open(openFile.FileName);
                UpdateObjects();
            }
        }
        void installResources(object a,EventArgs e)
        {
        }
        void checkforUpdatesEvent(object s,EventArgs a)
        {
            WebClient client = new WebClient();
            client.DownloadFile("", @"version.temp");
            string v = File.ReadAllText(@"version.temp");
            string[] version = v.Split('.');
            bool NewVersionAvalable = false;
            for(int i =0; i < 3; i++)
            {
                if(version[i] != Program.Version[i])
                {
                    NewVersionAvalable = true;
                    toolStripStatusLabel1.Text = "Status: Downloading new update...";
                    break;
                }
            }
            if(NewVersionAvalable)
            {
                DialogResult dialog = MessageBox.Show("New update found! Do you want it installed?", "Update", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (dialog == DialogResult.Yes)
                {
                    client.DownloadFile("setup", @"Setup.exe");
                    saveProject(null, null);
                    Process.Start(@"Setup.exe");
                    Exit();
                }
            }
            else
            {
                MessageBox.Show("No new update found!", "Update", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
        void aboutBoxOpen(object a, EventArgs e)
        {
            AboutBox aboutBox = new AboutBox();
            aboutBox.ShowDialog();
        }
        void settingsOpen(object a, EventArgs e)
        {
            Settings settings = new Settings();
            settings.ShowDialog();
        }
        void openDocumentation(object a,EventArgs b)
        {
            //open documentation
        }
        void officialWebsite(object a, EventArgs b)
        {
            Process.Start("http://3dradspace.000webhost.com");
        }
        void openForum(object a, EventArgs b)
        {
            Process.Start("http://classdev.net");
        }
        void reportBug(object a,EventArgs args)
        {
            ///ah fck i realised I have to update the website aaaaaaaaaaaaa
            Process.Start("http://3dradspace.000webhost.com");
        }
        void M_EditObject(object a,EventArgs e)
        {
            
        }
        void M_DeleteObject(object obj,EventArgs e)
        {
            _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex] = null;
            //TODO :move the next elements...
            UpdateObjects();
        }
        void UpdateObjects()
        {
            listBox1.Items.Clear();
            for(int  i =0; i < _3DRadSpaceDll.Game.GameObjects.Count;i++)
            {
                GameObject obj = (GameObject)_3DRadSpaceDll.Game.GameObjects[i];
                listBox1.Items.Add(obj.Name);
            }
        }
    }
}
