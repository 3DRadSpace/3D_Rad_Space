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
        GameSettings GraphcalSettings;

        bool ProjectSaved = true;
        void newProject(object a,EventArgs e)
        {
            saveProject(null, null);
            ClearObjects();
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
                ClearObjects();
                _3DRadSpaceDll.Game.GameObjects = Project.Open(openFile.FileName);
                LoadAllObjects();
                UpdateObjects();
                ProjectSaved = true;
                OpenedFile = openFile.FileName;
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
                if (add.Result is TextPrint tp) tp.Load(Content);
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
                List<GameObject> c = Project.Open(openFile.FileName);
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
            object b = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index];
            if(b is Script)
            {
                ScriptW scriptW = new ScriptW((Script)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index]);
                scriptW.ShowDialog();
                if (scriptW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = scriptW.Result;
                scriptW.Dispose();
            }
            if (b is Camera)
            {
                CameraW cameraW = new CameraW((Camera)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index]);
                cameraW.ShowDialog();
                if (cameraW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = cameraW.Result;
                cameraW.Dispose();
            }
            if(b is SkyColor)
            {
                SkyColorW colorW = new SkyColorW((SkyColor)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index]);
                colorW.ShowDialog();
                if (colorW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = colorW.Result;
                colorW.Dispose();
            }
            if(b is Fog)
            {
                FogW fogW = new FogW((Fog)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index]);
                fogW.ShowDialog();
                if (fogW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = fogW.Result;
                fogW.Dispose();
            }
            if(b is Skinmesh)
            {
                SkinmeshW skinmeshW = new SkinmeshW((Skinmesh)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index]);
                skinmeshW.ShowDialog();
                if (skinmeshW.Result != null)
                {
                    _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = skinmeshW.Result;
                    Skinmesh sk = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] as Skinmesh;
                    sk.Load(Content);
                }
                skinmeshW.Dispose();
            }
            if( b is Sprite)
            {
                SpriteW spriteW = new SpriteW((Sprite)b);
                spriteW.ShowDialog();
                if (spriteW.Result != null)
                {
                    _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = (Sprite)spriteW.Result;
                    Sprite s = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] as Sprite;
                    s.Load(Content,GraphicsDevice);
                }
                spriteW.Dispose();
            }
            if( b is TextPrint p)
            {
                TextPrintW textPrintW = new TextPrintW((TextPrint)b);
                textPrintW.ShowDialog();
                if(textPrintW.Result != null)
                {
                    p = (TextPrint)textPrintW.Result;
                    p.Load(Content);
                    _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = p;
                }
                textPrintW.Dispose();
            }
            if(b is SoundEffect)
            {
                SoundEffectW soundEffectW = new SoundEffectW((SoundEffect)b);
                soundEffectW.ShowDialog();
                if (soundEffectW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = soundEffectW.Result;
                soundEffectW.Dispose();
            }
            if(b is GameSettings settings)
            {
                GraphcalSettings = settings;
            }
            UpdateObjects();
        }
        void M_DeleteObject(object obj,EventArgs e)
        {
            if(_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] is SkyColor s)
            {
                ClearColor = Color.Black;
            }
            if(_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] is Sprite sp)
            {
                sp.Dispose();
            }
            if (_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] is TextPrint tp) tp.Dispose();
            _3DRadSpaceDll.Game.GameObjects.RemoveAt(listBox1.SelectedItems[0].Index);
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
                GameObject obj = _3DRadSpaceDll.Game.GameObjects[i];
                if(obj) listBox1.Items.Add(obj.Name);
            }
        }
        void listBox1_MouseDown(object sender,MouseEventArgs mouse)
        {
            if(mouse.Button == MouseButtons.Right && listBox1.SelectedItems[0].Index != -1)
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
            if (input == null) return "0";
            string r = null;
            for(int i =0; i < input.Length;i++)
            {
                if (input[i] >= '0' && input[i] <= '9') r += input[i];
                if (input[i] == '.') r += input[i];
                if (input[i] == '-') r += input[i];
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
        void ClearObjects()
        {
            for(int i =0; i < _3DRadSpaceDll.Game.GameObjects.Count;i++)
            {
                if(_3DRadSpaceDll.Game.GameObjects[i] is Sprite sp)
                {
                    sp.Dispose();
                }
                if (_3DRadSpaceDll.Game.GameObjects[i] is TextPrint tp)
                {
                    tp.Dispose();
                }
            }
            _3DRadSpaceDll.Game.GameObjects.Clear();
            UpdateObjects();
        }
        void LoadAllObjects()
        {
            for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
            {
                if (_3DRadSpaceDll.Game.GameObjects[i] is Camera c) c.Load(null);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Script script) script.Load(null);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Skinmesh sk) sk.Load(Content);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Sprite sp) sp.Load(Content, GraphicsDevice);
                if (_3DRadSpaceDll.Game.GameObjects[i] is TextPrint tp) tp.Load(Content);
            }
        }
        private void ListBox1_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            e.Handled = true;
        }

        private void GameWindow_SizeChanged(object sender, EventArgs e)
        {
            listBox1.ClientSize = new System.Drawing.Size(listBox1.ClientSize.Width, GameWindow.ClientSize.Height - 44);
        }
        //int _oldindex = 0;
        private void ListBox1_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            if(listBox1.SelectedItems == null)
            {
                listBox1.Items[e.Index].Checked = false;
                return;
            }
            int i = 0;
            GameObject o = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index];
            if (e.NewValue == CheckState.Unchecked)
            {
                for (; i < o.Behiavours.Count; i++)
                {
                    if (o.Behiavours[i].ObjectID == listBox1.SelectedItems[0].Index)
                    {
                        o.Behiavours.RemoveAt(i);
                        break;
                    }
                }
            }
            else o.Behiavours.Add(new ObjectBehiavour(e.Index));
        }
        private void ListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //_oldindex = listBox1.TabIndex;
        }
    }
}
