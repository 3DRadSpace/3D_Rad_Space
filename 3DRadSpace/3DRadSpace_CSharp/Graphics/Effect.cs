using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class Effect : NatPtrWrapper
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Effect_Create")]
	extern static IntPtr _create(IntPtr device, IntPtr ppShaders, ulong numShaders);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Effect_SetAll")]
	extern static void _setAll(IntPtr effect);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Effect_Set")]
	extern static void _set(IntPtr effect, int idx);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Effect_SetData")]
	extern static void _setData(IntPtr effect, IntPtr data, ulong dataSize, int cBufferID, int shaderID);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Effect_SetData2")]
	extern static void _setData2(IntPtr effect, IntPtr data, ulong dataSize, int cBufferID);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Effect_SetTexture")]
	extern static void _setTex(IntPtr effect, IntPtr texture, int idTexture);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Effect_SetTexture2")]
	extern static void _setText2(IntPtr effect, IntPtr texture, int idTexture, int shaderID);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Effect_SetSampler")]
	extern static void _setSamp(IntPtr effect, IntPtr sampler, int idTexture);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Effect_SetSampler2")]
	extern static void _setSamp2(IntPtr effect, IntPtr sampler, int idTexture, int shaderID);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Effect_GetShader")]
	extern static IntPtr _getShader(IntPtr effect, int id);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Effect_Destroy")]
	extern static void _destroy(IntPtr effect);

	static unsafe IntPtr _createInstance(IGraphicsDevice device, IShader[] shaders, int numShaders)
	{
		IntPtr* ppShaders = stackalloc IntPtr[numShaders];

		for(int i = 0; i < shaders.Length; i++)
		{
			ppShaders[i] = shaders[i].Handle;
		}

		return _create(device.Handle, ppShaders[0], (ulong)numShaders);
	}

	public Effect(IGraphicsDevice device, IShader[] shaders, int numShaders ) : base(_createInstance(device, shaders, numShaders), _destroy)
	{
	}

	public Effect(IntPtr handle) : base(handle, _destroy)
	{
	}

	internal Effect(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle ? _destroy : null)
	{
	}

	public void SetAll()
	{
		_setAll(_handle);
	}

	public void Set(int shaderID)
	{
		_set(_handle, shaderID);
	}

	public void SetData(IntPtr data, ulong size, int cBufferID, int shaderID)
	{
		_setData(_handle, data, size, cBufferID, shaderID);
	}

	public void SetData(IntPtr data, ulong size, int cBufferID)
	{
		_setData2(_handle, data, size, cBufferID);
	}

	public void SetTexture(ITexture2D texture, int textureID)
	{
		_setTex(_handle, texture.Handle, textureID);
	}

	public void SetTexture(ITexture2D texture, int textureID, int shaderID)
	{
		_setText2(_handle, texture.Handle, textureID, shaderID);
	}

	public void SetSampler(ISamplerState samplerState, int idx)
	{
		_setSamp(_handle, samplerState.Handle, idx);
	}

	public void SetSampler(ISamplerState samplerState, int idx, int shaderID)
	{
		_setSamp2(_handle, samplerState.Handle, idx, shaderID);
	}

	public IShader GetShader(int shaderID)
	{
		return new InstIShader(_getShader(_handle, shaderID), ownsHandle: false);
	}
}
