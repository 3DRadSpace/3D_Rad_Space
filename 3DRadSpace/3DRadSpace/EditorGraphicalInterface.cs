using _3DRadSpaceDll;
using System;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpace
{
    /// <summary>
    /// Developer note: Copied from the EditorUI.cs, only events were added manually.
    /// </summary>
    partial class Editor : Microsoft.Xna.Framework.Game
    {
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openCtrlOToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveCtrlSToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveProjectAsCtrlShitSToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem playProjectCtrlPToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem compileProjectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem objectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addAObjectCtrlAToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addAAddonToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem installResourcesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem checkForUpdatesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem settingsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem documentationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem officialWebsiteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem forumToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem reportABugToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripMenuItem editObjectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteObjectToolStripMenuItem;

        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openCtrlOToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveCtrlSToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveProjectAsCtrlShitSToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.playProjectCtrlPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.compileProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.objectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addAObjectCtrlAToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addAAddonToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.installResourcesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.checkForUpdatesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.settingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.documentationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.officialWebsiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.forumToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.reportABugToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.editObjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteObjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            GameWindow.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.objectToolStripMenuItem,
            this.optionsToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(784, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openCtrlOToolStripMenuItem,
            this.saveCtrlSToolStripMenuItem,
            this.saveProjectAsCtrlShitSToolStripMenuItem,
            this.playProjectCtrlPToolStripMenuItem,
            this.compileProjectToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(226, 22);
            this.newToolStripMenuItem.Text = "&New Project (Ctrl+N)";
            newToolStripMenuItem.Click += newProject;
            // 
            // openCtrlOToolStripMenuItem
            // 
            this.openCtrlOToolStripMenuItem.Name = "openCtrlOToolStripMenuItem";
            this.openCtrlOToolStripMenuItem.Size = new System.Drawing.Size(226, 22);
            this.openCtrlOToolStripMenuItem.Text = "&Open Project (Ctrl+O)";
            openCtrlOToolStripMenuItem.Click += openProject;
            // 
            // saveCtrlSToolStripMenuItem
            // 
            this.saveCtrlSToolStripMenuItem.Name = "saveCtrlSToolStripMenuItem";
            this.saveCtrlSToolStripMenuItem.Size = new System.Drawing.Size(226, 22);
            this.saveCtrlSToolStripMenuItem.Text = "&Save Project (Ctrl+S)";
            saveCtrlSToolStripMenuItem.Click += saveProject;
            // 
            // saveProjectAsCtrlShitSToolStripMenuItem
            // 
            this.saveProjectAsCtrlShitSToolStripMenuItem.Name = "saveProjectAsCtrlShitSToolStripMenuItem";
            this.saveProjectAsCtrlShitSToolStripMenuItem.Size = new System.Drawing.Size(226, 22);
            this.saveProjectAsCtrlShitSToolStripMenuItem.Text = "Save Project As (Ctrl+Shit+S)";
            saveProjectAsCtrlShitSToolStripMenuItem.Click += saveProjectAs;
            // 
            // playProjectCtrlPToolStripMenuItem
            // 
            this.playProjectCtrlPToolStripMenuItem.Name = "playProjectCtrlPToolStripMenuItem";
            this.playProjectCtrlPToolStripMenuItem.Size = new System.Drawing.Size(226, 22);
            this.playProjectCtrlPToolStripMenuItem.Text = "&Play Project (Ctrl+P)";
            playProjectCtrlPToolStripMenuItem.Click += playProject;
            // 
            // compileProjectToolStripMenuItem
            // 
            this.compileProjectToolStripMenuItem.Name = "compileProjectToolStripMenuItem";
            this.compileProjectToolStripMenuItem.Size = new System.Drawing.Size(226, 22);
            this.compileProjectToolStripMenuItem.Text = "Compile Project";
            compileProjectToolStripMenuItem.Click += compileProject;
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(226, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            exitToolStripMenuItem.Click += exitEditor;
            // 
            // objectToolStripMenuItem
            // 
            this.objectToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addAObjectCtrlAToolStripMenuItem,
            this.addAAddonToolStripMenuItem,
            this.installResourcesToolStripMenuItem});
            this.objectToolStripMenuItem.Name = "objectToolStripMenuItem";
            this.objectToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
            this.objectToolStripMenuItem.Text = "Edit";
            // 
            // addAObjectCtrlAToolStripMenuItem
            // 
            this.addAObjectCtrlAToolStripMenuItem.Name = "addAObjectCtrlAToolStripMenuItem";
            this.addAObjectCtrlAToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.addAObjectCtrlAToolStripMenuItem.Text = "&Add a Object (Ctrl+A)";
            addAObjectCtrlAToolStripMenuItem.Click += addObject;
            // 
            // addAAddonToolStripMenuItem
            // 
            this.addAAddonToolStripMenuItem.Name = "addAAddonToolStripMenuItem";
            this.addAAddonToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.addAAddonToolStripMenuItem.Text = "Add a Addon";
            addAAddonToolStripMenuItem.Click += addAddon;
            // 
            // installResourcesToolStripMenuItem
            // 
            this.installResourcesToolStripMenuItem.Name = "installResourcesToolStripMenuItem";
            this.installResourcesToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.installResourcesToolStripMenuItem.Text = "Install resources";
            installResourcesToolStripMenuItem.Click += installResources;
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.checkForUpdatesToolStripMenuItem,
            this.settingsToolStripMenuItem});
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.optionsToolStripMenuItem.Text = "Options";
            // 
            // checkForUpdatesToolStripMenuItem
            // 
            this.checkForUpdatesToolStripMenuItem.Name = "checkForUpdatesToolStripMenuItem";
            this.checkForUpdatesToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.checkForUpdatesToolStripMenuItem.Text = "Check for updates";
            checkForUpdatesToolStripMenuItem.Click += checkforUpdatesEvent;
            // 
            // settingsToolStripMenuItem
            // 
            this.settingsToolStripMenuItem.Name = "settingsToolStripMenuItem";
            this.settingsToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.settingsToolStripMenuItem.Text = "Settings";
            settingsToolStripMenuItem.Click += settingsOpen;
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem,
            this.documentationToolStripMenuItem,
            this.officialWebsiteToolStripMenuItem,
            this.forumToolStripMenuItem,
            this.reportABugToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.aboutToolStripMenuItem.Text = "About";
            aboutToolStripMenuItem.Click += aboutBoxOpen;
            // 
            // documentationToolStripMenuItem
            // 
            this.documentationToolStripMenuItem.Name = "documentationToolStripMenuItem";
            this.documentationToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.documentationToolStripMenuItem.Text = "Documentation";
            documentationToolStripMenuItem.Click += openDocumentation;
            // 
            // officialWebsiteToolStripMenuItem
            // 
            this.officialWebsiteToolStripMenuItem.Name = "officialWebsiteToolStripMenuItem";
            this.officialWebsiteToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.officialWebsiteToolStripMenuItem.Text = "Official Website";
            officialWebsiteToolStripMenuItem.Click += officialWebsite;
            // 
            // forumToolStripMenuItem
            // 
            this.forumToolStripMenuItem.Name = "forumToolStripMenuItem";
            this.forumToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.forumToolStripMenuItem.Text = "Forum";
            forumToolStripMenuItem.Click += openForum;
            // 
            // reportABugToolStripMenuItem
            // 
            this.reportABugToolStripMenuItem.Name = "reportABugToolStripMenuItem";
            this.reportABugToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.reportABugToolStripMenuItem.Text = "Report a bug";
            reportABugToolStripMenuItem.Click += reportBug;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.editObjectToolStripMenuItem,
            this.deleteObjectToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(146, 48);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(0, 27);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(150, 511);
            this.listBox1.TabIndex = 2;
            listBox1.MouseDown += listBox1_MouseDown;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 539);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(784, 22);
            this.statusStrip1.TabIndex = 3;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(42, 17);
            this.toolStripStatusLabel1.Text = "Status:";
            // 
            // editObjectToolStripMenuItem
            // 
            this.editObjectToolStripMenuItem.Name = "editObjectToolStripMenuItem";
            this.editObjectToolStripMenuItem.Size = new System.Drawing.Size(145, 22);
            this.editObjectToolStripMenuItem.Text = "Edit Object";
            editObjectToolStripMenuItem.Click += M_EditObject;
            // 
            // deleteObjectToolStripMenuItem
            // 
            this.deleteObjectToolStripMenuItem.Name = "deleteObjectToolStripMenuItem";
            this.deleteObjectToolStripMenuItem.Size = new System.Drawing.Size(145, 22);
            this.deleteObjectToolStripMenuItem.Text = "&Delete Object";
            deleteObjectToolStripMenuItem.Click += M_DeleteObject;
            // 
            // EditorUI
            //               
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.contextMenuStrip1.ResumeLayout(false);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            GameWindow.ResumeLayout(false);
            GameWindow.PerformLayout();
            GameWindow.SizeChanged += GameWindow_SizeChanged;

            GameWindow.Controls.Add(menuStrip1);
            GameWindow.Controls.Add(listBox1);
            GameWindow.Controls.Add(statusStrip1);
            GameWindow.FormClosing += Editor_Exiting;

        }

        private void GameWindow_SizeChanged(object sender, EventArgs e)
        {
            listBox1.ClientSize = new System.Drawing.Size(listBox1.ClientSize.Width, GameWindow.ClientSize.Height - 44);
        }
    }
}
