namespace _3DRadSpace
{
    partial class ObjectsInProject
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
            this.list_objects = new System.Windows.Forms.ListView();
            this.Object = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SuspendLayout();
            // 
            // list_objects
            // 
            this.list_objects.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.Object});
            this.list_objects.Dock = System.Windows.Forms.DockStyle.Fill;
            this.list_objects.FullRowSelect = true;
            this.list_objects.GridLines = true;
            this.list_objects.Location = new System.Drawing.Point(0, 0);
            this.list_objects.Name = "list_objects";
            this.list_objects.Size = new System.Drawing.Size(282, 438);
            this.list_objects.TabIndex = 0;
            this.list_objects.UseCompatibleStateImageBehavior = false;
            this.list_objects.View = System.Windows.Forms.View.Details;
            // 
            // Object
            // 
            this.Object.Text = "Object";
            this.Object.Width = 200;
            // 
            // ObjectsInProject
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(282, 438);
            this.Controls.Add(this.list_objects);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ObjectsInProject";
            this.ShowIcon = false;
            this.Load += new System.EventHandler(this.ObjectsInProject_Load);
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.ListView list_objects;
        private System.Windows.Forms.ColumnHeader Object;
    }
}