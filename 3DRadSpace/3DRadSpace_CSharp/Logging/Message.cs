using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Logging;

[StructLayout(LayoutKind.Sequential)]
public struct Message
{
	[MarshalAs(UnmanagedType.LPStr)]
	public string Details;
	public int Code;
	public IntPtr Extra;

	public Message(string details, int code, IntPtr extra)
	{
		Details = details;
		Code = code;
		Extra = extra;
	}

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_PrintMessage")]
	public extern static void PrintMessage(ref Message msg);
}
