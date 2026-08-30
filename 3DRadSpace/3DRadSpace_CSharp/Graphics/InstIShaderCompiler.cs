using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstIShaderCompiler : NatPtrWrapper, IShaderCompiler
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IShaderCompiler_Destroy")]
	extern static void _destroy(IntPtr compiler);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IShaderCompiler_Compile")]
	extern static CompileOutput _compileShader(IntPtr compiler, IntPtr desc);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IShaderCompiler_CompileEffect")]
	extern static EffectCompileOutput _compileEffect(IntPtr compiler, IntPtr ppDescs, ulong numDescs);

	public InstIShaderCompiler(IntPtr handle) : base(handle, null)
	{
	}

	public CompileOutput CompileShader(ShaderDesc shaderDescription)
	{
		return _compileShader(_handle, shaderDescription.Handle);
	}

	public unsafe EffectCompileOutput CompileEffect(ShaderDesc[] descs)
	{
		ulong numDescs = (ulong)descs.Length;

		nint* ppDescs = stackalloc nint[(int)numDescs];
		for (ulong i = 0; i < numDescs; i++)
		{
			ppDescs[i] = descs[i].Handle;
		}

		return _compileEffect(_handle, (IntPtr)ppDescs, numDescs);
	}
}
