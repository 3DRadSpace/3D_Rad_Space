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
            menuStrip.MouseEnter += SetFocusFalse;
            menuStrip.MouseLeave += SetFocusTrue;
            //File
            ToolStripMenuItem ms_file = new ToolStripMenuItem();
            ms_file.Text = "File";
            ms_file.MouseEnter += SetFocusFalse;
            ms_file.MouseLeave += SetFocusTrue;

            ToolStripMenuItem f_new = new ToolStripMenuItem();
            f_new.Text = "New project (Ctrl+N)";
            f_new.Click += F_new_Click;
            f_new.MouseEnter += SetFocusFalse;
            f_new.MouseLeave += SetFocusTrue;

            ToolStripMenuItem f_open = new ToolStripMenuItem();
            f_open.Text = "Open project (Ctrl+O)";
            f_open.Click += F_open_Click;
            f_open.MouseEnter += SetFocusFalse;
            f_open.MouseLeave += SetFocusTrue;

            ToolStripMenuItem f_save = new ToolStripMenuItem();
            f_save.Text = "Save Project (Ctrl+S)";
            f_save.Click += F_save_Click;
            f_save.MouseEnter += SetFocusFalse;
            f_save.MouseLeave += SetFocusTrue;

            ToolStripMenuItem f_save_as = new ToolStripMenuItem();
            f_save_as.Text = "Save Project As (Ctrl+Shift+S)";
            f_save_as.Click += F_save_as_Click;
            f_save_as.MouseEnter += SetFocusFalse;
            f_save_as.MouseLeave += SetFocusTrue;

            ToolStripMenuItem f_play = new ToolStripMenuItem();
            f_play.Text = "Play Project (Ctrl+F5)";
            f_play.Click += F_play_Click;
            f_play.MouseEnter += SetFocusFalse;
            f_play.MouseLeave += SetFocusTrue;

            ToolStripMenuItem f_compile = new ToolStripMenuItem();
            f_compile.Text = "Compile Project";
            f_compile.Click += F_compile_Click;
            f_compile.MouseEnter += SetFocusFalse;
            f_compile.MouseLeave += SetFocusTrue;

            ToolStripMenuItem f_exit = new ToolStripMenuItem();
            f_exit.Text = "Exit (Alt+F4)";
            f_exit.Click += F_exit_Click;
            f_exit.MouseEnter += SetFocusFalse;
            f_exit.MouseLeave += SetFocusTrue;

            ms_file.DropDownItems.AddRange(new ToolStripItem[] { f_new,f_open,f_save,f_save_as,f_play,f_compile,f_exit });

            ToolStripMenuItem ms_edit = new ToolStripMenuItem();
            ms_edit.Text = "Edit";
            ms_edit.MouseEnter += SetFocusFalse;
            ms_edit.MouseLeave += SetFocusTrue;

            ToolStripMenuItem e_addobj = new ToolStripMenuItem();
            e_addobj.Text = "Add Object (Ctrl+A)";
            e_addobj.Click += E_addobj_Click;
            e_addobj.MouseEnter += SetFocusFalse;
            e_addobj.MouseLeave += SetFocusTrue;

            ToolStripMenuItem e_addaddon = new ToolStripMenuItem();
            e_addaddon.Text = "Add addon ";
            e_addaddon.Click += E_addaddon_Click;
            e_addaddon.MouseEnter += SetFocusFalse;
            e_addaddon.MouseLeave += SetFocusTrue;

            ToolStripMenuItem e_undo = new ToolStripMenuItem();
            e_undo.Text = "Undo (Ctrl+Z)";
            e_undo.Click += E_undo_Click;
            e_undo.MouseEnter += SetFocusFalse;
            e_undo.MouseLeave += SetFocusTrue;

            ToolStripMenuItem e_redo = new ToolStripMenuItem();
            e_redo.Text = "Redo (Ctrl+X)";
            e_redo.Click += E_redo_Click;
            e_redo.MouseEnter += SetFocusFalse;
            e_redo.MouseLeave += SetFocusTrue;

            ToolStripMenuItem e_import = new ToolStripMenuItem();
            e_import.Text = "Import Resources...";
            e_import.Click += E_import_Click;
            e_import.MouseEnter += SetFocusFalse;
            e_import.MouseLeave += SetFocusTrue;

            ToolStripMenuItem e_reset3dcursor = new ToolStripMenuItem();
            e_reset3dcursor.Text = "Reset 3D Cursor";
            e_reset3dcursor.Click += E_reset3dcursor_Click;
            e_reset3dcursor.MouseEnter += SetFocusFalse;
            e_reset3dcursor.MouseLeave += SetFocusTrue;

            ms_edit.DropDownItems.AddRange(new ToolStripItem[] { e_addobj,e_addaddon,e_addaddon,e_undo,e_redo,e_import,e_reset3dcursor});

            ToolStripMenuItem ms_options = new ToolStripMenuItem();
            ms_options.Text = "Options";
            ms_options.MouseEnter += SetFocusFalse;
            ms_options.MouseLeave += SetFocusTrue;

            ToolStripMenuItem o_settings = new ToolStripMenuItem();
            o_settings.Text = "Settings...";
            o_settings.Click += O_settings_Click;
            o_settings.MouseEnter += SetFocusFalse;
            o_settings.MouseLeave += SetFocusTrue;

            ToolStripMenuItem o_checkforupdates = new ToolStripMenuItem();
            o_checkforupdates.Text = "Check for updates...";
            o_checkforupdates.Click += O_checkforupdates_Click;
            o_checkforupdates.MouseEnter += SetFocusFalse;
            o_checkforupdates.MouseLeave += SetFocusTrue;

            ms_options.DropDownItems.AddRange(new ToolStripItem[] { o_settings,o_checkforupdates});

            ToolStripMenuItem ms_help = new ToolStripMenuItem();
            ms_help.Text = "Help";
            ms_help.MouseEnter += SetFocusFalse;
            ms_help.MouseLeave += SetFocusTrue;

            ToolStripMenuItem h_about = new ToolStripMenuItem();
            h_about.Text = "About...";
            h_about.Click += H_about_Click;
            h_about.MouseEnter += SetFocusFalse;
            h_about.MouseLeave += SetFocusTrue;

            ToolStripMenuItem h_docs = new ToolStripMenuItem();
            h_docs.Text = "Documentation";
            h_docs.Click += H_docs_Click;
            h_docs.MouseEnter += SetFocusFalse;
            h_docs.MouseLeave += SetFocusTrue;

            ToolStripMenuItem h_web = new ToolStripMenuItem();
            h_web.Text = "Website";
            h_web.Click += H_web_Click;
            h_web.MouseEnter += SetFocusFalse;
            h_web.MouseLeave += SetFocusTrue;

            ToolStripMenuItem h_forum = new ToolStripMenuItem();
            h_forum.Text = "Forum";
            h_forum.Click += H_forum_Click;
            h_forum.MouseEnter += SetFocusFalse;
            h_forum.MouseLeave += SetFocusTrue;

            ToolStripMenuItem h_rbug = new ToolStripMenuItem();
            h_rbug.Text = "Report a bug...";
            h_rbug.Click += H_rbug_Click;
            h_rbug.MouseEnter += SetFocusFalse;
            h_rbug.MouseLeave += SetFocusTrue;

            ms_help.DropDownItems.AddRange(new ToolStripItem[] { h_about, h_docs, h_web, h_forum, h_rbug });

            menuStrip.Items.AddRange(new ToolStripItem[] { ms_file,ms_edit,ms_options,ms_help});

            //listView1 = VisualObjectsList
            VisualObjectsList = new ListView();
            VisualObjectsList.Location = new Point(0, 48);
            VisualObjectsList.Size = new Size(150, 600);
            VisualObjectsList.CheckBoxes = true;
            VisualObjectsList.MultiSelect = false;
            VisualObjectsList.View = View.List;
            MainWindow.Controls.Add(VisualObjectsList);

            //toolstrip
            toolStrip = new ToolStrip();
            toolStrip.MouseEnter += SetFocusFalse;
            toolStrip.MouseLeave += SetFocusTrue;

            ToolStripMenuItem ts_new = new ToolStripMenuItem();
            ts_new.Image = Image.FromFile("EngineData\\IconNewF.ico");
            ts_new.Text = "New";
            ts_new.Click += F_new_Click;

            ToolStripMenuItem ts_open = new ToolStripMenuItem();
            ts_open.Image = Image.FromFile("EngineData\\IconOpenF.ico");
            ts_open.Text = "Open";
            ts_open.Click += F_open_Click;

            ToolStripMenuItem ts_save = new ToolStripMenuItem();
            ts_save.Image = Image.FromFile("EngineData\\IconSaveF.ico");
            ts_save.Text = "Save";
            ts_save.Click += F_save_Click;

            ToolStripMenuItem ts_debug = new ToolStripMenuItem();
            ts_debug.Image = Image.FromFile("EngineData\\IconDebug.ico");
            ts_debug.Text = "Debug";
            ts_debug.Click += F_play_Click;

            ToolStripMenuItem ts_compile = new ToolStripMenuItem();
            ts_compile.Image = Image.FromFile("EngineData\\IconCompile.ico");
            ts_compile.Text = "Compile";
            ts_compile.Click += F_compile_Click;

            ToolStripButton ts_sw2d3d = new ToolStripButton();
            ts_sw2d3d.Image = Image.FromFile("EngineData\\IconSwitch2D3D.ico");
            ts_sw2d3d.Text = "Switch 2D/3D";
            ts_sw2d3d.CheckOnClick = true;
            ts_sw2d3d.Checked = true;
            ts_sw2d3d.CheckState = CheckState.Checked;
            ts_sw2d3d.CheckedChanged += Ts_sw2d3d_CheckedChanged;

            toolStrip.Items.AddRange(new ToolStripItem[] {ts_new,ts_open,ts_save,ts_debug,ts_compile,ts_sw2d3d });
            //reverse order because WinForms is switching some stuff with the HMENU pointers or smth
            MainWindow.Controls.Add(toolStrip);
            MainWindow.Controls.Add(menuStrip);

            //MainWindow
            MainWindow.Location = new Point(0, 0);
            MainWindow.WindowState = FormWindowState.Maximized;
            MainWindow.Resize += MainWindow_Resize;
        }
    }
}
