using _3DRadSpaceDll;
using System;
using System.Collections.Generic;
using System.IO;
using System.Diagnostics;
using System.Net;
using Microsoft.Xna.Framework;
using System.Windows.Forms;


namespace _3DRadSpace
{
    partial class Editor : Microsoft.Xna.Framework.Game
    {
        bool ProjectSaved = true;
        void newProject(object a,EventArgs e)
        {
            saveProject(null, null);
            _3DRadSpaceDll.Game.GameObjects.Clear();
            NewProjectWindow projectWindow = new NewProjectWindow();
            projectWindow.ShowDialog();
            ApplyProjectType();
            ProjectSaved = true;
            discordRichPresence.SetPresence("Editing project", "New Project");
        }
        void openProject(object a,EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
                Title = "Open a 3DRadSpace project",
                Filter = "3DRadSpace Project (*.3drsp)|*.3drsp",
                Multiselect = false
            };
            DialogResult b = openFile.ShowDialog();
            if(b == DialogResult.OK)
            {
                _3DRadSpaceDll.Game.GameObjects = Project.Open(openFile.FileName);
                UpdateObjects();
                ProjectSaved = true;
                discordRichPresence.SetPresence("Editing project", Path.GetFileName(OpenedFile));
            }
        }
        void saveProject(object a,EventArgs e)
        {
            if (OpenedFile != null) Project.Save(OpenedFile);
            else saveProjectAs(a, e);
            ProjectSaved = true;
        }
        void saveProjectAs(object a,EventArgs e)
        {
            SaveFileDialog saveFile = new SaveFileDialog()
            {
                Filter = "3DRadSpace Project (*.3drsp)|*.3drsp",
                Title = "Save a 3DRadSpace project",
                OverwritePrompt = true,
            };
            if (saveFile.ShowDialog() == DialogResult.OK)
            {
                Project.Save(saveFile.FileName);
                OpenedFile = saveFile.FileName;
                discordRichPresence.SetPresence("Editing project", Path.GetFileName(OpenedFile));
                ProjectSaved = true;
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
            if (add.Result != null)
            {
                _3DRadSpaceDll.Game.GameObjects.Add(add.Result);
                ProjectSaved = false;
            }
            UpdateObjects();
        }
        void addAddon(object a,EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
                Title = "Add a 3DRadSpace project as a addon",
                Filter = "3DRadSpace Project (*.3drsp)|*.3drsp",
                Multiselect = false
            };
            DialogResult b = openFile.ShowDialog();
            if (b == DialogResult.OK)
            {
                List<object> c = Project.Open(openFile.FileName);
                _3DRadSpaceDll.Game.GameObjects.AddRange(c);
                UpdateObjects();
                ProjectSaved = false;
            }
        }
        void installResources(object a,EventArgs e)
        {
        }
        void checkforUpdatesEvent(object s,EventArgs a)
        {
            WebClient client = new WebClient();
            client.DownloadFile("https://drive.google.com/uc?export=download&id=0B9yRO5eZEvTjeHhPa05OZDRxUmM", @"version.temp");
            string v = File.ReadAllText(@"version.temp");
            string[] version = v.Split(' ');
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
                    client.DownloadFile("https://drive.google.com/uc?export=download&id=0B9yRO5eZEvTjSVhCZndjSGRUcVE", @"Setup.exe");
                    toolStripStatusLabel1.Text = "Status: Installing new update...";
                    saveProject(null, null);
                    Process.Start(@"Setup.exe");
                    Exit();
                }
                else toolStripStatusLabel1.Text = "Status: Ready";
            }
            else
            {
                MessageBox.Show("No new update found!", "Update", MessageBoxButtons.OK, MessageBoxIcon.Information);
                toolStripStatusLabel1.Text = "Status: Ready";
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
            object b = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex];
            if(b is Script s)
            {
                ScriptW scriptW = new ScriptW();

            }
        }
        void M_DeleteObject(object obj,EventArgs e)
        {
            _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex] = null;
            for(int i = listBox1.SelectedIndex;i < _3DRadSpaceDll.Game.GameObjects.Count -1;i++)
            {
                _3DRadSpaceDll.Game.GameObjects[i] = _3DRadSpaceDll.Game.GameObjects[i+1];
            }
            _3DRadSpaceDll.Game.GameObjects[_3DRadSpaceDll.Game.GameObjects.Count-1] = null;
            UpdateObjects();
        }
        void UpdateObjects()
        {
            listBox1.Items.Clear();
            for(int  i =0; i < _3DRadSpaceDll.Game.GameObjects.Count;i++)
            {
                GameObject obj = (GameObject)_3DRadSpaceDll.Game.GameObjects[i];
                if(obj) listBox1.Items.Add(obj.Name);
            }
        }
        void listBox1_MouseDown(object sender,MouseEventArgs mouse)
        {
            if(mouse.Button == MouseButtons.Right && listBox1.SelectedIndex != -1)
            {
                contextMenuStrip1.Show(GameWindow.Location.X+listBox1.Location.X, Cursor.Position.Y);
            }
        }
        void Editor_Exiting(object sender, FormClosingEventArgs e)
        {
            if(Settings[1] == true && ProjectSaved == false)
            {
               DialogResult result = MessageBox.Show("Your project is not saved. Unsaved changes can be lost.", "Warning", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Warning);
                if(result == DialogResult.Yes)
                {
                    saveProject(sender, null);
                }
                else if(result == DialogResult.Cancel)
                {
                    e.Cancel = true;
                }
            }
        }
        public static string ValidateNumericInput(string input)
        {
            string r = null;
            for(int i =0; i < input.Length;i++)
            {
                if (input[i] != ' ') r += input[i];
            }
            return r;
        }
    }
}
