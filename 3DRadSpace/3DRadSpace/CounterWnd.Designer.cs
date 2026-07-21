namespace _3DRadSpace
{
    partial class CounterWnd
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
            if(disposing && (components != null))
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CounterWnd));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.CBOX_enabled = new System.Windows.Forms.CheckBox();
            this.TXTBOXobject_name = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.tb_inc = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.TB_initialv = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.cb_savefile = new System.Windows.Forms.CheckBox();
            this.tb_filename = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.b_ok = new System.Windows.Forms.Button();
            this.b_cancel = new System.Windows.Forms.Button();
            this.Help = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.CBOX_enabled);
            this.groupBox1.Controls.Add(this.TXTBOXobject_name);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(314, 64);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Common settings";
            // 
            // CBOX_enabled
            // 
            this.CBOX_enabled.AutoSize = true;
            this.CBOX_enabled.Checked = true;
            this.CBOX_enabled.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CBOX_enabled.Location = new System.Drawing.Point(203, 28);
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
            this.TXTBOXobject_name.Text = "Camera";
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
            this.groupBox2.Controls.Add(this.tb_inc);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.TB_initialv);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Location = new System.Drawing.Point(12, 84);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(315, 92);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Value fields";
            // 
            // tb_inc
            // 
            this.tb_inc.Location = new System.Drawing.Point(93, 51);
            this.tb_inc.Name = "tb_inc";
            this.tb_inc.Size = new System.Drawing.Size(100, 22);
            this.tb_inc.TabIndex = 3;
            this.tb_inc.Text = "100";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(17, 54);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(70, 17);
            this.label3.TabIndex = 2;
            this.label3.Text = "Increment";
            // 
            // TB_initialv
            // 
            this.TB_initialv.Location = new System.Drawing.Point(93, 21);
            this.TB_initialv.Name = "TB_initialv";
            this.TB_initialv.Size = new System.Drawing.Size(100, 22);
            this.TB_initialv.TabIndex = 1;
            this.TB_initialv.Text = "0";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 24);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(78, 17);
            this.label2.TabIndex = 0;
            this.label2.Text = "Initial value";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.cb_savefile);
            this.groupBox3.Controls.Add(this.tb_filename);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Location = new System.Drawing.Point(12, 182);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(315, 91);
            this.groupBox3.TabIndex = 5;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Saving and loading";
            // 
            // cb_savefile
            // 
            this.cb_savefile.AutoSize = true;
            this.cb_savefile.Location = new System.Drawing.Point(10, 53);
            this.cb_savefile.Name = "cb_savefile";
            this.cb_savefile.Size = new System.Drawing.Size(183, 21);
            this.cb_savefile.TabIndex = 2;
            this.cb_savefile.Text = "Save in game directory?";
            this.cb_savefile.UseVisualStyleBackColor = true;
            // 
            // tb_filename
            // 
            this.tb_filename.Location = new System.Drawing.Point(80, 25);
            this.tb_filename.Name = "tb_filename";
            this.tb_filename.Size = new System.Drawing.Size(100, 22);
            this.tb_filename.TabIndex = 1;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 28);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 17);
            this.label4.TabIndex = 0;
            this.label4.Text = "Filename";
            // 
            // b_ok
            // 
            this.b_ok.Location = new System.Drawing.Point(171, 279);
            this.b_ok.Name = "b_ok";
            this.b_ok.Size = new System.Drawing.Size(75, 23);
            this.b_ok.TabIndex = 6;
            this.b_ok.Text = "OK";
            this.b_ok.UseVisualStyleBackColor = true;
            this.b_ok.Click += new System.EventHandler(this.b_ok_Click);
            // 
            // b_cancel
            // 
            this.b_cancel.Location = new System.Drawing.Point(252, 279);
            this.b_cancel.Name = "b_cancel";
            this.b_cancel.Size = new System.Drawing.Size(75, 23);
            this.b_cancel.TabIndex = 7;
            this.b_cancel.Text = "Cancel";
            this.b_cancel.UseVisualStyleBackColor = true;
            this.b_cancel.Click += new System.EventHandler(this.b_cancel_Click);
            // 
            // Help
            // 
            this.Help.Location = new System.Drawing.Point(11, 279);
            this.Help.Name = "Help";
            this.Help.Size = new System.Drawing.Size(75, 23);
            this.Help.TabIndex = 8;
            this.Help.Text = "Help";
            this.Help.UseVisualStyleBackColor = true;
            this.Help.Click += new System.EventHandler(this.Help_Click);
            // 
            // CounterWnd
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(345, 312);
            this.Controls.Add(this.Help);
            this.Controls.Add(this.b_cancel);
            this.Controls.Add(this.b_ok);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "CounterWnd";
            this.Text = "Counter Object";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox CBOX_enabled;
        private System.Windows.Forms.TextBox TXTBOXobject_name;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox TB_initialv;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tb_inc;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox cb_savefile;
        private System.Windows.Forms.TextBox tb_filename;
        private System.Windows.Forms.Button b_ok;
        private System.Windows.Forms.Button b_cancel;
        private System.Windows.Forms.Button Help;
    }
}