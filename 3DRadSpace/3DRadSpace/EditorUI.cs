using System;
using System.Windows.Forms;
using System.Drawing;

namespace _3DRadSpace
{
    public partial class Main
    {
        ListView VisualObjectsList;
        MenuStrip menuStrip;
        ToolStrip toolStrip;
        void InitializeComponents()
        {
            //menuStrip
            menuStrip = new MenuStrip();
            //File
            MenuItem ms_file = new MenuItem();
            ms_file.Text = "File";

            MenuItem f_new = new MenuItem();
            f_new.Name = "New";
            f_new.Click += F_new_Click;

            MenuItem f_open = new MenuItem();
            f_open.Name = "Open";
            f_open.Click += F_open_Click;

            ms_file.MenuItems.AddRange(new MenuItem[] { f_new, f_open });

            //menuStrip.Items.AddRange(new MenuItem[] { ms_file});

            //listView1 = VisualObjectsList
            VisualObjectsList = new ListView();
            VisualObjectsList.Location = new Point(0, 25);
            VisualObjectsList.Size = new Size(150, 600);
            VisualObjectsList.CheckBoxes = true;
            MainWindow.Controls.Add(VisualObjectsList);
        }
    }
}
