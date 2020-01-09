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
            UpdateObjects();
            discordRichPresence.SetPresence("Editing project", "New Project");
            projectWindow.Dispose();
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
            openFile.Dispose();
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
            saveFile.Dispose();
        }
        void playProject(object a,EventArgs e)
        {
            saveProject(null, null);
            ProcessStartInfo process = new ProcessStartInfo(@"3DRadSpace_Player.exe", "\""+OpenedFile+"\"");
            Process.Start(process);
        }
        void exitEditor(object a,EventArgs e)
        {
            Application.Exit();
        }
        void compileProject(object a,EventArgs e)
        {
            ProjectCompiler compiler = new ProjectCompiler();
            compiler.ShowDialog();
            compiler.Dispose();
        }
        void addObject(object a,EventArgs e)
        {
            AddObject add = new AddObject();
            add.ShowDialog();
            if (add.Result != null)
            {
                _3DRadSpaceDll.Game.GameObjects.Add(add.Result);
                if(add.Result is Skinmesh s) s.Load(Content); //Prevent crashes by loading the model.
                if (add.Result is Sprite sp) sp.Load(Content,GraphicsDevice);
                ProjectSaved = false;
            }
            UpdateObjects();
            add.Dispose();
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
            openFile.Dispose();
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
            client.Dispose();
        }
        void aboutBoxOpen(object a, EventArgs e)
        {
            AboutBox aboutBox = new AboutBox();
            aboutBox.ShowDialog();
            aboutBox.Dispose();
        }
        void settingsOpen(object a, EventArgs e)
        {
            Settings settings = new Settings();
            settings.ShowDialog();
            settings.Dispose();
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
            if(b is Script)
            {
                ScriptW scriptW = new ScriptW((Script)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex]);
                scriptW.ShowDialog();
                if (scriptW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex] = scriptW.Result;
                scriptW.Dispose();
            }
            if (b is Camera)
            {
                CameraW cameraW = new CameraW((Camera)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex]);
                cameraW.ShowDialog();
                if (cameraW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex] = cameraW.Result;
                cameraW.Dispose();
            }
            if(b is SkyColor)
            {
                SkyColorW colorW = new SkyColorW((SkyColor)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex]);
                colorW.ShowDialog();
                if (colorW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex] = colorW.Result;
                colorW.Dispose();
            }
            if(b is Fog)
            {
                FogW fogW = new FogW((Fog)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex]);
                fogW.ShowDialog();
                if (fogW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex] = fogW.Result;
                fogW.Dispose();
            }
            if(b is Skinmesh)
            {
                SkinmeshW skinmeshW = new SkinmeshW((Skinmesh)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex]);
                skinmeshW.ShowDialog();
                if (skinmeshW.Result != null)
                {
                    _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex] = skinmeshW.Result;
                    Skinmesh sk = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex] as Skinmesh;
                    sk.Load(Content);
                }
                skinmeshW.Dispose();
            }
            if( b is Sprite)
            {
                SpriteW spriteW = new SpriteW((Sprite)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex]);
                spriteW.ShowDialog();
                if (spriteW.Result != null)
                {
                    _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex] = spriteW.Result;
                    Sprite spr = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex] as Sprite;
                    spr.Load(Content,GraphicsDevice);
                }
                spriteW.Dispose();
            }
            UpdateObjects();
        }
        void M_DeleteObject(object obj,EventArgs e)
        {
            if(_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedIndex] is SkyColor s)
            {
                ClearColor = Color.Black;
            }
            _3DRadSpaceDll.Game.GameObjects.RemoveAt(listBox1.SelectedIndex);
            UpdateObjects();
        }
        void GameWindow_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop)) e.Effect = DragDropEffects.Copy;
        }
        void GameWindow_DragDrop(object sender, DragEventArgs e)
        {
            string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
            for(int i =0; i < files.Length;i++)
            {
                string[] ext = files[i].Split('.');
               if(ext[ext.Length- 1] == "3drsp") _3DRadSpaceDll.Game.GameObjects.AddRange(Project.Open(files[i]));
            }
            ProjectSaved = false;
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
        public static string ValidateNumberTextInput(string input)
        {
            if (input == null) return "_";
            string r = null;
            for(int i =0; i < input.Length;i++)
            {
                if (input[i] >= '0' && input[i] <= '9') r += input[i];
            }
            return r;
        }
        public static string ValidateTextInput(string input)
        {
            if (input == null) return "_object_";
            string r = null;
            for (int i = 0; i < input.Length; i++)
            {
                if (input[i] != ' ') r += input[i];
                else r += '_';
            }
            return r;
        }
    }
}
