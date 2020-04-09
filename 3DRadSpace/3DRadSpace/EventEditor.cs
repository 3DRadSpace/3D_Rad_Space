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
using _3DRadSpaceDll.OpcodeEvent;
using Microsoft.Xna.Framework;

namespace _3DRadSpace
{
	public partial class EventEditor : Form
	{
		public EventEditor(List<OpCodeCall> events,List<int> ids)
		{
			InitializeComponent();
			if(events != null)
			{
				Result = events;
				_old = events;
				for (int i = 0; i < events.Count; i++)
				{
					listBox2.Items.Add(events[i].VisibleString());
				}
			}
			if (ids != null)
			{
				for (int i = 0; i < ids.Count; i++)
				{
					listBox1.Items.Add(_3DRadSpaceDll.Game.GameObjects[ids[i]]+" ("+i+')');
				}
			}
			else Result = new List<OpCodeCall>();
		}

		public List<OpCodeCall> Result;
		public List<OpCodeCall> _old;

		private void EventEditor_Load(object sender, EventArgs e)
		{
			HideAll();
			for (int i=0; i < 11;i++)
			{
				comboBox1.Items.Add(OpCodeCall.GetOpcodeText((Opcode)i));
			}
		}

		private void button3_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.OK;
			Close();
		}

		private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
		{
			//No paranthesis in switch-case kinda gay
			switch (comboBox1.SelectedIndex)
			{
				case (int)Opcode.NOP:
					HideAll();
					break;
				case (int)Opcode.Start:
				case (int)Opcode.Stop:
				case (int)Opcode.Toggle:
				case (int)Opcode.Show:
				case (int)Opcode.Hide:
				case (int)Opcode.RunOneFrame:
					ShowIDField();
					break;
				case (int)Opcode.SetPos:
				case (int)Opcode.AddPos:
				case (int)Opcode.SetRot:
				case (int)Opcode.AddRot:
					ShowIDAndPosFields();
					break;
				default: break;
			}
		}
		void HideAll()
		{
			label3.Visible = false;
			label4.Visible = false;
			label5.Visible = false;
			label6.Visible = false;
			textBox1.Visible = false;
			textBox2.Visible = false;
			textBox3.Visible = false;
			textBox4.Visible = false;
		}
		void ShowIDField()
		{
			label3.Visible = false;
			label4.Visible = false;
			label5.Visible = true;
			label6.Visible = false;
			textBox1.Visible = false;
			textBox2.Visible = false;
			textBox3.Visible = true;
			textBox4.Visible = false;
		}
		void ShowIDAndPosFields()
		{
			label3.Visible = true;
			label4.Visible = true;
			label5.Visible = true;
			label6.Visible = true;
			textBox1.Visible = true;
			textBox2.Visible = true;
			textBox3.Visible = true;
			textBox4.Visible = true;
		}

		private void button1_Click(object sender, EventArgs e)
		{
			OpCodeCall c;
			switch (comboBox1.SelectedIndex)
			{
				case (int)Opcode.Start:
				case (int)Opcode.Stop:
				case (int)Opcode.Toggle:
				case (int)Opcode.Show:
				case (int)Opcode.Hide:
				case (int)Opcode.RunOneFrame:
					c = new OpCodeCall((Opcode)comboBox1.SelectedIndex, new object[] {
					SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox3.Text))
					});
					break;
				case (int)Opcode.SetPos:
				case (int)Opcode.AddPos:
				case (int)Opcode.SetRot:
				case (int)Opcode.AddRot:
					c = new OpCodeCall((Opcode)comboBox1.SelectedIndex, new object[] {
					SafeConverter.IntFromString(Editor.ValidateNumberTextInput(textBox3.Text)),
					new Vector3( 
						SafeConverter.FloatFromString(Editor.ValidateNumberTextInput(textBox1.Text)),
						SafeConverter.FloatFromString(Editor.ValidateNumberTextInput(textBox2.Text)),
						SafeConverter.FloatFromString(Editor.ValidateNumberTextInput(textBox4.Text)))
					});
					break;
				default: c = new OpCodeCall(Opcode.NOP, null); break;
			}
			listBox2.Items.Add(c.VisibleString());
			Result.Add(c);
		}

		private void button2_Click(object sender, EventArgs e)
		{
			if (listBox2.SelectedIndex != -1)
			{
				listBox2.Items.RemoveAt(listBox2.SelectedIndex);
				Result.RemoveAt(listBox2.SelectedIndex);
			}
		}

		private void button4_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
			Result = _old;
			Close();
		}
	}
}
