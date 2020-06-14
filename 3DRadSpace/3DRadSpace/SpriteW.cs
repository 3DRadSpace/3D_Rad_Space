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
			textBox3.Text = sp.Position.X.ToString( Program.CultureInfo);
			textBox4.Text = sp.Position.Y.ToString( Program.CultureInfo);
			textBox5.Text = sp.Rotation.ToString( Program.CultureInfo);
			textBox6.Text = sp.Size.X.ToString( Program.CultureInfo);
			textBox7.Text = sp.Size.Y.ToString( Program.CultureInfo);
			if (sp.SpriteSheetSection.HasValue)
			{
				textBox8.Text = sp.SpriteSheetSection.Value.X.ToString( Program.CultureInfo);
				textBox9.Text = sp.SpriteSheetSection.Value.Y.ToString( Program.CultureInfo);
				textBox10.Text = sp.SpriteSheetSection.Value.Width.ToString( Program.CultureInfo);
				textBox11.Text = sp.SpriteSheetSection.Value.Height.ToString( Program.CultureInfo);
			}
			else
			{
				textBox8.Text = "0";
				textBox9.Text = "0";
				textBox10.Text = "0";
				textBox11.Text = "0";
			}
			textBox12.Text = ""+sp.Layer.ToString( Program.CultureInfo);
			textBox13.Text = ""+sp.Center.X.ToString( Program.CultureInfo);
			textBox14.Text = ""+sp.Center.Y.ToString( Program.CultureInfo);
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
					Convert.ToInt32(Editor.ValidateNumberTextInput(textBox8.Text),Program.CultureInfo), Convert.ToInt32(Editor.ValidateNumberTextInput(textBox9.Text), Program.CultureInfo),
					Convert.ToInt32(Editor.ValidateNumberTextInput(textBox10.Text), Program.CultureInfo), Convert.ToInt32(Editor.ValidateNumberTextInput(textBox11.Text), Program.CultureInfo));
			if (r.Value.Height + r.Value.Width == 0) r = null;
			Result = new Sprite(Editor.ValidateTextInput(textBox1.Text), checkBox1.Checked, textBox2.Text,
				new Vector2(Convert.ToInt32(Editor.ValidateNumberTextInput(textBox3.Text), Program.CultureInfo), Convert.ToInt32(Editor.ValidateNumberTextInput(textBox4.Text), Program.CultureInfo)),
				new Vector2(Convert.ToInt32(Editor.ValidateNumberTextInput(textBox6.Text), Program.CultureInfo), Convert.ToInt32(Editor.ValidateNumberTextInput(textBox7.Text), Program.CultureInfo)),
				new Vector2(Convert.ToInt32(Editor.ValidateNumberTextInput(textBox13.Text), Program.CultureInfo), Convert.ToInt32(Editor.ValidateNumberTextInput(textBox14.Text), Program.CultureInfo)),
				Convert.ToSingle(textBox5.Text, Program.CultureInfo),r,
				new Color(Convert.ToByte(Editor.ValidateNumberTextInput(textBox15.Text)),Convert.ToByte(Editor.ValidateNumberTextInput(textBox16.Text)),Convert.ToByte(Editor.ValidateNumberTextInput(textBox17.Text))),
				(SpriteEffects)(Convert.ToInt32( (Convert.ToInt32(checkBox2.Checked)) + 2*Convert.ToInt32(checkBox3.Checked))),Convert.ToInt32(Editor.ValidateNumberTextInput(textBox12.Text), Program.CultureInfo));
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
