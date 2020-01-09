using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System.Windows.Forms;
using _3DRadSpaceDll;

namespace _3DRadSpace
{
	public partial class SpriteW : Form
	{

		public object Result;

		public SpriteW(Sprite sp)
		{
			InitializeComponent();
			textBox1.Text = sp.Name;
			checkBox1.Checked = sp.Enabled;
			textBox2.Text = sp.Resource;
			textBox3.Text = sp.Position.X+"";
			textBox4.Text = sp.Position.Y+"";
			textBox5.Text = sp.Rotation + "";
			textBox6.Text = sp.Size.X+"";
			textBox7.Text = sp.Size.Y + "";
			if (sp.SpriteSheetSection.HasValue)
			{
				textBox8.Text = sp.SpriteSheetSection.Value.X + "";
				textBox9.Text = sp.SpriteSheetSection.Value.Y + "";
				textBox10.Text = sp.SpriteSheetSection.Value.Width + "";
				textBox11.Text = sp.SpriteSheetSection.Value.Height + "";
			}
			else
			{
				textBox8.Text = "0";
				textBox9.Text = "0";
				textBox10.Text = "0";
				textBox11.Text = "0";
			}
			textBox12.Text = sp.Layer + "";
			textBox13.Text = sp.Center.X + "";
			textBox14.Text = sp.Center.Y + "";
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
			Rectangle? r = new Rectangle(
					Convert.ToInt32(Editor.ValidateNumberTextInput(textBox9.Text)), Convert.ToInt32(Editor.ValidateNumberTextInput(textBox10.Text)),
					Convert.ToInt32(Editor.ValidateNumberTextInput(textBox11.Text)), Convert.ToInt32(Editor.ValidateNumberTextInput(textBox12.Text)));
			if (r.Value.Height + r.Value.Width == 0) r = null;
			Result = new Sprite(Editor.ValidateTextInput(textBox1.Text), checkBox1.Checked, textBox2.Text,
				new Vector2(Convert.ToInt32(Editor.ValidateNumberTextInput(textBox3.Text)), Convert.ToInt32(Editor.ValidateNumberTextInput(textBox4.Text))),
				new Vector2(Convert.ToInt32(Editor.ValidateNumberTextInput(textBox6.Text)), Convert.ToInt32(Editor.ValidateNumberTextInput(textBox7.Text))),
				new Vector2(Convert.ToInt32(Editor.ValidateNumberTextInput(textBox8.Text)), Convert.ToInt32(Editor.ValidateNumberTextInput(textBox9.Text))),
				Convert.ToSingle(textBox5.Text),r,
				new Color(Convert.ToByte(Editor.ValidateNumberTextInput(textBox15.Text)),Convert.ToByte(Editor.ValidateNumberTextInput(textBox16.Text)),Convert.ToByte(Editor.ValidateNumberTextInput(textBox17.Text))),
				(SpriteEffects)(Convert.ToInt32(checkBox2.Checked) + Convert.ToInt32(checkBox3.Checked)));
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
				textBox2.Text = openFile.FileName;
				pictureBox1.ImageLocation = openFile.FileName;
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
