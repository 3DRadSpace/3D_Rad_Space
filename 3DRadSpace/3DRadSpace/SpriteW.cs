using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System.Windows.Forms;
using _3DRadSpaceDll;
using System.IO;

namespace _3DRadSpace
{
	public partial class SpriteW : Form
	{

		public GameObject Result;

		public SpriteW(Sprite sp)
		{
			InitializeComponent();
			textBox1.Text = sp.Name;
			checkBox1.Checked = sp.Enabled;
			textBox2.Text = sp.Resource;
			pictureBox1.ImageLocation = sp.Resource;
			textBox3.Text = SafeConverter.FloatToString(sp.Position.X);
			textBox4.Text = SafeConverter.FloatToString(sp.Position.Y);
			textBox5.Text = SafeConverter.FloatToString(sp.Rotation);
			textBox6.Text = SafeConverter.FloatToString(sp.Size.X);
			textBox7.Text = SafeConverter.FloatToString(sp.Size.Y);
			if (sp.SpriteSheetSection.HasValue)
			{
				textBox8.Text = SafeConverter.FloatToString(sp.SpriteSheetSection.Value.X);
				textBox9.Text = SafeConverter.FloatToString(sp.SpriteSheetSection.Value.Y);
				textBox10.Text = SafeConverter.FloatToString(sp.SpriteSheetSection.Value.Width);
				textBox11.Text = SafeConverter.FloatToString(sp.SpriteSheetSection.Value.Height);
			}
			else
			{
				textBox8.Text = "0";
				textBox9.Text = "0";
				textBox10.Text = "0";
				textBox11.Text = "0";
			}
			textBox12.Text = SafeConverter.FloatToString(sp.Layer );
			textBox13.Text = SafeConverter.FloatToString(sp.Center.X );
			textBox14.Text = SafeConverter.FloatToString(sp.Center.Y );
			textBox15.Text = sp.Mask.R + "";
			textBox16.Text = sp.Mask.G + "";
			textBox17.Text = sp.Mask.B + "";
		}
		public SpriteW()
		{
			InitializeComponent();
		}

		private void button3_Click(object sender, EventArgs e)
		{
			if(!File.Exists(textBox2.Text))
			{
				MessageBox.Show("The file: \n" + textBox2.Text + " doesn't exist.", "Resource file not found.", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}
			Rectangle? r = new Rectangle(
					SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox8.Text)), SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox9.Text)),
					SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox10.Text)), SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox11.Text)));
			if (r.Value.Height + r.Value.Width == 0) r = null;
			Result = new Sprite(Editor.ValidateTextInput(textBox1.Text), checkBox1.Checked, textBox2.Text,
				new Vector2(SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox3.Text)), SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox4.Text))),
				new Vector2(SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox6.Text)), SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox7.Text))),
				new Vector2(SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox13.Text)), SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox14.Text))),
				SafeConverter.FloatFromString(textBox5.Text),r,
				new Color(Convert.ToByte(Editor.ValidateNumberTextInput(textBox15.Text)),Convert.ToByte(Editor.ValidateNumberTextInput(textBox16.Text)),Convert.ToByte(Editor.ValidateNumberTextInput(textBox17.Text))),
				(SpriteEffects)(SafeConverter.IntFromString(checkBox2.Checked) + 2*SafeConverter.IntFromString(checkBox3.Checked)),SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox12.Text)));
			DialogResult = DialogResult.OK;
			Close();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			OpenFileDialog openFile = new OpenFileDialog()
			{
				Title = "Find a image...",
				Multiselect = false,
			};
			if (openFile.ShowDialog() == DialogResult.OK)
			{
				string f = "Content\\" + Path.GetFileName(openFile.FileName);
				File.Copy(openFile.FileName, f,true);
				textBox2.Text = f;
				pictureBox1.ImageLocation = f;
			}
			openFile.Dispose();
		}

		private void button4_Click(object sender, EventArgs e)
		{
			Result = null;
			DialogResult = DialogResult.Cancel;
			Close();
		}

		private void button5_Click(object sender, EventArgs e)
		{
			//open docs
		}
	}
}
