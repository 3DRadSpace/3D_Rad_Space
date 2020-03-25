using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;

namespace _3DRadSpaceDll
{
	namespace ActionScript
	{
		/// <summary>
		/// The commands that the script can execute.
		/// <para>Name: OPeration CODE</para>
		/// </summary>
		public enum Opcode
		{
			/// <summary>
			/// No operation. Does nothing.
			/// </summary>
			NOP = 0,
			/// <summary>
			/// Starts an object. 
			/// <para>Argument: int -object identifier.</para>
			/// </summary>
			Start,
			/// <summary>
			/// Stops an object.
			/// <para>Argument: int -object identifier.</para>
			/// </summary>
			Stop,
			/// <summary>
			/// Toggles the start/stop state of an object.
			/// <para>Argument: int -object identifier.</para>
			/// </summary>
			Toggle,
			/// <summary>
			/// Shows an object.
			/// <para>Arguments: int -object identifier.</para>
			/// </summary>
			Show,
			/// <summary>
			/// Hides an object.
			/// <para>Arguments: int -object identifier.</para>
			/// </summary>
			Hide,
			/// <summary>
			/// Sets an object's position. 
			/// <para>Arguments: int - object identifier</para>
			/// <para>Vector3 - position.</para>
			/// </summary>
			SetPos,
			/// <summary>
			/// Adds a vector to the object's position.
			/// <para>Arguments:</para>
			/// <para>int - Object identifier.</para>
			/// <para>Vector3 - position</para>
			/// </summary>
			AddPos,
			/// <summary>
			/// Sets the object rotation.
			/// <para>Arguments:</para>
			/// <para>int - Object identifier.</para>
			/// <para>Vector3 - Rotation in Euler angles.</para>
			/// </summary>
			SetRot,
			/// <summary>
			/// Adds a vector to the object's rotation.
			/// <para>Arguments:</para>
			/// <para>int - Object identifier.</para>
			/// <para>Vector3 - Rotation in Euler Angles.</para>
			/// </summary>
			AddRot,
			/// <summary>
			/// Executes a piece of code.
			/// <para>Arguments</para>
			/// <para>string[] - The piece of code to be compiled and then executed.</para>
			/// </summary>
			ExecuteScript
		}
		/// <summary>
		/// Calls an opcode;
		/// </summary>
		public struct OpCodeCall
		{
			Opcode Opcode;
			object[] Arguments;
			/// <summary>
			/// Main opcode constructor.
			/// </summary>
			/// <param name="op">Code.</param>
			/// <param name="args">Function call arguments</param>
			public OpCodeCall(Opcode op, object[] args)
			{
				Opcode = op;
				Arguments = args;
			}
			/// <summary>
			/// Calls the opcode.
			/// </summary>
			public void Call()
			{
				switch (Opcode)
				{
					case Opcode.NOP: break;
					case Opcode.Start:
						{
							int id = Convert.ToInt32(Arguments[0]);
							Game.GameObjects[id].Enable();
							break;
						}
					case Opcode.Stop:
						{
							int id = Convert.ToInt32(Arguments[0]);
							Game.GameObjects[id].Disable();
							break;
						}
					case Opcode.Toggle:
						{
							int id = Convert.ToInt32(Arguments[0]);
							Game.GameObjects[id].Toggle();
							break;
						}
					case Opcode.Show:
						{
							int id = Convert.ToInt32(Arguments[0]);
							Game.GameObjects[id].Show();
							break;
						}
					case Opcode.Hide:
						{
							int id = Convert.ToInt32(Arguments[0]);
							Game.GameObjects[id].Hide();
							break;
						}
					case Opcode.SetPos:
						{
							int id = Convert.ToInt32(Arguments[0]);
							Game.GameObjects[id].Position = (Vector3)Arguments[1];
							break;
						}
					case Opcode.AddPos:
						{
							int id = Convert.ToInt32(Arguments[0]);
							Game.GameObjects[id].Position += (Vector3)Arguments[1];
							break;
						}
					case Opcode.SetRot:
						{
							int id = Convert.ToInt32(Arguments[0]);
							Game.GameObjects[id].Rotation = (Vector3)Arguments[1];
							break;
						}
					case Opcode.AddRot:
						{
							int id = Convert.ToInt32(Arguments[0]);
							Game.GameObjects[id].Rotation += (Vector3)Arguments[1];
							break;
						}
					case Opcode.ExecuteScript:
						{
							/*
							string[] script = (string[])Arguments[0];
							Script s = new Script()
							{
								ClassName = (string)Arguments[1],
								Enabled = true,
							};
							s.Start();
							*/
							break;
						}
					default: break;
				}
			}
			/// <summary>
			/// Returns a string representing the data inside the struct.
			/// </summary>
			/// <returns></returns>
			public override string ToString()
			{
				return (int)Opcode + " " + Arguments;
			}
			/// <summary>
			/// Returns a visible string to be used in UIs.
			/// </summary>
			/// <returns></returns>
			public string VisibleString()
			{
				switch (Opcode)
				{
					case Opcode.Start: return "Start ID:" + Convert.ToInt32(Arguments[0]);
					case Opcode.Stop: return "Stop ID:" + Convert.ToInt32(Arguments[0]);
					case Opcode.Toggle: return "Toggle ID:" + Convert.ToInt32(Arguments[0]);
					case Opcode.Show: return "Show ID:" + Convert.ToInt32(Arguments[0]);
					case Opcode.Hide: return "Hide ID:" + Convert.ToInt32(Arguments[0]);
					case Opcode.SetPos: return "Set Position " + Arguments[1] + " to ID:" + Convert.ToInt32(Arguments[0]);
					case Opcode.AddPos: return "Add Position " + Arguments[1] + " to ID:" + Convert.ToInt32(Arguments[0]);
					case Opcode.SetRot: return "Set Rotation " + Arguments[1] + " to ID:" + Convert.ToInt32(Arguments[0]);
					case Opcode.AddRot: return "Add Rotation " + Arguments[1] + " to ID:" + Convert.ToInt32(Arguments[0]);
					case Opcode.ExecuteScript: return "Execute Script";
					default: return "NOP";
				}
			}
			/// <summary>
			/// Returns a string that represents the opcode without argument.
			/// </summary>
			/// <param name="Arg">Argument Opcode</param>
			/// <returns></returns>
			public static string GetOpcodeText(Opcode Arg)
			{
				switch (Arg)
				{
					case Opcode.Start: return "Start object";
					case Opcode.Stop: return "Stop object";
					case Opcode.Toggle: return "Toggle object";
					case Opcode.Show: return "Show Object";
					case Opcode.Hide: return "Hide Object";
					case Opcode.SetPos: return "Set Object Position ";
					case Opcode.AddPos: return "Add Object Position ";
					case Opcode.SetRot: return "Set Object Rotation ";
					case Opcode.AddRot: return "Add Object Rotation ";
					case Opcode.ExecuteScript: return "Execute Script";
					default: return "NOP";
				}
			}
		}
	}
}