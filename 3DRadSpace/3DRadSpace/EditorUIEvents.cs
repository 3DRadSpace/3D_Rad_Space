using System;
using Lib3DRadSpace_DX;
using System.Windows.Forms;
using System.Diagnostics;
using System.Net;
using Microsoft.Xna.Framework;

namespace _3DRadSpace
{
    public partial class Main
    {
        private void F_new_Click(object sender, EventArgs e)
        {
            DeleteAllObjects();
        }
        void DeleteAllObjects()
        {
            CurrentProject.GameObjects.Clear();
            VisualObjectsList.Items.Clear();
            Saved = true;
        }
        private void F_open_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofn = new OpenFileDialog()
            {
                Filter = "3DRadSpace Project(*.3drsp)|*.3drsp",
                Multiselect = false,
                Title = "Open a 3DRadSpace project"
            };
            if(ofn.ShowDialog() == DialogResult.OK)
            {
                CurrentProject.Open(ofn.FileName);
                Saved = true;
            }
            ofn.Dispose();
        }
        private void F_save_Click(object sender, EventArgs e)
        {
            if (LoadedFIle == null) F_save_as_Click(sender, e);
            else CurrentProject.Save(LoadedFIle);
            Saved = true;
        }

        private void F_save_as_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog()
            {
                Filter = "3DRadSpace Project(*.3drsp)|*.3drsp",
                Title = "Save your 3DRadSpace project",
                OverwritePrompt = true
            };
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                CurrentProject.Save(sfd.FileName);
                Saved = true;
            }
        }

        private void F_compile_Click(object sender, EventArgs e)
        {
            
        }

        private void F_exit_Click(object sender, EventArgs e)
        {
            if (!Saved)
            {
                DialogResult r = MessageBox.Show("Your project isn't saved. Unsaved progress will be lost. \r\n Save the project?", "Unsaved project.", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Warning);
                switch (r)
                {
                    case DialogResult.Yes:
                        F_save_as_Click(null, null);
                        break;
                    case DialogResult.No:
                        Exit();
                        break;
                    default: break;
                }
            }
            else Exit();
        }

        private void F_play_Click(object sender, EventArgs e)
        {
            //Process.Start("", "");
        }
        private void H_rbug_Click(object sender, EventArgs e)
        {
            Process.Start("https://3dradspace.tk/Forum/index.php?board=9.0");
        }

        private void H_forum_Click(object sender, EventArgs e)
        {
            Process.Start("https://3dradspace.tk/Forum/index.php?");
        }

        private void H_web_Click(object sender, EventArgs e)
        {
            Process.Start("https://3dradspace.tk/");
        }

        private void H_docs_Click(object sender, EventArgs e)
        {
            Process.Start("https://3dradspace.tk/Wiki/");
        }

        private void H_about_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        private void O_checkforupdates_Click(object sender, EventArgs e)
        {
            WebClient client = new WebClient();
            string version = client.DownloadString("https://3dradspace.tk/UpdateVersion.txt");
            if(version != Program.Version)
            {
                client.DownloadFile("https://3dradspace.tk/", @"null.txt");
            }
            client.Dispose();
        }

        private void O_settings_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        private void E_reset3dcursor_Click(object sender, EventArgs e)
        {
            _cursor = Vector3.Zero;
        }

        private void E_import_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        private void E_redo_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        private void E_undo_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        private void E_addaddon_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofn = new OpenFileDialog()
            {
                Filter = "3DRadSpace Project(*.3drsp)|*.3drsp",
                Multiselect = false,
                Title = "Open a 3DRadSpace project as a addon."
            };
            if(ofn.ShowDialog() == DialogResult.OK)
            {
                CurrentProject.Add(ofn.FileName);
                Saved = false;
            }
        }

        private void E_addobj_Click(object sender, EventArgs e)
        {
            AddObjectWnd addObj = new AddObjectWnd();
            addObj.ShowDialog();
            if(addObj.DialogResult == DialogResult.OK)
            {
                AddObject(addObj.Result);
                addObj.Result.Load(Content);
            }
            addObj.Dispose();
        }
        private void Ts_sw2d3d_CheckedChanged(object sender, EventArgs e)
        {
            _3DMode = !_3DMode;
        }
        private void MainWindow_Resize(object sender, EventArgs e)
        {
            VisualObjectsList.Size = new System.Drawing.Size(150, MainWindow.Size.Height-50);
        }
        void SetFocusFalse(object sender,EventArgs e)
        {
            _3dviewfocus = false;
        }
        void SetFocusTrue(object sender,EventArgs e)
        {
            _3dviewfocus = true;
        }
        void AddObject(BaseGameObject obj)
        {
            CurrentProject.GameObjects.Add(obj);
            VisualObjectsList.Items.Add(obj.Name);
        }
    }
}
