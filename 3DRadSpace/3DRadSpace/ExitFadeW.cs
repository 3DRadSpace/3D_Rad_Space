using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using _3DRadSpaceDll;
using System.IO;

namespace _3DRadSpace
{
	public partial class ExitFadeW : Form
	{
		public GameObject Result;
		public ExitFadeW()
		{
			InitializeComponent();
		}
		public ExitFadeW(ExitFade fade)
		{
			InitializeComponent();
			textBox1.Text = fade.Name;
			textBox2.Text = fade.Fade.R + "";
			textBox3.Text = fade.Fade.G + "";
			textBox4.Text = fade.Fade.B+ "";
			textBox5.Text = fade.Time * 1000 + "";
			textBox6.Text = fade.ProjectToLoad;
		}

		private void checkBox2_CheckedChanged(object sender, EventArgs e)
		{
			if (checkBox2.Checked) checkBox2.Text = "Fade In";
			else checkBox2.Text = "Fade Out";
		}

		private void ExitFadeW_Load(object sender, EventArgs e)
		{
			checkBox2_CheckedChanged(null,null);
		}

		private void button3_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
			Close();
		}

		private void button4_Click(object sender, EventArgs e)
		{
			if (!File.Exists("Content\\" + textBox6.Text + ".xnb"))
			{
				MessageBox.Show("The project: \n" + textBox6.Text + " doesn't exist.", "Resource file not found.", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}
			Result = new ExitFade(textBox1.Text, textBox6.Text, new Microsoft.Xna.Framework.Color(
				Convert.ToByte(textBox2.Text), Convert.ToByte(textBox3.Text), Convert.ToByte(textBox4.Text))
				,Convert.ToInt32(textBox5.Text),checkBox2.Checked);
			DialogResult = DialogResult.OK;
			Close();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			ColorDialog color = new ColorDialog()
			{
				AllowFullOpen = true,
				AnyColor = true
			};
			if(color.ShowDialog() == DialogResult.OK)
			{
				textBox2.Text = color.Color.R + "";
				textBox3.Text = color.Color.G + "";
				textBox4.Text = color.Color.B + "";
			}
			color.Dispose();
		}

		private void button5_Click(object sender, EventArgs e)
		{
			//open docs
		}

		private void button2_Click(object sender, EventArgs e)
		{
			OpenFileDialog openProject = new OpenFileDialog()
			{
				Title = "Open a 3DRadSpace project",
				Filter = "3DRadSpace Project (*.3drsp)|*.3drsp",
				Multiselect = false
			};
			if(openProject.ShowDialog() == DialogResult.OK)
			{
				string f = "//Projects//"+Path.GetFileName(openProject.FileName);
				File.Copy(openProject.FileName, f);
				textBox6.Text = f;
			}
			openProject.Dispose();
		}
	}
}
