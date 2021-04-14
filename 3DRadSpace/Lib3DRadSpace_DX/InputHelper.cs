using Microsoft.Xna.Framework.Input;

namespace Lib3DRadSpace_DX
{
	/// <summary>
	/// This is used for the editor.
	/// Functions are taken from the 0.0.6a bulid
	/// </summary>
    public static class InputHelper
    {
		/// <summary>
		/// Gets the key from the given string.
		/// </summary>
		/// <param name="item"></param>
		/// <returns></returns>
		public static Keys GetKeyFromString(string item)
		{
			switch(item)
			{
				case "Q": return Keys.Q;
				case "W": return Keys.W;
				case "E": return Keys.E;
				case "R": return Keys.R;
				case "T": return Keys.T;
				case "Y": return Keys.Y;
				case "U": return Keys.U;
				case "I": return Keys.I;
				case "O": return Keys.O;
				case "P": return Keys.P;
				case "A": return Keys.A;
				case "S": return Keys.S;
				case "D": return Keys.D;
				case "F": return Keys.F;
				case "G": return Keys.G;
				case "H": return Keys.H;
				case "J": return Keys.J;
				case "K": return Keys.K;
				case "L": return Keys.L;
				case "Z": return Keys.Z;
				case "X": return Keys.X;
				case "C": return Keys.C;
				case "V": return Keys.V;
				case "B": return Keys.B;
				case "N": return Keys.N;
				case "M": return Keys.M;
				case "1": return Keys.D1;
				case "2": return Keys.D2;
				case "3": return Keys.D3;
				case "4": return Keys.D4;
				case "5": return Keys.D5;
				case "6": return Keys.D6;
				case "7": return Keys.D7;
				case "8": return Keys.D8;
				case "9": return Keys.D9;
				case "0": return Keys.D0;
				case "Left Shift": return Keys.LeftShift;
				case "Right Shift": return Keys.RightShift;
				case "Left Ctrl": return Keys.LeftControl;
				case "Right Ctrl": return Keys.RightControl;
				case "Tab": return Keys.Tab;
				case "Up Arrow": return Keys.Up;
				case "Down Arrow": return Keys.Down;
				case "Left Arrow": return Keys.Left;
				case "Right Arrow": return Keys.Right;
				case "Enter": return Keys.Enter;
				case "Space": return Keys.Space;
				case "ESC": return Keys.Escape;
				default: return Keys.None;
			}
		}

		/// <summary>
		/// Gets a string from the given key
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		public static string GetStringFromKey(Keys arg)
		{
			switch(arg)
			{
				case Keys.Q: return "Q";
				case Keys.W: return "W";
				case Keys.E: return "E";
				case Keys.R: return "R";
				case Keys.T: return "T";
				case Keys.Y: return "Y";
				case Keys.U: return "U";
				case Keys.I: return "I";
				case Keys.O: return "O";
				case Keys.P: return "P";
				case Keys.A: return "A";
				case Keys.S: return "S";
				case Keys.D: return "D";
				case Keys.F: return "F";
				case Keys.G: return "G";
				case Keys.H: return "H";
				case Keys.J: return "J";
				case Keys.K: return "K";
				case Keys.L: return "L";
				case Keys.Z: return "Z";
				case Keys.X: return "X";
				case Keys.C: return "C";
				case Keys.V: return "V";
				case Keys.B: return "B";
				case Keys.N: return "N";
				case Keys.M: return "M";
				case Keys.D1: return "1";
				case Keys.D2: return "2";
				case Keys.D3: return "3";
				case Keys.D4: return "4";
				case Keys.D5: return "5";
				case Keys.D6: return "6";
				case Keys.D7: return "7";
				case Keys.D8: return "8";
				case Keys.D9: return "9";
				case Keys.D0: return "0";
				case Keys.LeftShift: return "Left Shift";
				case Keys.RightShift: return "Right Shift";
				case Keys.LeftControl: return "Left Ctrl";
				case Keys.RightControl: return "Roght Ctrl";
				case Keys.Tab: return "Tab";
				case Keys.Up: return "Up Arrow";
				case Keys.Down: return "Down Arrow";
				case Keys.Left: return "Left Arrow";
				case Keys.Right: return "Right Arrow";
				case Keys.Enter: return "Enter";
				case Keys.Space: return "Space";
				case Keys.Escape: return "ESC";
				default: return null;
			}
		}
	}
}
