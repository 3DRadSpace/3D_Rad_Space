using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects;

public class InstIObject2D : NatPtrWrapper
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject2D_GetPosition")]
	extern static Vector2 _getPosition(IntPtr object2D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject2D_SetPosition")]
	extern static void _setPosition(IntPtr object2D, in Vector2 pos);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject2D_GetRotationCenter")]
	extern static Vector2 _getRotationCenter(IntPtr object2D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject2D_SetRotationCenter")]
	extern static void _setRotationCenter(IntPtr object2D, in Vector2 center);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject2D_GetRotation")]
	extern static float _getRotation(IntPtr object2D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject2D_SetRotation")]
	extern static void _setRotation(IntPtr object2D, float rotation);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject2D_GetScale")]
	extern static Vector2 _getScale(IntPtr object2D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject2D_SetScale")]
	extern static void _setScale(IntPtr object2D, in Vector2 scale);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject2D_GetDepth")]
	extern static float _getDepth(IntPtr object2D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject2D_SetDepth")]
	extern static void _setDepth(IntPtr object2D, float depth);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject2D_Destroy")]
	extern static void _destroy(IntPtr object2D);

	public Vector2 Position
	{
		get => _getPosition(_handle);
		set => _setPosition(_handle, in value);
	}

	public Vector2 RotationCenter
	{
		get => _getRotationCenter(_handle);
		set => _setRotationCenter(_handle, in value);
	}

	public float Rotation
	{
		get => _getRotation(_handle);
		set => _setRotation(_handle, value);
	}

	public Vector2 Scale
	{
		get => _getScale(_handle);
		set => _setScale(_handle, in value);
	}

	public float Depth
	{
		get => _getDepth(_handle);
		set => _setDepth(_handle, value);
	}

	public InstIObject2D(IntPtr natPtr) : base(natPtr, null)
	{
	}
}
