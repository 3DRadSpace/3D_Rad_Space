namespace _3DRadSpace
{
    partial class GroupWnd
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(GroupWnd));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.cb_enabled = new System.Windows.Forms.CheckBox();
            this.tb_objname = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.tb_sZ = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.tb_sY = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.tb_sX = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.tb_rotZ = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.tb_rotY = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.tb_rotX = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.tb_zpos = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.tb_ypos = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.TB_xpos = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.b_cancel = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.label14 = new System.Windows.Forms.Label();
            this.b_ok = new System.Windows.Forms.Button();
            this.b_help = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.cb_enabled);
            this.groupBox1.Controls.Add(this.tb_objname);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(358, 52);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Common settings";
            // 
            // cb_enabled
            // 
            this.cb_enabled.AutoSize = true;
            this.cb_enabled.Checked = true;
            this.cb_enabled.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cb_enabled.Location = new System.Drawing.Point(152, 23);
            this.cb_enabled.Name = "cb_enabled";
            this.cb_enabled.Size = new System.Drawing.Size(71, 17);
            this.cb_enabled.TabIndex = 2;
            this.cb_enabled.Text = "Enabled?";
            this.cb_enabled.UseVisualStyleBackColor = true;
            // 
            // tb_objname
            // 
            this.tb_objname.Location = new System.Drawing.Point(47, 22);
            this.tb_objname.Name = "tb_objname";
            this.tb_objname.Size = new System.Drawing.Size(100, 20);
            this.tb_objname.TabIndex = 1;
            this.tb_objname.Text = "Group";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Name";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.tb_sZ);
            this.groupBox2.Controls.Add(this.label10);
            this.groupBox2.Controls.Add(this.label11);
            this.groupBox2.Controls.Add(this.tb_sY);
            this.groupBox2.Controls.Add(this.label12);
            this.groupBox2.Controls.Add(this.tb_sX);
            this.groupBox2.Controls.Add(this.label13);
            this.groupBox2.Controls.Add(this.tb_rotZ);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.tb_rotY);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.tb_rotX);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.tb_zpos);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.tb_ypos);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.TB_xpos);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Location = new System.Drawing.Point(12, 70);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(358, 100);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Translation";
            // 
            // tb_sZ
            // 
            this.tb_sZ.Location = new System.Drawing.Point(265, 64);
            this.tb_sZ.Margin = new System.Windows.Forms.Padding(2);
            this.tb_sZ.Name = "tb_sZ";
            this.tb_sZ.Size = new System.Drawing.Size(76, 20);
            this.tb_sZ.TabIndex = 41;
            this.tb_sZ.Text = "0";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(248, 66);
            this.label10.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(14, 13);
            this.label10.TabIndex = 40;
            this.label10.Text = "Z";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.ForeColor = System.Drawing.Color.Red;
            this.label11.Location = new System.Drawing.Point(7, 66);
            this.label11.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(34, 13);
            this.label11.TabIndex = 39;
            this.label11.Text = "Scale";
            // 
            // tb_sY
            // 
            this.tb_sY.Location = new System.Drawing.Point(168, 64);
            this.tb_sY.Margin = new System.Windows.Forms.Padding(2);
            this.tb_sY.Name = "tb_sY";
            this.tb_sY.Size = new System.Drawing.Size(76, 20);
            this.tb_sY.TabIndex = 38;
            this.tb_sY.Text = "1";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(151, 66);
            this.label12.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(14, 13);
            this.label12.TabIndex = 37;
            this.label12.Text = "Y";
            // 
            // tb_sX
            // 
            this.tb_sX.Location = new System.Drawing.Point(71, 64);
            this.tb_sX.Margin = new System.Windows.Forms.Padding(2);
            this.tb_sX.Name = "tb_sX";
            this.tb_sX.Size = new System.Drawing.Size(76, 20);
            this.tb_sX.TabIndex = 36;
            this.tb_sX.Text = "0";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(55, 66);
            this.label13.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(14, 13);
            this.label13.TabIndex = 35;
            this.label13.Text = "X";
            // 
            // tb_rotZ
            // 
            this.tb_rotZ.Location = new System.Drawing.Point(265, 41);
            this.tb_rotZ.Margin = new System.Windows.Forms.Padding(2);
            this.tb_rotZ.Name = "tb_rotZ";
            this.tb_rotZ.Size = new System.Drawing.Size(76, 20);
            this.tb_rotZ.TabIndex = 34;
            this.tb_rotZ.Text = "0";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(247, 44);
            this.label6.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(14, 13);
            this.label6.TabIndex = 33;
            this.label6.Text = "Z";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.ForeColor = System.Drawing.Color.Red;
            this.label7.Location = new System.Drawing.Point(6, 44);
            this.label7.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(47, 13);
            this.label7.TabIndex = 32;
            this.label7.Text = "Rotation";
            // 
            // tb_rotY
            // 
            this.tb_rotY.Location = new System.Drawing.Point(167, 41);
            this.tb_rotY.Margin = new System.Windows.Forms.Padding(2);
            this.tb_rotY.Name = "tb_rotY";
            this.tb_rotY.Size = new System.Drawing.Size(76, 20);
            this.tb_rotY.TabIndex = 31;
            this.tb_rotY.Text = "0";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(150, 44);
            this.label8.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(14, 13);
            this.label8.TabIndex = 30;
            this.label8.Text = "Y";
            // 
            // tb_rotX
            // 
            this.tb_rotX.Location = new System.Drawing.Point(70, 41);
            this.tb_rotX.Margin = new System.Windows.Forms.Padding(2);
            this.tb_rotX.Name = "tb_rotX";
            this.tb_rotX.Size = new System.Drawing.Size(76, 20);
            this.tb_rotX.TabIndex = 29;
            this.tb_rotX.Text = "0";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(54, 44);
            this.label9.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(14, 13);
            this.label9.TabIndex = 28;
            this.label9.Text = "X";
            // 
            // tb_zpos
            // 
            this.tb_zpos.Location = new System.Drawing.Point(265, 16);
            this.tb_zpos.Margin = new System.Windows.Forms.Padding(2);
            this.tb_zpos.Name = "tb_zpos";
            this.tb_zpos.Size = new System.Drawing.Size(76, 20);
            this.tb_zpos.TabIndex = 27;
            this.tb_zpos.Text = "0";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(247, 18);
            this.label5.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(14, 13);
            this.label5.TabIndex = 26;
            this.label5.Text = "Z";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.Color.Red;
            this.label4.Location = new System.Drawing.Point(7, 19);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(44, 13);
            this.label4.TabIndex = 25;
            this.label4.Text = "Position";
            // 
            // tb_ypos
            // 
            this.tb_ypos.Location = new System.Drawing.Point(168, 16);
            this.tb_ypos.Margin = new System.Windows.Forms.Padding(2);
            this.tb_ypos.Name = "tb_ypos";
            this.tb_ypos.Size = new System.Drawing.Size(76, 20);
            this.tb_ypos.TabIndex = 24;
            this.tb_ypos.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(151, 18);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(14, 13);
            this.label3.TabIndex = 23;
            this.label3.Text = "Y";
            // 
            // TB_xpos
            // 
            this.TB_xpos.Location = new System.Drawing.Point(71, 16);
            this.TB_xpos.Margin = new System.Windows.Forms.Padding(2);
            this.TB_xpos.Name = "TB_xpos";
            this.TB_xpos.Size = new System.Drawing.Size(76, 20);
            this.TB_xpos.TabIndex = 22;
            this.TB_xpos.Text = "0";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(54, 18);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(14, 13);
            this.label2.TabIndex = 21;
            this.label2.Text = "X";
            // 
            // b_cancel
            // 
            this.b_cancel.Location = new System.Drawing.Point(295, 292);
            this.b_cancel.Name = "b_cancel";
            this.b_cancel.Size = new System.Drawing.Size(75, 23);
            this.b_cancel.TabIndex = 5;
            this.b_cancel.Text = "Cancel";
            this.b_cancel.UseVisualStyleBackColor = true;
            this.b_cancel.Click += new System.EventHandler(this.b_cancel_Click);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(12, 191);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(358, 95);
            this.listBox1.TabIndex = 6;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(12, 175);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(76, 13);
            this.label14.TabIndex = 7;
            this.label14.Text = "Linked objects";
            // 
            // b_ok
            // 
            this.b_ok.Location = new System.Drawing.Point(214, 292);
            this.b_ok.Name = "b_ok";
            this.b_ok.Size = new System.Drawing.Size(75, 23);
            this.b_ok.TabIndex = 8;
            this.b_ok.Text = "OK";
            this.b_ok.UseVisualStyleBackColor = true;
            this.b_ok.Click += new System.EventHandler(this.b_ok_Click);
            // 
            // b_help
            // 
            this.b_help.Location = new System.Drawing.Point(12, 292);
            this.b_help.Name = "b_help";
            this.b_help.Size = new System.Drawing.Size(75, 23);
            this.b_help.TabIndex = 9;
            this.b_help.Text = "Help";
            this.b_help.UseVisualStyleBackColor = true;
            this.b_help.Click += new System.EventHandler(this.button1_Click);
            // 
            // GroupWnd
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(390, 330);
            this.Controls.Add(this.b_help);
            this.Controls.Add(this.b_ok);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.b_cancel);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "GroupWnd";
            this.Text = "Group Object";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox cb_enabled;
        private System.Windows.Forms.TextBox tb_objname;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox tb_sZ;
        private System.Windows.Forms.TextBox tb_rotZ;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox tb_rotY;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox tb_rotX;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox tb_zpos;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox tb_ypos;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox TB_xpos;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button b_cancel;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Button b_ok;
        private System.Windows.Forms.Button b_help;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox tb_sY;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox tb_sX;
        private System.Windows.Forms.Label label13;
    }
}