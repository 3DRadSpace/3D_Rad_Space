using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Xna.Framework;
using _3DRadSpaceDll;

namespace _3DRadSpace
{
	public partial class EventOnLocationW : Form
	{
		public EventOnLocationW()
		{
			InitializeComponent();
		}

		GameObject Result;

		private void label8_Click(object sender, EventArgs e)
		{

		}

		private void EventOnLocationW_Load(object sender, EventArgs e)
		{

		}

		private void button2_Click(object sender, EventArgs e)
		{
			BoundingObject type;
			switch (tabControl1.SelectedIndex)
			{
				case 0:
					type = BoundingObject.Box;
					break;
				case 1:
					type = BoundingObject.Sphere;
					break;
				case 2:
					type = BoundingObject.Plane;
					break;
				default:
					type = BoundingObject.None;
					break;
			}
			EventOnLocation r = new EventOnLocation()
			{
				Name = Editor.ValidateTextInput(textBox1.Text),
				Enabled = checkBox1.Checked,
				VisibleInEditor = checkBox2.Checked,
				BoundingType = type
			};
			switch (type)
			{
				case BoundingObject.Box:
					r.BoundingBox = new BoundingBox(
						new Vector3(
							Convert.ToSingle(Editor.ValidateNumberTextInput(textBox2.Text)),
							Convert.ToSingle(Editor.ValidateNumberTextInput(textBox3.Text)),
							Convert.ToSingle(Editor.ValidateNumberTextInput(textBox4.Text))),
						new Vector3(
							Convert.ToSingle(Editor.ValidateNumberTextInput(textBox5.Text)),
							Convert.ToSingle(Editor.ValidateNumberTextInput(textBox6.Text)),
							Convert.ToSingle(Editor.ValidateNumberTextInput(textBox7.Text))));
					r.BoundingSphere = BoundingSphere.CreateFromBoundingBox(r.BoundingBox);
					r.BoundingPlane = new Plane(Vector4.Zero);
					break;
				case BoundingObject.Sphere:
					r.BoundingSphere = new BoundingSphere(new Vector3(
						Convert.ToSingle(Editor.ValidateNumberTextInput(textBox8.Text)),
						Convert.ToSingle(Editor.ValidateNumberTextInput(textBox9.Text)),
						Convert.ToSingle(Editor.ValidateNumberTextInput(textBox10.Text))
						),Convert.ToSingle(Editor.ValidateNumberTextInput(textBox11.Text)));
					r.BoundingBox = BoundingBox.CreateFromSphere(r.BoundingSphere);
					r.BoundingPlane = new Plane(Vector4.Zero);
					break;
				case BoundingObject.Plane:
					r.BoundingPlane = new Plane(new Vector3(
						Convert.ToSingle(Editor.ValidateNumberTextInput(textBox12.Text)),
						Convert.ToSingle(Editor.ValidateNumberTextInput(textBox13.Text)),
						Convert.ToSingle(Editor.ValidateNumberTextInput(textBox14.Text))),
						Convert.ToSingle(Editor.ValidateNumberTextInput(textBox15.Text)));
					r.BoundingBox = new BoundingBox(Vector3.Zero, Vector3.Zero);
					r.BoundingSphere = new BoundingSphere(Vector3.Zero, 0);
					break;
				default: break;
			}
			Result = r;
			DialogResult = DialogResult.OK;
			Close();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
			Result = null;
			Close();
		}

		private void button3_Click(object sender, EventArgs e)
		{
			//open docs
		}

		private void button4_Click(object sender, EventArgs e)
		{
			//open some list thing
		}

		private void button5_Click(object sender, EventArgs e)
		{
			//open event editor.
		}
	}
}
