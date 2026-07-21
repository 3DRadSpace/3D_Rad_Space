namespace _3DRadSpace
{
    partial class AddObjectWnd
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
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
            System.Windows.Forms.ListViewGroup listViewGroup1 = new System.Windows.Forms.ListViewGroup("Camera objects", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup2 = new System.Windows.Forms.ListViewGroup("Scripting Objects", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup3 = new System.Windows.Forms.ListViewGroup("3D Visual Objects", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup4 = new System.Windows.Forms.ListViewGroup("Physics Objects", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup5 = new System.Windows.Forms.ListViewGroup("2D Visual Objects", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup6 = new System.Windows.Forms.ListViewGroup("Events", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup7 = new System.Windows.Forms.ListViewGroup("Triggerable objects", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup8 = new System.Windows.Forms.ListViewGroup("Sound objects", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewItem listViewItem1 = new System.Windows.Forms.ListViewItem("Camera");
            System.Windows.Forms.ListViewItem listViewItem2 = new System.Windows.Forms.ListViewItem("Script");
            System.Windows.Forms.ListViewItem listViewItem3 = new System.Windows.Forms.ListViewItem("Skinmesh");
            System.Windows.Forms.ListViewItem listViewItem4 = new System.Windows.Forms.ListViewItem("Sprite");
            System.Windows.Forms.ListViewItem listViewItem5 = new System.Windows.Forms.ListViewItem("TextPrint");
            System.Windows.Forms.ListViewItem listViewItem6 = new System.Windows.Forms.ListViewItem("Skybox");
            System.Windows.Forms.ListViewItem listViewItem7 = new System.Windows.Forms.ListViewItem("SoundEffect");
            System.Windows.Forms.ListViewItem listViewItem8 = new System.Windows.Forms.ListViewItem("SoundSource");
            System.Windows.Forms.ListViewItem listViewItem9 = new System.Windows.Forms.ListViewItem("EventOnLocation");
            System.Windows.Forms.ListViewItem listViewItem10 = new System.Windows.Forms.ListViewItem("EventOnKey");
            System.Windows.Forms.ListViewItem listViewItem11 = new System.Windows.Forms.ListViewItem("Timer");
            System.Windows.Forms.ListViewItem listViewItem12 = new System.Windows.Forms.ListViewItem("Fog");
            System.Windows.Forms.ListViewItem listViewItem13 = new System.Windows.Forms.ListViewItem("ExitFade");
            System.Windows.Forms.ListViewItem listViewItem14 = new System.Windows.Forms.ListViewItem("Counter");
            System.Windows.Forms.ListViewItem listViewItem15 = new System.Windows.Forms.ListViewItem("FirstPersonCamera");
            System.Windows.Forms.ListViewItem listViewItem16 = new System.Windows.Forms.ListViewItem("RigidBody");
            System.Windows.Forms.ListViewItem listViewItem17 = new System.Windows.Forms.ListViewItem("GForce");
            System.Windows.Forms.ListViewItem listViewItem18 = new System.Windows.Forms.ListViewItem("Force");
            System.Windows.Forms.ListViewItem listViewItem19 = new System.Windows.Forms.ListViewItem("Group");
            System.Windows.Forms.ListViewItem listViewItem20 = new System.Windows.Forms.ListViewItem("Empty");
            this.listView1 = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SuspendLayout();
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1});
            this.listView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listView1.GridLines = true;
            listViewGroup1.Header = "Camera objects";
            listViewGroup1.Name = "cameraGroup";
            listViewGroup2.Header = "Scripting Objects";
            listViewGroup2.Name = "scriptingGroup";
            listViewGroup3.Header = "3D Visual Objects";
            listViewGroup3.Name = "visualGroup";
            listViewGroup4.Header = "Physics Objects";
            listViewGroup4.Name = "physicsGroup";
            listViewGroup5.Header = "2D Visual Objects";
            listViewGroup5.Name = "visual2dGroup";
            listViewGroup6.Header = "Events";
            listViewGroup6.Name = "eventsGroup";
            listViewGroup7.Header = "Triggerable objects";
            listViewGroup7.Name = "triggerGroup";
            listViewGroup8.Header = "Sound objects";
            listViewGroup8.Name = "soundsGroup";
            this.listView1.Groups.AddRange(new System.Windows.Forms.ListViewGroup[] {
            listViewGroup1,
            listViewGroup2,
            listViewGroup3,
            listViewGroup4,
            listViewGroup5,
            listViewGroup6,
            listViewGroup7,
            listViewGroup8});
            this.listView1.HideSelection = false;
            listViewItem1.Group = listViewGroup1;
            listViewItem1.StateImageIndex = 0;
            listViewItem2.Group = listViewGroup2;
            listViewItem2.StateImageIndex = 0;
            listViewItem3.Group = listViewGroup3;
            listViewItem4.Group = listViewGroup5;
            listViewItem5.Group = listViewGroup5;
            listViewItem6.Group = listViewGroup3;
            listViewItem7.Group = listViewGroup8;
            listViewItem8.Group = listViewGroup8;
            listViewItem9.Group = listViewGroup6;
            listViewItem10.Group = listViewGroup6;
            listViewItem11.Group = listViewGroup6;
            listViewItem12.Group = listViewGroup3;
            listViewItem13.Group = listViewGroup7;
            listViewItem14.Group = listViewGroup6;
            listViewItem15.Group = listViewGroup1;
            listViewItem16.Group = listViewGroup4;
            listViewItem17.Group = listViewGroup4;
            listViewItem18.Group = listViewGroup4;
            listViewItem19.Group = listViewGroup4;
            listViewItem20.Group = listViewGroup2;
            this.listView1.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem1,
            listViewItem2,
            listViewItem3,
            listViewItem4,
            listViewItem5,
            listViewItem6,
            listViewItem7,
            listViewItem8,
            listViewItem9,
            listViewItem10,
            listViewItem11,
            listViewItem12,
            listViewItem13,
            listViewItem14,
            listViewItem15,
            listViewItem16,
            listViewItem17,
            listViewItem18,
            listViewItem19,
            listViewItem20});
            this.listView1.Location = new System.Drawing.Point(0, 0);
            this.listView1.MultiSelect = false;
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(914, 533);
            this.listView1.TabIndex = 0;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.listView1_MouseDoubleClick);
            // 
            // AddObjectWnd
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(914, 533);
            this.Controls.Add(this.listView1);
            this.Name = "AddObjectWnd";
            this.Text = "AddObjectWnd";
            this.Load += new System.EventHandler(this.AddObjectWnd_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ColumnHeader columnHeader1;
    }
}