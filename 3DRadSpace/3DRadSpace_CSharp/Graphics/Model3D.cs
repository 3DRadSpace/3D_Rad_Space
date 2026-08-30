using Engine3DRadSpace.Math;
using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class Model3D : NatPtrWrapper
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "EDRSP_Model3D_Create")]
	extern static IntPtr _create(IntPtr device, string path);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "EDRSP_Model3D_NumMeshes")]
	extern static ulong _num(IntPtr model);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "EDRSP_Model3D_GetMesh")]
	extern static IntPtr _at(IntPtr model, ulong idx);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "EDRSP_Model3D_GetBoundingBox")]
	extern static BoundingBox _bbox(IntPtr model);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "EDRSP_Model3D_GetBoundingSphere")]
	extern static BoundingSphere _bsph(IntPtr model);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "EDRSP_Model3D_SetShader")]
	extern static void _setShader(IntPtr model, IntPtr shader);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "EDRSP_Model3D_SetShaders")]
	extern static unsafe void _setShader(IntPtr model, IntPtr* shaders, ulong numShaders);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "EDRSP_Model3D_Destroy")]
	extern static unsafe void _setTransform(IntPtr model, Matrix4x4* mat);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "EDRSP_Model3D_Destroy")]
	extern static void _destroy(IntPtr model);

	public Model3D(IntPtr handle) : base(handle, null)
	{
	}

	public Model3D(IGraphicsDevice device, string path) : base(_create(device.Handle, path), null)
	{
	}

	public ulong NumMeshes
	{
		get => _num(_handle);
	}

	public ModelMesh this[ulong idx]
	{
		get => new ModelMesh(_at(_handle, idx));
	}

	public BoundingBox BoundingBox
	{
		get => _bbox(_handle);
	}

	public BoundingSphere BoundingSphere
	{
		get => _bsph(_handle);
	}

	public void SetShader(Effect effect)
	{
		_setShader(_handle, effect.Handle);
	}

	public unsafe void SetShaders(Effect[] effects)
	{
		ulong numEffects = (ulong)effects.Length;

		IntPtr* ppShaders = stackalloc IntPtr[(int)numEffects];
		for (ulong i = 0; i < numEffects; i++)
		{
			ppShaders[i] = effects[i].Handle;
		}

		_setShader(_handle, ppShaders, numEffects);
	}

	public unsafe Matrix4x4 Transform
	{
		set => _setTransform(_handle, &value);
	}
}
