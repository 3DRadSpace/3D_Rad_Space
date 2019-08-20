using _3DRadSpaceDll;
using System;
using Microsoft.Xna.Framework;
using System.Windows.Forms;


namespace _3DRadSpace
{
    partial class Editor : Microsoft.Xna.Framework.Game
    {
        void newProject(object a,EventArgs e)
        {
            //Open wizard.
        }
        void openProject(object a,EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
                Title = "Open a 3DRadSpace project",
                Filter = "3DRadSpace Project (*.3drsp) | (.*3drsp)"
            };
            DialogResult b = openFile.ShowDialog();
            if(b == DialogResult.OK)
            {

            }
        }
        void saveProject(object a,EventArgs e)
        {

        }
        void saveProjectAs(object a,EventArgs e)
        {

        }
        void playProject(object a,EventArgs e)
        {

        }
        void exitEditor(object a,EventArgs e)
        {
            Application.Exit();
        }
        void compileProject(object a,EventArgs e)
        {

        }
        void addObject(object a,EventArgs e)
        {

        }
        void addAddon(object a,EventArgs e)
        {

        }
        void installResources(object a,EventArgs e)
        {

        }
        void checkforUpdatesEvent(object s,EventArgs a)
        {

        }
        void aboutBoxOpen(object a, EventArgs e)
        {

        }
        void settingsOpen(object a, EventArgs e)
        {

        }
        void openDocumentation(object a,EventArgs b)
        {

        }
        void officialWebsite(object a, EventArgs b)
        {

        }
        void openForum(object a, EventArgs b)
        {

        }
        void reportBug(object a,EventArgs args)
        {

        }
        void M_EditObject(object a,EventArgs e)
        {

        }
        void M_DeleteObject(object obj,EventArgs e)
        {

        }
    }
}
