using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class EffectManager : NatPtrWrapper
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_EffectManager_Create")]
	extern static IntPtr _create();

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_EffectManager_AddShader")]
	extern static IntPtr _addShader(IntPtr manager, string name, IntPtr shader);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_EffectManager_AddEffect")]
	extern static IntPtr _addEffect(IntPtr manager, string name, IntPtr effect);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_EffectManager_GetEffect")]
	extern static IntPtr _getEffect(IntPtr manager, string name);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_EffectManager_GetShader")]
	extern static IntPtr _getShader(IntPtr manager, string name);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_EffectManager_Destroy")]
	extern static void _destroy(IntPtr manager);

	public EffectManager() : base(_create(), _destroy)
	{
	}

	public EffectManager(IntPtr handle) : base(handle, _destroy)
	{
	}

	public void AddShader(string name, IShader shader)
	{
		_addShader(_handle, name, shader.Handle);
	}

	public void AddEffect(string name, Effect effect)
	{
		_addEffect(_handle, name, effect.Handle);
	}

	public Effect GetEffect(string name)
	{
		return new Effect(_getEffect(_handle, name), ownsHandle: false);
	}

	public IShader GetShader(string name)
	{
		return new InstIShader(_getShader(_handle, name), ownsHandle: false);
	}
}
