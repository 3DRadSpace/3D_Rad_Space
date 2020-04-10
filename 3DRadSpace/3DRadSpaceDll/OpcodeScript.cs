using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;

namespace _3DRadSpaceDll
{
	namespace OpcodeEvent
	{
		/// <summary>
		/// The commands that the script can execute.
		/// <para>Name: OPeration CODE</para>
		/// </summary>
		public enum Opcode
		{
			/// <summary>
			/// No operation. Does nothing.
			/// <para>Can be used to store object IDs or other data.</para>
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
			/// Starts an object, update it, then stop it.
			/// <para>Arguments</para>
			/// <para>int - Object ID</para>
			/// </summary>
			RunOneFrame
		}
		/// <summary>
		/// Calls an opcode;
		/// </summary>
		public struct OpCodeCall
		{
			/// <summary>
			/// 
			/// </summary>
			public Opcode Opcode;
			/// <summary>
			/// 
			/// </summary>
			public object[] Arguments;
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
							int id = SafeConverter.IntFromString(Arguments[0]);
							Game.GameObjects[id].Enable();
							if (Game.GameObjects[id] is SoundEffect ef) ef.Trigger();
							break;
						}
					case Opcode.Stop:
						{
							int id = SafeConverter.IntFromString(Arguments[0]);
							Game.GameObjects[id].Disable();
							break;
						}
					case Opcode.Toggle:
						{
							int id = SafeConverter.IntFromString(Arguments[0]);
							Game.GameObjects[id].Toggle();
							break;
						}
					case Opcode.Show:
						{
							int id = SafeConverter.IntFromString(Arguments[0]);
							Game.GameObjects[id].Show();
							break;
						}
					case Opcode.Hide:
						{
							int id = SafeConverter.IntFromString(Arguments[0]);
							Game.GameObjects[id].Hide();
							break;
						}
					case Opcode.SetPos:
						{
							int id = SafeConverter.IntFromString(Arguments[0]);
							Game.GameObjects[id].Position = (Vector3)Arguments[1];
							break;
						}
					case Opcode.AddPos:
						{
							int id = SafeConverter.IntFromString(Arguments[0]);
							Game.GameObjects[id].Position += (Vector3)Arguments[1];
							break;
						}
					case Opcode.SetRot:
						{
							int id = SafeConverter.IntFromString(Arguments[0]);
							Game.GameObjects[id].Rotation = (Vector3)Arguments[1];
							break;
						}
					case Opcode.AddRot:
						{
							int id = SafeConverter.IntFromString(Arguments[0]);
							Game.GameObjects[id].Rotation += (Vector3)Arguments[1];
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
				string args = "";
				switch(Opcode)
				{
					case Opcode.Start:
					case Opcode.Stop:
					case Opcode.Toggle:
					case Opcode.Show: 
					case Opcode.Hide:
					case Opcode.RunOneFrame:
						args = Arguments[0] + "";
						break;
					case Opcode.SetPos:
					case Opcode.AddPos:
					case Opcode.SetRot: 
					case Opcode.AddRot:
						Vector3 v = (Vector3)Arguments[1];
						args = Arguments[0] + " " + v.X + ' ' + v.Y + ' ' + v.Z;
						break;
					default: break ;
				}
				return (int)Opcode + " "+args ;
			}
			/// <summary>
			/// Returns a visible string to be used in UIs.
			/// </summary>
			/// <returns></returns>
			public string VisibleString()
			{
				switch (Opcode)
				{
					case Opcode.Start: return "Start ID:" + SafeConverter.IntFromString(Arguments[0]);
					case Opcode.Stop: return "Stop ID:" + SafeConverter.IntFromString(Arguments[0]);
					case Opcode.Toggle: return "Toggle ID:" + SafeConverter.IntFromString(Arguments[0]);
					case Opcode.Show: return "Show ID:" + SafeConverter.IntFromString(Arguments[0]);
					case Opcode.Hide: return "Hide ID:" + SafeConverter.IntFromString(Arguments[0]);
					case Opcode.SetPos: return "Set Position " + Arguments[1] + " to ID:" + SafeConverter.IntFromString(Arguments[0]);
					case Opcode.AddPos: return "Add Position " + Arguments[1] + " to ID:" + SafeConverter.IntFromString(Arguments[0]);
					case Opcode.SetRot: return "Set Rotation " + Arguments[1] + " to ID:" + SafeConverter.IntFromString(Arguments[0]);
					case Opcode.AddRot: return "Add Rotation " + Arguments[1] + " to ID:" + SafeConverter.IntFromString(Arguments[0]);
					case Opcode.RunOneFrame: return "Run once ID: " + SafeConverter.IntFromString(Arguments[0]); ;
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
					case Opcode.RunOneFrame: return "Run once";
					default: return "NOP";
				}
			}
			/// <summary>
			/// Runs a array
			/// </summary>
			/// <param name="e"></param>
			public static void Run(List<OpCodeCall> e)
			{
				for(int i =0; i < e.Count;i++) e[i].Call();
			}
			/// <summary>
			/// Used in I/O operations.
			/// </summary>
			/// <param name="offset">Integer offset</param>
			/// <param name="str">Parsed string array</param>
			/// <param name="stop"></param>
			/// <returns></returns>
			public static List<OpCodeCall> CreateFromString(int offset,string[] str,int stop)
			{
				List<OpCodeCall> c = new List<OpCodeCall>();
				for(int i =offset; i < stop;i++)
				{
					Opcode op = (Opcode)SafeConverter.IntFromString(str[i]);
					switch (op)
					{
						case Opcode.Start:
						case Opcode.Stop:
						case Opcode.Toggle:
						case Opcode.Show: 
						case Opcode.Hide:
						case Opcode.RunOneFrame:
							c.Add(new OpCodeCall(op, new object[] { SafeConverter.IntFromString(str[i + 1]) }));
							i += 1;
							break;
						case Opcode.SetPos:
						case Opcode.AddPos:
						case Opcode.SetRot:
						case Opcode.AddRot:
							c.Add(new OpCodeCall(op, new object[] { SafeConverter.IntFromString(str[i + 1]),
							new Vector3( SafeConverter.FloatFromString(str[i+2]),SafeConverter.FloatFromString(str[i+3]),SafeConverter.FloatFromString(str[i+4]))
							}));
							i += 4;
							break;
						default: break;
					}
				}
				return c;
			}
			/// <summary>
			/// Create from a null-terminated buffer.
			/// </summary>
			/// <param name="buf"></param>
			/// <param name="offset"></param>
			/// <param name="length"></param>
			/// <returns></returns>
			public static List<OpCodeCall> CreateFromBuffer(byte[] buf,int offset,out int length)
			{
				List<OpCodeCall> c = new List<OpCodeCall>();
				int i = offset;
				for (; buf[i] != 0 ; i++)
				{
					Opcode op = (Opcode)BitConverter.ToInt32(buf, offset);
					i += sizeof(int);
					switch (op)
					{
						case Opcode.Start:
						case Opcode.Stop:
						case Opcode.Toggle:
						case Opcode.Show:
						case Opcode.Hide:
						case Opcode.RunOneFrame:
							c.Add(new OpCodeCall(op, new object[] { BitConverter.ToInt32(buf,i) }));
							i += sizeof(int);
							break;
						case Opcode.SetPos:
						case Opcode.AddPos:
						case Opcode.SetRot:
						case Opcode.AddRot:
							c.Add(new OpCodeCall(op, new object[] { BitConverter.ToInt32(buf,i),
							new Vector3( BitConverter.ToSingle(buf,i+sizeof(float)),BitConverter.ToSingle(buf,i+(2*sizeof(float))),BitConverter.ToSingle(buf,i+(3*sizeof(float))))
							}));
							i += sizeof(float) * 3 + sizeof(int);
							break;
						default: break;
					}
				}
				length = i - offset;
				return c;
			}
			/// <summary>
			/// used for i/o operations.
			/// </summary>
			/// <param name="opcodes"></param>
			/// <returns></returns>
			public static List<byte> ToBytes(List<OpCodeCall> opcodes)
			{
				List<byte> c = new List<byte>();
				for (int i = 0 ; i < opcodes.Count; i++)
				{
					Opcode op = opcodes[i].Opcode;
					c.AddRange(BitConverter.GetBytes((int)op));
					switch (op)
					{
						case Opcode.Start:
						case Opcode.Stop:
						case Opcode.Toggle:
						case Opcode.Show:
						case Opcode.Hide:
						case Opcode.RunOneFrame:
							c.AddRange(BitConverter.GetBytes((int)opcodes[i].Arguments[0]));
							break;
						case Opcode.SetPos:
						case Opcode.AddPos:
						case Opcode.SetRot:
						case Opcode.AddRot:
							c.AddRange(BitConverter.GetBytes((int)opcodes[i].Arguments[0]));
							c.AddRange(BitConverter.GetBytes(((Vector3)opcodes[i].Arguments[1]).X));
							c.AddRange(BitConverter.GetBytes(((Vector3)opcodes[i].Arguments[1]).Y));
							c.AddRange(BitConverter.GetBytes(((Vector3)opcodes[i].Arguments[1]).Z));
							break;
						default: break;
					}
				}
				return c;
			}
		}
	}
}