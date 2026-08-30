using Engine3DRadSpace.Reflection;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstIVertexShader : NatPtrWrapper, IVertexShader
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IVertexShader_GetInputLayout")]
	extern static unsafe IntPtr* _inputLayout(IntPtr vshader, ulong *outSize);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IVertexShader_Destroy")]
	extern static void _destroy(IntPtr vshader);

	public InstIVertexShader(IntPtr handle) : base(handle, null)
	{
	}

	public unsafe IReflectedField[] GetInputLayout()
	{
		ulong numFields;
		var ppFields = _inputLayout(_handle, &numFields);

		IReflectedField[] r = new IReflectedField[numFields];
		for(ulong i = 0; i < numFields; i++)
		{
			r[i] = new InstIReflectedField(ppFields[i]);
		}

		return r;
	}
}
