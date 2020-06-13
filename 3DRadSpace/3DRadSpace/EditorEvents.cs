using _3DRadSpaceDll;
using System;
using System.Collections.Generic;
using System.IO;
using System.Diagnostics;
using System.Net;
using Microsoft.Xna.Framework;
using System.Windows.Forms;
using System.Threading;


namespace _3DRadSpace
{
    partial class Editor : Microsoft.Xna.Framework.Game
    {
        public static GameSettings GraphcalSettings= new GameSettings();

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
                InitialDirectory = @"Projects",
                RestoreDirectory = true,
                AutoUpgradeEnabled = false,
                Multiselect = false
            };
            DialogResult b = openFile.ShowDialog();
            if(b == DialogResult.OK)
            {
                ClearObjects();
                _3DRadSpaceDll.Game.GameObjects = Project.Open(openFile.FileName);
                if(_3DRadSpaceDll.Game.GameObjects == null)
                {
                    MessageBox.Show("Opened file is not a valid 3DRadSpace project", "Error",MessageBoxButtons.OK,MessageBoxIcon.Error);
                    return;
                }
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
                InitialDirectory = @"Projects",
                RestoreDirectory = true,
                AutoUpgradeEnabled = false,
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
            Process p = Process.Start(process);
            p.WaitForExit();
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
                if(add.Result is Skinmesh s) s.Load(Content);
                if (add.Result is Sprite sp) sp.Load(Content,GraphicsDevice);
                if (add.Result is TextPrint tp) tp.Load(Content);
                if (add.Result is Skybox sb) sb.Load(Content, GraphicsDevice);
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
                InitialDirectory = @"Projects",
                RestoreDirectory = true,
                AutoUpgradeEnabled = false,
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
            ResourceWizard wizard = new ResourceWizard();
            wizard.ShowDialog();
            wizard.Dispose();
        }
        void checkforUpdatesEvent(object s,EventArgs a)
        {
            WebClient client = new WebClient();
            string v = client.DownloadString("https://drive.google.com/uc?export=download&id=0B9yRO5eZEvTjeHhPa05OZDRxUmM");
            bool NewVersionAvalable = false;
            for(int i =0; i < 3; i++)
            {
                if (Convert.ToInt32(v,Program.CultureInfo) != Program.Version)
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
                    _updating = true;
                    toolStripStatusLabel1.Text = "Status: Downloading new update...";
                    client.DownloadProgressChanged += Client_DownloadProgressChanged;
                    client.DownloadFileCompleted += Client_DownloadFileCompleted;
                    client.DownloadFileAsync(new Uri("https://drive.google.com/uc?export=download&id=0B9yRO5eZEvTjSVhCZndjSGRUcVE"), @"Setup.exe");
                    saveProject(null, null);
                    client.Dispose();
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

        private void Client_DownloadFileCompleted(object sender, System.ComponentModel.AsyncCompletedEventArgs e)
        {
            Process.Start(@"Setup.exe");
            Exit();
        }

        private void Client_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            toolStripStatusLabel1.Text = "Status: Downloading new update "+e.ProgressPercentage+" % ("+(e.BytesReceived / 1024)+" KB recieved / "+(e.TotalBytesToReceive/1024)+" KB total)";
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
            Settings = Settings_Load();
        }
        void openDocumentation(object a,EventArgs b)
        {
            Process.Start("https://3dradspace.tk/Documentation");
        }
        void officialWebsite(object a, EventArgs b)
        {
            Process.Start("https://3dradspace.tk");
        }
        void openForum(object a, EventArgs b)
        {
            Process.Start("https://3dradspace.tk/Forum/index.php");
        }
        void reportBug(object a,EventArgs args)
        {
            Process.Start("https://3dradspace.tk/Forum/index.php?board=9.0");
        }
        void M_EditObject(object a, EventArgs e)
        {
            EditObj();
            UpdateObjects();
        }
        void EditObj()
        {
            object b = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index];
            if (b is Script)
            {
                ScriptW scriptW = new ScriptW((Script)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index]);
                scriptW.ShowDialog();
                if (scriptW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = scriptW.Result;
                scriptW.Dispose();
                return;
            }
            if (b is FPVCamera fpv)
            {
                FPVCameraW wnd = new FPVCameraW(fpv);
                wnd.ShowDialog();
                if (wnd.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = wnd.Result;
                wnd.Dispose();
                return;
            }
            if (b is Camera)
            {
                CameraW cameraW = new CameraW((Camera)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index]);
                cameraW.ShowDialog();
                if (cameraW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = cameraW.Result;
                cameraW.Dispose();
                return;
            }
            if (b is SkyColor)
            {
                SkyColorW colorW = new SkyColorW((SkyColor)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index]);
                colorW.ShowDialog();
                if (colorW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = colorW.Result;
                colorW.Dispose();
                return;
            }
            if (b is Fog)
            {
                FogW fogW = new FogW((Fog)_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index]);
                fogW.ShowDialog();
                if (fogW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = fogW.Result;
                fogW.Dispose();
                return;
            }
            if (b is Skinmesh skn)
            {
                SkinmeshW skinmeshW = new SkinmeshW(skn);
                skinmeshW.ShowDialog();
                if (skinmeshW.Result != null)
                {
                    _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = skinmeshW.Result;
                    Skinmesh sk = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] as Skinmesh;
                    sk.Load(Content);
                }
                skinmeshW.Dispose();
                return;
            }
            if (b is Sprite sp)
            {
                SpriteW spriteW = new SpriteW(sp);
                spriteW.ShowDialog();
                if (spriteW.Result != null)
                {
                    _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = (Sprite)spriteW.Result;
                    Sprite s = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] as Sprite;
                    s.Load(Content, GraphicsDevice);
                }
                spriteW.Dispose();
                return;
            }
            if (b is TextPrint p)
            {
                TextPrintW textPrintW = new TextPrintW(p);
                textPrintW.ShowDialog();
                if (textPrintW.Result != null)
                {
                    p = (TextPrint)textPrintW.Result;
                    p.Load(Content);
                    _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = p;
                }
                textPrintW.Dispose();
                return;
            }
            if (b is SoundEffect se)
            {
                SoundEffectW soundEffectW = new SoundEffectW(se);
                soundEffectW.ShowDialog();
                if (soundEffectW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = soundEffectW.Result;
                soundEffectW.Dispose();
                return;
            }
            if (b is SoundSource soundSource)
            {
                SoundSourceW soundSourceW = new SoundSourceW(soundSource);
                soundSourceW.ShowDialog();
                if (soundSourceW.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = soundSourceW.Result;
                soundSourceW.Dispose();
                return;
            }
            if (b is EventOnLocation eol)
            {
                EventOnLocationW eolw = new EventOnLocationW(eol);
                eolw.ShowDialog();
                if (eolw.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = eolw.Result;
                eolw.Dispose();
                return;
            }
            if(b is EventOnKey eok)
            {
                EventOnKeyW eokw = new EventOnKeyW(eok);
                eokw.ShowDialog();
                if (eokw.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = eokw.Result;
                eokw.Dispose();
                return;
            }
            if(b is _3DRadSpaceDll.Timer t)
            {
                TimerW w = new TimerW(t);
                w.ShowDialog();
                if (w.Result != null) _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = w.Result;
                w.Dispose();
                return;
            }
            if(b is Skybox sb)
            {
                SkyBoxW skyboxW = new SkyBoxW(sb);
                skyboxW.ShowDialog();
                if (skyboxW.Result != null)
                {
                    _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] = (Skybox)skyboxW.Result;
                    Skybox s = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] as Skybox;
                    s.Load(Content, GraphicsDevice);
                }
                skyboxW.Dispose();
                return;
            }
        }
        void M_DeleteObject(object obj,EventArgs e)
        {
            if(_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] is SkyColor)
            {
                ClearColor = Color.Black;
            }
            if(_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] is Sprite sp)
            {
                sp.Dispose();
            }
            if (_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index] is Skybox sb)
            {
                sb.Dispose();
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
            int l = _3DRadSpaceDll.Game.GameObjects.Count;
            string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
            for(int i =0; i < files.Length;i++)
            {
                string[] ext = files[i].Split('.');
               if(ext[ext.Length- 1] == "3drsp") _3DRadSpaceDll.Game.GameObjects.AddRange(Project.Open(files[i]));
            }
            ProjectSaved = false;
            LoadAllObjects(l);
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
            if(mouse.Button == MouseButtons.Right && listBox1.SelectedItems.Count > 0)
            {
                contextMenuStrip1.Show(GameWindow.Location.X+listBox1.Location.X, Cursor.Position.Y);
            }
        }
        bool _updating = false;
        void Editor_Exiting(object sender, FormClosingEventArgs e)
        {
            if(Settings[1] == true && ProjectSaved == false && !_updating)
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
            ClearColor = Color.Black;
            for (int i =0; i < _3DRadSpaceDll.Game.GameObjects.Count;i++)
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
            FogEnabled = false;
            UpdateObjects();
        }
        void LoadAllObjects()
        {
            for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
            {
                if (_3DRadSpaceDll.Game.GameObjects[i] is Camera c) c.Load(null);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Skinmesh sk) sk.Load(Content);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Sprite sp) sp.Load(Content, GraphicsDevice);
                if (_3DRadSpaceDll.Game.GameObjects[i] is TextPrint tp) tp.Load(Content);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Skybox sb) sb.Load(Content, GraphicsDevice);
            }
        }
        void LoadAllObjects(int offset)
        {
            for (int i = offset; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
            {
                if (_3DRadSpaceDll.Game.GameObjects[i] is Camera c) c.Load(null);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Skinmesh sk) sk.Load(Content);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Sprite sp) sp.Load(Content, GraphicsDevice);
                if (_3DRadSpaceDll.Game.GameObjects[i] is TextPrint tp) tp.Load(Content);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Skybox sb) sb.Load(Content, GraphicsDevice);
            }
        }
        private void ListBox1_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            e.Handled = true;
        }

        private void GameWindow_SizeChanged(object sender, EventArgs e)
        {
            listBox1.ClientSize = new System.Drawing.Size(listBox1.ClientSize.Width, GameWindow.ClientSize.Height - (int)(2.3*statusStrip1.Size.Height));
        }
        //int _oldindex = 0;
        private void ListBox1_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            if (_deselect) return;

            if (listBox1.SelectedItems.Count == 0)
            {
                if (listBox1.Items[e.Index].Checked != false) e.NewValue = CheckState.Unchecked;
                return;
            }
            GameObject o = _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index];
            if (e.NewValue == CheckState.Unchecked)
            {
                if (o is EventOnLocation eol)
                {
                    for (int i = 0; i < eol.Behiavours.Count; i++)
                    {
                        if (eol.SelectedObjects[i] == listBox1.SelectedItems[0].Index)
                        {
                            eol.Behiavours.RemoveAt(i);
                            break;
                        }
                    }
                }
                if (o is EventOnKey eok)
                {
                    for (int j = 0; j < eok.Behiavours.Count; j++)
                    {
                        if (eok.SelectedObjects[j] == listBox1.SelectedItems[0].Index)
                        {
                            eok.Behiavours.RemoveAt(j);
                            break;
                        }
                    }
                }
                if (o is _3DRadSpaceDll.Timer t)
                {
                    for (int i = 0; i < t.Behiavours.Count; i++)
                    {
                        if (t.SelectedObjects[i] == listBox1.SelectedItems[0].Index)
                        {
                            t.Behiavours.RemoveAt(i);
                            break;
                        }
                    }
                }
                else
                {
                    for (int i=0; i < o.Behiavours.Count; i++)
                    {
                        if (o.Behiavours[i].ObjectID == listBox1.SelectedItems[0].Index)
                        {
                            o.Behiavours.RemoveAt(i);
                            break;
                        }
                    }
                }
            }
            else if (e.NewValue == CheckState.Checked)
            {
                if (o is EventOnLocation eol) eol.SelectedObjects.Add(e.Index );
                if (o is EventOnKey eok) eok.SelectedObjects.Add(e.Index);
                if (o is _3DRadSpaceDll.Timer t) t.SelectedObjects.Add(e.Index);
                else o.Behiavours.Add(new ObjectBehiavour(e.Index));
            }
        }
        bool _deselect;
        private void ListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            _deselect = true;
            for(int i =0; i < listBox1.Items.Count; i++)
            {
                listBox1.Items[i].Checked = false;
            }
            if (listBox1.SelectedItems.Count > 0 )
            {
                for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index].SelectedObjects.Count; i++)
                {
                    listBox1.Items[_3DRadSpaceDll.Game.GameObjects[listBox1.SelectedItems[0].Index].SelectedObjects[i]].Checked = true;
                }
            }
            _deselect = false;
        }
    }
}
