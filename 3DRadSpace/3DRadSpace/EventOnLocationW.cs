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
using _3DRadSpaceDll.ActionScript;

namespace _3DRadSpace
{
	public partial class EventOnLocationW : Form
	{
		public EventOnLocationW()
		{
			InitializeComponent();
		}
		public EventOnLocationW(EventOnLocation eol)
		{
			InitializeComponent();
			textBox1.Text = eol.Name;
			checkBox1.Checked = eol.Enabled;
			checkBox2.Checked = eol.VisibleInEditor;
			textBox2.Text = eol.BoundingBox.Min.X + "";
			textBox3.Text = eol.BoundingBox.Min.Y + "";
			textBox4.Text = eol.BoundingBox.Min.Z + "";
			textBox5.Text = eol.BoundingBox.Max.X + "";
			textBox6.Text = eol.BoundingBox.Max.Y + "";
			textBox7.Text = eol.BoundingBox.Max.Z + "";
			textBox8.Text = eol.BoundingSphere.Center.X + "";
			textBox9.Text = eol.BoundingSphere.Center.Y + "";
			textBox10.Text = eol.BoundingSphere.Center.Z + "";
			textBox11.Text = eol.BoundingSphere.Radius + "";
			textBox12.Text = eol.BoundingPlane.Normal.X + "";
			textBox13.Text = eol.BoundingPlane.Normal.Y + "";
			textBox14.Text = eol.BoundingPlane.Normal.Z + "";
			textBox15.Text = eol.BoundingPlane.D + "";
			_eol = eol;
			opcodes = eol.Behiavours;
		}

		public GameObject Result;
		List<OpCodeCall> opcodes = new List<OpCodeCall>();
		EventOnLocation _eol;

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
			r.Behiavours = opcodes;
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

		private void button5_Click(object sender, EventArgs e)
		{
			EventEditor eventEditor;
			if (_eol != null) eventEditor = new EventEditor(_eol.Behiavours,_eol.SelectedObjects);
			else eventEditor = new EventEditor(null,null);

			if(eventEditor.ShowDialog() == DialogResult.OK)
			{
				opcodes = eventEditor.Result;
			}
			eventEditor.Dispose();
		}
	}
}
