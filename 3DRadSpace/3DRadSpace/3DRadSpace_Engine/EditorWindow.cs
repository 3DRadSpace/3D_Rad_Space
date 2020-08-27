using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpace_Engine
{
    partial class Editor : Microsoft.Xna.Framework.Game
    {
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EditorWindow_winforms));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.Menu = new System.Windows.Forms.ToolStripMenuItem();
            this.MI_newProj = new System.Windows.Forms.ToolStripMenuItem();
            this.MI_OpenProject = new System.Windows.Forms.ToolStripMenuItem();
            this.MI_RecentProj = new System.Windows.Forms.ToolStripMenuItem();
            this.I_P1 = new System.Windows.Forms.ToolStripMenuItem();
            this.I_P2 = new System.Windows.Forms.ToolStripMenuItem();
            this.I_P3 = new System.Windows.Forms.ToolStripMenuItem();
            this.I_P4 = new System.Windows.Forms.ToolStripMenuItem();
            this.I_P5 = new System.Windows.Forms.ToolStripMenuItem();
            this.I_P6 = new System.Windows.Forms.ToolStripMenuItem();
            this.I_P7 = new System.Windows.Forms.ToolStripMenuItem();
            this.I_P8 = new System.Windows.Forms.ToolStripMenuItem();
            this.I_P9 = new System.Windows.Forms.ToolStripMenuItem();
            this.I_P10 = new System.Windows.Forms.ToolStripMenuItem();
            this.MI_saveProj = new System.Windows.Forms.ToolStripMenuItem();
            this.MI_SaveProjAs = new System.Windows.Forms.ToolStripMenuItem();
            this.MI_DebugProj = new System.Windows.Forms.ToolStripMenuItem();
            this.MI_CompileG = new System.Windows.Forms.ToolStripMenuItem();
            this.MI_Exit = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addObjectCtrlAToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addAddonToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addResourcesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.reset3DCursorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.checkForUpdatesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.settingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.forumToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.websiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.discordToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.Switch2D3DButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.DebugButton = new System.Windows.Forms.ToolStripButton();
            this.menuStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.EditorWindow.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Menu,
            this.editToolStripMenuItem,
            this.optionsToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // Menu
            // 
            this.Menu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MI_newProj,
            this.MI_OpenProject,
            this.MI_RecentProj,
            this.MI_saveProj,
            this.MI_SaveProjAs,
            this.MI_DebugProj,
            this.MI_CompileG,
            this.MI_Exit});
            this.Menu.Name = "Menu";
            this.Menu.Size = new System.Drawing.Size(46, 24);
            this.Menu.Text = "File";
            // 
            // MI_newProj
            // 
            this.MI_newProj.Name = "MI_newProj";
            this.MI_newProj.Size = new System.Drawing.Size(288, 26);
            this.MI_newProj.Text = "New Project (Ctrl+N)";
            this.MI_newProj.Click += new System.EventHandler(this.newProjClick);
            // 
            // MI_OpenProject
            // 
            this.MI_OpenProject.Name = "MI_OpenProject";
            this.MI_OpenProject.Size = new System.Drawing.Size(288, 26);
            this.MI_OpenProject.Text = "Open Project (Ctrl+O)";
            this.MI_OpenProject.Click += new System.EventHandler(this.openProjClick);
            // 
            // MI_RecentProj
            // 
            this.MI_RecentProj.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.I_P1,
            this.I_P2,
            this.I_P3,
            this.I_P4,
            this.I_P5,
            this.I_P6,
            this.I_P7,
            this.I_P8,
            this.I_P9,
            this.I_P10});
            this.MI_RecentProj.Name = "MI_RecentProj";
            this.MI_RecentProj.Size = new System.Drawing.Size(288, 26);
            this.MI_RecentProj.Text = "Recent Projects";
            // 
            // I_P1
            // 
            this.I_P1.Name = "I_P1";
            this.I_P1.Size = new System.Drawing.Size(116, 26);
            this.I_P1.Text = "P1";
            // 
            // I_P2
            // 
            this.I_P2.Name = "I_P2";
            this.I_P2.Size = new System.Drawing.Size(116, 26);
            this.I_P2.Text = "P2";
            // 
            // I_P3
            // 
            this.I_P3.Name = "I_P3";
            this.I_P3.Size = new System.Drawing.Size(116, 26);
            this.I_P3.Text = "P3";
            // 
            // I_P4
            // 
            this.I_P4.Name = "I_P4";
            this.I_P4.Size = new System.Drawing.Size(116, 26);
            this.I_P4.Text = "P4";
            // 
            // I_P5
            // 
            this.I_P5.Name = "I_P5";
            this.I_P5.Size = new System.Drawing.Size(116, 26);
            this.I_P5.Text = "P5";
            // 
            // I_P6
            // 
            this.I_P6.Name = "I_P6";
            this.I_P6.Size = new System.Drawing.Size(116, 26);
            this.I_P6.Text = "P6";
            // 
            // I_P7
            // 
            this.I_P7.Name = "I_P7";
            this.I_P7.Size = new System.Drawing.Size(116, 26);
            this.I_P7.Text = "P7";
            // 
            // I_P8
            // 
            this.I_P8.Name = "I_P8";
            this.I_P8.Size = new System.Drawing.Size(116, 26);
            this.I_P8.Text = "P8";
            // 
            // I_P9
            // 
            this.I_P9.Name = "I_P9";
            this.I_P9.Size = new System.Drawing.Size(116, 26);
            this.I_P9.Text = "P9";
            // 
            // I_P10
            // 
            this.I_P10.Name = "I_P10";
            this.I_P10.Size = new System.Drawing.Size(116, 26);
            this.I_P10.Text = "P10";
            // 
            // MI_saveProj
            // 
            this.MI_saveProj.Name = "MI_saveProj";
            this.MI_saveProj.Size = new System.Drawing.Size(288, 26);
            this.MI_saveProj.Text = "Save Project (Ctrl+S)";
            this.MI_saveProj.Click += new System.EventHandler(this.saveProjClick);
            // 
            // MI_SaveProjAs
            // 
            this.MI_SaveProjAs.Name = "MI_SaveProjAs";
            this.MI_SaveProjAs.Size = new System.Drawing.Size(288, 26);
            this.MI_SaveProjAs.Text = "Save Project As (Shift+Ctrl+S)";
            this.MI_SaveProjAs.Click += new System.EventHandler(this.saveProjAsClick);
            // 
            // MI_DebugProj
            // 
            this.MI_DebugProj.Name = "MI_DebugProj";
            this.MI_DebugProj.Size = new System.Drawing.Size(288, 26);
            this.MI_DebugProj.Text = "Play Project (F5)";
            this.MI_DebugProj.Click += new System.EventHandler(this.playProjClick);
            // 
            // MI_CompileG
            // 
            this.MI_CompileG.Name = "MI_CompileG";
            this.MI_CompileG.Size = new System.Drawing.Size(288, 26);
            this.MI_CompileG.Text = "Compile Project (Ctrl+B)";
            this.MI_CompileG.Click += new System.EventHandler(this.compileProjClick);
            // 
            // MI_Exit
            // 
            this.MI_Exit.Name = "MI_Exit";
            this.MI_Exit.Size = new System.Drawing.Size(288, 26);
            this.MI_Exit.Text = "Exit (Alt+F4)";
            this.MI_Exit.Click += new System.EventHandler(this.ExitClick);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addObjectCtrlAToolStripMenuItem,
            this.addAddonToolStripMenuItem,
            this.addResourcesToolStripMenuItem,
            this.reset3DCursorToolStripMenuItem});
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(49, 24);
            this.editToolStripMenuItem.Text = "Edit";
            // 
            // addObjectCtrlAToolStripMenuItem
            // 
            this.addObjectCtrlAToolStripMenuItem.Name = "addObjectCtrlAToolStripMenuItem";
            this.addObjectCtrlAToolStripMenuItem.Size = new System.Drawing.Size(225, 26);
            this.addObjectCtrlAToolStripMenuItem.Text = "Add Object (Ctrl+A)";
            this.addObjectCtrlAToolStripMenuItem.Click += new System.EventHandler(this.addObjectClick);
            // 
            // addAddonToolStripMenuItem
            // 
            this.addAddonToolStripMenuItem.Name = "addAddonToolStripMenuItem";
            this.addAddonToolStripMenuItem.Size = new System.Drawing.Size(225, 26);
            this.addAddonToolStripMenuItem.Text = "Add Addon";
            this.addAddonToolStripMenuItem.Click += new System.EventHandler(this.addAddon_Click);
            // 
            // addResourcesToolStripMenuItem
            // 
            this.addResourcesToolStripMenuItem.Name = "addResourcesToolStripMenuItem";
            this.addResourcesToolStripMenuItem.Size = new System.Drawing.Size(225, 26);
            this.addResourcesToolStripMenuItem.Text = "Add Resource(s)";
            this.addResourcesToolStripMenuItem.Click += new System.EventHandler(this.addResourcesClick);
            // 
            // reset3DCursorToolStripMenuItem
            // 
            this.reset3DCursorToolStripMenuItem.Name = "reset3DCursorToolStripMenuItem";
            this.reset3DCursorToolStripMenuItem.Size = new System.Drawing.Size(225, 26);
            this.reset3DCursorToolStripMenuItem.Text = "Reset 3D Cursor";
            this.reset3DCursorToolStripMenuItem.Click += new System.EventHandler(this.reset3DCursor);
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.checkForUpdatesToolStripMenuItem,
            this.settingsToolStripMenuItem});
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(75, 24);
            this.optionsToolStripMenuItem.Text = "Options";
            // 
            // checkForUpdatesToolStripMenuItem
            // 
            this.checkForUpdatesToolStripMenuItem.Name = "checkForUpdatesToolStripMenuItem";
            this.checkForUpdatesToolStripMenuItem.Size = new System.Drawing.Size(211, 26);
            this.checkForUpdatesToolStripMenuItem.Text = "Check for updates";
            this.checkForUpdatesToolStripMenuItem.Click += new System.EventHandler(this.checkForUpdates);
            // 
            // settingsToolStripMenuItem
            // 
            this.settingsToolStripMenuItem.Name = "settingsToolStripMenuItem";
            this.settingsToolStripMenuItem.Size = new System.Drawing.Size(211, 26);
            this.settingsToolStripMenuItem.Text = "Settings";
            this.settingsToolStripMenuItem.Click += new System.EventHandler(this.OpenSettings);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem,
            this.forumToolStripMenuItem,
            this.websiteToolStripMenuItem,
            this.discordToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(55, 24);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(145, 26);
            this.aboutToolStripMenuItem.Text = "About...";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.OpenAboutW);
            // 
            // forumToolStripMenuItem
            // 
            this.forumToolStripMenuItem.Name = "forumToolStripMenuItem";
            this.forumToolStripMenuItem.Size = new System.Drawing.Size(145, 26);
            this.forumToolStripMenuItem.Text = "Forum";
            this.forumToolStripMenuItem.Click += new System.EventHandler(this.OpenForum);
            // 
            // websiteToolStripMenuItem
            // 
            this.websiteToolStripMenuItem.Name = "websiteToolStripMenuItem";
            this.websiteToolStripMenuItem.Size = new System.Drawing.Size(145, 26);
            this.websiteToolStripMenuItem.Text = "Website";
            this.websiteToolStripMenuItem.Click += new System.EventHandler(this.OpenWebsite);
            // 
            // discordToolStripMenuItem
            // 
            this.discordToolStripMenuItem.Name = "discordToolStripMenuItem";
            this.discordToolStripMenuItem.Size = new System.Drawing.Size(145, 26);
            this.discordToolStripMenuItem.Text = "Discord";
            this.discordToolStripMenuItem.Click += new System.EventHandler(this.OpenDiscord);
            // 
            // toolStrip1
            // 
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabel1,
            this.Switch2D3DButton,
            this.toolStripSeparator1,
            this.DebugButton});
            this.toolStrip1.Location = new System.Drawing.Point(0, 28);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(800, 27);
            this.toolStrip1.TabIndex = 1;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(96, 24);
            this.toolStripLabel1.Text = "3D/2D Mode";
            // 
            // Switch2D3DButton
            // 
            this.Switch2D3DButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Switch2D3DButton.Image = ((System.Drawing.Image)(resources.GetObject("Switch2D3DButton.Image")));
            this.Switch2D3DButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Switch2D3DButton.Name = "Switch2D3DButton";
            this.Switch2D3DButton.Size = new System.Drawing.Size(29, 24);
            this.Switch2D3DButton.Text = "toolStripButton1";
            this.Switch2D3DButton.Click += new System.EventHandler(this.Switch2D3D);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 27);
            // 
            // DebugButton
            // 
            this.DebugButton.Image = ((System.Drawing.Image)(resources.GetObject("DebugButton.Image")));
            this.DebugButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.DebugButton.Name = "DebugButton";
            this.DebugButton.Size = new System.Drawing.Size(78, 24);
            this.DebugButton.Text = "Debug";
            this.DebugButton.Click += new System.EventHandler(this.playProjClick);
            // 
            // EditorWindow_winforms
            // 
            EditorWindow.Controls.Add(this.toolStrip1);
            EditorWindow.Controls.Add(this.menuStrip1);
            EditorWindow.MainMenuStrip = this.menuStrip1;
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            EditorWindow.ResumeLayout(false);
            EditorWindow.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem Menu;
        private System.Windows.Forms.ToolStripMenuItem MI_newProj;
        private System.Windows.Forms.ToolStripMenuItem MI_OpenProject;
        private System.Windows.Forms.ToolStripMenuItem MI_RecentProj;
        private System.Windows.Forms.ToolStripMenuItem MI_saveProj;
        private System.Windows.Forms.ToolStripMenuItem I_P1;
        private System.Windows.Forms.ToolStripMenuItem I_P2;
        private System.Windows.Forms.ToolStripMenuItem I_P3;
        private System.Windows.Forms.ToolStripMenuItem I_P4;
        private System.Windows.Forms.ToolStripMenuItem I_P5;
        private System.Windows.Forms.ToolStripMenuItem I_P6;
        private System.Windows.Forms.ToolStripMenuItem I_P7;
        private System.Windows.Forms.ToolStripMenuItem I_P8;
        private System.Windows.Forms.ToolStripMenuItem I_P9;
        private System.Windows.Forms.ToolStripMenuItem MI_SaveProjAs;
        private System.Windows.Forms.ToolStripMenuItem MI_DebugProj;
        private System.Windows.Forms.ToolStripMenuItem MI_CompileG;
        private System.Windows.Forms.ToolStripMenuItem MI_Exit;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addObjectCtrlAToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addAddonToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addResourcesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem reset3DCursorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem checkForUpdatesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem settingsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem forumToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem websiteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem discordToolStripMenuItem;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripButton Switch2D3DButton;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton DebugButton;
        private System.Windows.Forms.ToolStripMenuItem I_P10;
    }
}

