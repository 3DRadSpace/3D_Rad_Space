using System.Numerics;
using System.Runtime.InteropServices;
using Engine3DRadSpace.Math;

namespace Engine3DRadSpace.Objects;

public class InstIObject3D : NatPtrWrapper
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject3D_GetPosition")]
	extern static Vector3 _getPosition(IntPtr object3D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject3D_SetPosition")]
	extern static void _setPosition(IntPtr object3D, in Vector3 pos);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject3D_GetRotationCenter")]
	extern static Vector3 _getRotationCenter(IntPtr object3D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject3D_SetRotationCenter")]
	extern static void _setRotationCenter(IntPtr object3D, in Vector3 center);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject3D_GetRotation")]
	extern static Quaternion _getRotation(IntPtr object3D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject3D_SetRotation")]
	extern static void _setRotation(IntPtr object3D, in Quaternion rotation);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject3D_GetScale")]
	extern static Vector3 _getScale(IntPtr object3D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject3D_SetScale")]
	extern static void _setScale(IntPtr object3D, in Vector3 scale);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject3D_GetModelMatrix")]
	extern static Matrix4x4 _getModelMatrix(IntPtr object3D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject3D_Intersects")]
	extern static float _intersects(IntPtr object3D, in Ray ray);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject3D_Destroy")]
	extern static void _destroy(IntPtr object3D);

	public Vector3 Position
	{
		get => _getPosition(_handle);
		set => _setPosition(_handle, in value);
	}

	public Vector3 RotationCenter
	{
		get => _getRotationCenter(_handle);
		set => _setRotationCenter(_handle, in value);
	}

	public Quaternion Rotation
	{
		get => _getRotation(_handle);
		set => _setRotation(_handle, in value);
	}

	public Vector3 Scale
	{
		get => _getScale(_handle);
		set => _setScale(_handle, in value);
	}

	public Matrix4x4 GetModelMatrix()
	{
		return _getModelMatrix(_handle);
	}

	public float? Intersects(Ray ray)
	{
		float result = _intersects(_handle, in ray);
		return float.IsNaN(result) ? null : result;
	}

	public InstIObject3D(IntPtr natPtr) : base(natPtr, null)
	{
	}
}
