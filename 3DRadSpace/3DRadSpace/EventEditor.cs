using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using _3DRadSpaceDll.ActionScript;
using Microsoft.Xna.Framework;

namespace _3DRadSpace
{
	public partial class EventEditor : Form
	{
		public EventEditor(int[] ids)
		{
			Result = new List<OpCodeCall>();
			InitializeComponent();
			if (ids != null)
			{
				for (int i = 0; i < ids.Length; i++)
				{
					listBox1.Items.Add(_3DRadSpaceDll.Game.GameObjects[ids[i]]);
				}
			}
		}

		public List<OpCodeCall> Result;

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
			switch (comboBox1.SelectedIndex)
			{
				case (int)Opcode.NOP:
					listBox2.Items.Add(new OpCodeCall(Opcode.NOP, null));
					break;
				case (int)Opcode.Start:
				case (int)Opcode.Stop:
				case (int)Opcode.Toggle:
				case (int)Opcode.Show:
				case (int)Opcode.Hide:
				case (int)Opcode.RunOneFrame:
					listBox2.Items.Add(new OpCodeCall((Opcode)comboBox1.SelectedIndex, new object[] {
					Convert.ToInt32(Editor.ValidateNumberTextInput(textBox3.Text))
					}));
					break;
				case (int)Opcode.SetPos:
				case (int)Opcode.AddPos:
				case (int)Opcode.SetRot:
				case (int)Opcode.AddRot:
					listBox2.Items.Add(new OpCodeCall((Opcode)comboBox1.SelectedIndex, new object[] {
					Convert.ToInt32(Editor.ValidateNumberTextInput(textBox3.Text)),
					new Vector3( 
						Convert.ToSingle(Editor.ValidateNumberTextInput(textBox1.Text)),
						Convert.ToSingle(Editor.ValidateNumberTextInput(textBox2.Text)),
						Convert.ToSingle(Editor.ValidateNumberTextInput(textBox4.Text)))
					}));
					break;
				default: break;
			}
		}
	}
}
