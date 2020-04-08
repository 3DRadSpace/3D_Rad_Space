using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System.Windows.Forms;
using _3DRadSpaceDll;

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
			textBox3.Text = SafeConverter.FloatToString(textPrint.Position.X);
			textBox4.Text = SafeConverter.FloatToString(textPrint.Position.Y);
			textBox5.Text = SafeConverter.FloatToString(textPrint.Rotation);
			textBox6.Text = SafeConverter.FloatToString(textPrint.Center.X);
			textBox7.Text = SafeConverter.FloatToString(textPrint.Center.Y);
			textBox8.Text = textPrint.Text;
			textBox9.Text = textPrint.Color.R + "";
			textBox10.Text = textPrint.Color.G + "";
			textBox11.Text = textPrint.Color.B + "";
			textBox12.Text = SafeConverter.FloatToString(textPrint.Size.X);
			textBox13.Text = SafeConverter.FloatToString(textPrint.Size.Y);
			textBox14.Text = SafeConverter.FloatToString(textPrint.Layer);
		}

		private void button2_Click(object sender, EventArgs e)
		{
			if (!File.Exists("Content\\" + textBox2.Text + ".xnb"))
			{
				MessageBox.Show("The file: \n" + Path.GetFullPath("Content\\" + textBox2.Text + ".xnb") + " doesn't exist.", "Resource file not found.", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}
			Result = new TextPrint(Editor.ValidateTextInput(textBox1.Text), checkBox1.Checked,Editor.ValidateTextInput(textBox2.Text),textBox8.Text, new Vector2(
				SafeConverter.FloatFromString(Editor.ValidateNumberTextInput(textBox3.Text)),
				SafeConverter.FloatFromString(Editor.ValidateNumberTextInput(textBox4.Text))),
			new Vector2(SafeConverter.FloatFromString(Editor.ValidateNumberTextInput(textBox12.Text)),
				SafeConverter.FloatFromString(Editor.ValidateNumberTextInput(textBox13.Text))),
				SafeConverter.FloatFromString(Editor.ValidateNumberTextInput(textBox5.Text)),
			new Vector2(SafeConverter.FloatFromString(Editor.ValidateNumberTextInput(textBox6.Text)),
				SafeConverter.FloatFromString(Editor.ValidateNumberTextInput(textBox7.Text))),
			new Color(
				Convert.ToByte(Editor.ValidateNumberTextInput(textBox9.Text)),
				Convert.ToByte(Editor.ValidateNumberTextInput(textBox10.Text)),
				Convert.ToByte(Editor.ValidateNumberTextInput(textBox11.Text))),
			(SpriteEffects)(SafeConverter.IntFromString(checkBox2.Checked) + SafeConverter.IntFromString(checkBox3.Checked)),
			SafeConverter.IntFromString(textBox14.Text));
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
