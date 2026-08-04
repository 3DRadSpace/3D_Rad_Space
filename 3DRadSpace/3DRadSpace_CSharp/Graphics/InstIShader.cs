using Engine3DRadSpace.Reflection;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class InstIShader : NatPtrWrapper, IShader
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IShader_Destroy")]
	extern static void _destroy(IntPtr shader);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IShader_SetData")]
	extern static void _setData(IntPtr shader, uint index, IntPtr data, ulong dataSize);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IShader_SetTexture")]
	extern static void _setTexture(IntPtr shader, uint index, IntPtr texture);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IShader_SetTextures")]
	extern static void _setTextures(IntPtr shader, IntPtr ppTextures, ulong numTextures);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IShader_SetSampler")]
	extern static void _setSampler(IntPtr shader, uint index, IntPtr sampler);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IShader_SetShader")]
	extern static void _set(IntPtr shader);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IShader_GetVariables")]
	extern unsafe static IntPtr _variables(IntPtr shader, ulong *outSize);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IShader_Set")]
	extern unsafe static IntPtr _setVariable(IntPtr shader, string name, IntPtr data, ulong dataSize);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi,  EntryPoint = "E3DRSP_IShader_GetEntryName")]
	extern unsafe static IntPtr _entryName(IntPtr shader);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_IShader_GetCompilationErrorsAndWarnings")]
	extern unsafe static IntPtr _log(IntPtr shader);

	public InstIShader(IntPtr handle) : base(handle, _destroy)
	{

	}

	internal InstIShader(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle ? _destroy : null)
	{
	}

	public string EntryName
	{
		get => Marshal.PtrToStringAnsi(_entryName(_handle));
	}

	public string CompilationErrorsAndWarnings
	{
		get => Marshal.PtrToStringAnsi(_log(_handle));
	}

	public void SetData(uint index, nint data, ulong dataSize)
	{
		_setData(_handle, index, data, dataSize);
	}

	public void SetTexture(uint index, ITexture2D texture)
	{
		_setTexture(_handle, index, texture.Handle);
	}

	public unsafe void SetTextures(Span<ITexture2D> textures)
	{
		nint* ppTextures = stackalloc nint[textures.Length];
		for (int i = 0; i < textures.Length; i++)
		{
			ppTextures[i] = textures[i].Handle;
		}
		
		_setTextures(_handle, (IntPtr)ppTextures, (ulong)textures.Length);
	}

	public void SetSampler(uint index, ISamplerState samplerState)
	{
		_setSampler(_handle, index, samplerState.Handle);
	}

	public void SetShader()
	{
		_set(_handle);
	}

	public unsafe IReflectedField[] GetVariables()
	{
		ulong numVars;
		IntPtr pVars = _variables(_handle, &numVars);

		IReflectedField[] result = new IReflectedField[numVars];

		for (ulong i = 0; i < numVars; i++)
		{
			result[i] = new InstIReflectedField(pVars);
		}

		return result;
	}
}
