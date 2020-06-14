using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System.Windows.Forms;
using _3DRadSpaceDll;
using System.Globalization;

namespace _3DRadSpace
{
	public partial class TextPrintW : Form
	{
		public GameObject Result;
		public TextPrintW()
		{
			InitializeComponent();
		}
		public TextPrintW(TextPrint textPrint)
		{
			InitializeComponent();
			textBox1.Text = textPrint.Name;
			checkBox1.Checked = textPrint.Enabled;
			textBox2.Text = textPrint.Resource;
			textBox3.Text = textPrint.Position.X.ToString( CultureInfo.InvariantCulture);
			textBox4.Text = textPrint.Position.Y.ToString( CultureInfo.InvariantCulture);
			textBox5.Text = textPrint.Rotation.ToString( CultureInfo.InvariantCulture);
			textBox6.Text = textPrint.Center.X.ToString( CultureInfo.InvariantCulture);
			textBox7.Text = textPrint.Center.Y.ToString( CultureInfo.InvariantCulture);
			textBox8.Text = textPrint.Text;
			textBox9.Text = textPrint.Color.R.ToString(CultureInfo.InvariantCulture);
			textBox10.Text = textPrint.Color.G.ToString(CultureInfo.InvariantCulture);
			textBox11.Text = textPrint.Color.B.ToString(CultureInfo.InvariantCulture);
			textBox12.Text = textPrint.Size.X.ToString(CultureInfo.InvariantCulture);
			textBox13.Text = textPrint.Size.Y.ToString(CultureInfo.InvariantCulture);
			textBox14.Text = textPrint.Layer.ToString(CultureInfo.InvariantCulture);
		}

		private void button2_Click(object sender, EventArgs e)
		{
			if (!File.Exists("Content\\" + textBox2.Text + ".xnb"))
			{
				MessageBox.Show("The file: \n" + Path.GetFullPath("Content\\" + textBox2.Text + ".xnb") + " doesn't exist.", "Resource file not found.", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}
			Result = new TextPrint(Editor.ValidateTextInput(textBox1.Text), checkBox1.Checked,Editor.ValidateTextInput(textBox2.Text),textBox8.Text, new Vector2(
				Convert.ToSingle(Editor.ValidateNumberTextInput(textBox3.Text), Program.CultureInfo),
				Convert.ToSingle(Editor.ValidateNumberTextInput(textBox4.Text), Program.CultureInfo)),
			new Vector2(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox12.Text), Program.CultureInfo),
				Convert.ToSingle(Editor.ValidateNumberTextInput(textBox13.Text), Program.CultureInfo)),
				Convert.ToSingle(Editor.ValidateNumberTextInput(textBox5.Text), Program.CultureInfo),
			new Vector2(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox6.Text), Program.CultureInfo),
				Convert.ToSingle(Editor.ValidateNumberTextInput(textBox7.Text), Program.CultureInfo)),
			new Color(
				Convert.ToByte(Editor.ValidateNumberTextInput(textBox9.Text), Program.CultureInfo),
				Convert.ToByte(Editor.ValidateNumberTextInput(textBox10.Text), Program.CultureInfo),
				Convert.ToByte(Editor.ValidateNumberTextInput(textBox11.Text), Program.CultureInfo)),
			(SpriteEffects)(Convert.ToInt32(checkBox2.Checked) + Convert.ToInt32(checkBox3.Checked)),
			Convert.ToInt32(textBox14.Text, Program.CultureInfo));
			DialogResult = DialogResult.OK;
			Close();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			ColorDialog colr = new ColorDialog()
			{
				AllowFullOpen = true,
				AnyColor = true
			};
			if(colr.ShowDialog() == DialogResult.OK)
			{
				textBox9.Text = colr.Color.R + "";
				textBox10.Text = colr.Color.G + "";
				textBox11.Text = colr.Color.B + "";
			}
			colr.Dispose();
		}

		private void button3_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
			Result = null;
			Close();
		}

		private void button4_Click(object sender, EventArgs e)
		{
			//open docs
		}
	}
}
