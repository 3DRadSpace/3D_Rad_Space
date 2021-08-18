namespace _3DRadSpace
{
    partial class ScriptWnd
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ScriptWnd));
            this.scintilla1 = new ScintillaNET.Scintilla();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.CBOX_enabled = new System.Windows.Forms.CheckBox();
            this.TXTBOXobject_name = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.TXTBOX_className = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.okButton = new System.Windows.Forms.Button();
            this.helpButton = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // scintilla1
            // 
            this.scintilla1.Lexer = ScintillaNET.Lexer.Cpp;
            this.scintilla1.Location = new System.Drawing.Point(248, 15);
            this.scintilla1.Margin = new System.Windows.Forms.Padding(4);
            this.scintilla1.Name = "scintilla1";
            this.scintilla1.Size = new System.Drawing.Size(710, 516);
            this.scintilla1.TabIndex = 0;
            this.scintilla1.Text = resources.GetString("scintilla1.Text");
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.CBOX_enabled);
            this.groupBox1.Controls.Add(this.TXTBOXobject_name);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(16, 15);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(224, 103);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Common settings";
            // 
            // CBOX_enabled
            // 
            this.CBOX_enabled.AutoSize = true;
            this.CBOX_enabled.Checked = true;
            this.CBOX_enabled.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CBOX_enabled.Location = new System.Drawing.Point(12, 59);
            this.CBOX_enabled.Margin = new System.Windows.Forms.Padding(4);
            this.CBOX_enabled.Name = "CBOX_enabled";
            this.CBOX_enabled.Size = new System.Drawing.Size(90, 21);
            this.CBOX_enabled.TabIndex = 2;
            this.CBOX_enabled.Text = "Enabled?";
            this.CBOX_enabled.UseVisualStyleBackColor = true;
            // 
            // TXTBOXobject_name
            // 
            this.TXTBOXobject_name.Location = new System.Drawing.Point(63, 27);
            this.TXTBOXobject_name.Margin = new System.Windows.Forms.Padding(4);
            this.TXTBOXobject_name.Name = "TXTBOXobject_name";
            this.TXTBOXobject_name.Size = new System.Drawing.Size(132, 22);
            this.TXTBOXobject_name.TabIndex = 1;
            this.TXTBOXobject_name.Text = "Script";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 31);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Name";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.TXTBOX_className);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.button1);
            this.groupBox2.Location = new System.Drawing.Point(16, 126);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox2.Size = new System.Drawing.Size(224, 117);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Script";
            // 
            // TXTBOX_className
            // 
            this.TXTBOX_className.Location = new System.Drawing.Point(8, 39);
            this.TXTBOX_className.Margin = new System.Windows.Forms.Padding(4);
            this.TXTBOX_className.Name = "TXTBOX_className";
            this.TXTBOX_className.Size = new System.Drawing.Size(203, 22);
            this.TXTBOX_className.TabIndex = 2;
            this.TXTBOX_className.Text = "Script";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 20);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(113, 17);
            this.label2.TabIndex = 1;
            this.label2.Text = "Entry-point class";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(8, 71);
            this.button1.Margin = new System.Windows.Forms.Padding(4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(204, 28);
            this.button1.TabIndex = 0;
            this.button1.Text = "Check for errors";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.Location = new System.Drawing.Point(16, 321);
            this.cancelButton.Margin = new System.Windows.Forms.Padding(4);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(224, 28);
            this.cancelButton.TabIndex = 3;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // okButton
            // 
            this.okButton.Location = new System.Drawing.Point(16, 250);
            this.okButton.Margin = new System.Windows.Forms.Padding(4);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(224, 28);
            this.okButton.TabIndex = 4;
            this.okButton.Text = "OK";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // helpButton
            // 
            this.helpButton.Location = new System.Drawing.Point(16, 286);
            this.helpButton.Margin = new System.Windows.Forms.Padding(4);
            this.helpButton.Name = "helpButton";
            this.helpButton.Size = new System.Drawing.Size(224, 28);
            this.helpButton.TabIndex = 5;
            this.helpButton.Text = "Help";
            this.helpButton.UseVisualStyleBackColor = true;
            this.helpButton.Click += new System.EventHandler(this.helpButton_Click);
            // 
            // ScriptWnd
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(971, 546);
            this.Controls.Add(this.helpButton);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.scintilla1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "ScriptWnd";
            this.Text = "Script Object";
            this.Resize += new System.EventHandler(this.ScriptWnd_Resize);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private ScintillaNET.Scintilla scintilla1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox TXTBOXobject_name;
        private System.Windows.Forms.CheckBox CBOX_enabled;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button helpButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox TXTBOX_className;
    }
}