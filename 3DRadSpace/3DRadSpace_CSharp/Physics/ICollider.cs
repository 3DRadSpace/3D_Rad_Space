using System.Numerics;
using System.Runtime.InteropServices;
using Engine3DRadSpace.Math;

namespace Engine3DRadSpace.Physics;

public class ICollider : NatPtrWrapper
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_GetMass")]
	private static extern float _getMass(IntPtr collider);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_SetMass")]
	private static extern void _setMass(IntPtr collider, float mass);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_GetLinearDamping")]
	private static extern float _getLinearDamping(IntPtr collider);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_SetLinearDamping")]
	private static extern void _setLinearDamping(IntPtr collider, float linearDamping);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_GetAngularDamping")]
	private static extern float _getAngularDamping(IntPtr collider);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_SetAngularDamping")]
	private static extern void _setAngularDamping(IntPtr collider, float angularDamping);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_GetStaticFriction")]
	private static extern float _getStaticFriction(IntPtr collider);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_SetStaticFriction")]
	private static extern void _setStaticFriction(IntPtr collider, float staticFriction);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_GetDynamicFriction")]
	private static extern float _getDynamicFriction(IntPtr collider);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_SetDynamicFriction")]
	private static extern void _setDynamicFriction(IntPtr collider, float dynFriction);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_GetRestitution")]
	private static extern float _getRestitution(IntPtr collider);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_SetRestitution")]
	private static extern void _setRestitution(IntPtr collider, float restitution);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_GetLinearVelocity")]
	private static extern Vector3 _getLinearVelocity(IntPtr collider);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_SetLinearVelocity")]
	private static extern void _setLinearVelocity(IntPtr collider, ref Vector3 vel);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_GetAngularVelocity")]
	private static extern Vector3 _getAngularVelocity(IntPtr collider);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_SetAngularVelocity")]
	private static extern void _setAngularVelocity(IntPtr collider, ref Vector3 vel);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_GetMaxAngularVelocity")]
	private static extern Vector3 _getMaxAngularVelocity(IntPtr collider);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_SetMaxAngularVelocity")]
	private static extern void _setMaxAngularVelocity(IntPtr collider, ref Vector3 vel);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_GetPhysics")]
	private static extern IntPtr _getPhysics(IntPtr collider);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_ApplyForce")]
	[return: MarshalAs(UnmanagedType.I1)]
	private static extern bool _applyForce(IntPtr collider, ref Vector3 force);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_ApplyForce2")]
	[return: MarshalAs(UnmanagedType.I1)]
	private static extern bool _applyForce2(IntPtr collider, ref Vector3 force, ref Vector3 center);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_ApplyTorque")]
	[return: MarshalAs(UnmanagedType.I1)]
	private static extern bool _applyTorque(IntPtr collider, ref Vector3 force);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_ApplyAcceleration")]
	[return: MarshalAs(UnmanagedType.I1)]
	private static extern bool _applyAcceleration(IntPtr collider, ref Vector3 acc);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_ApplyAngularAcceleration")]
	[return: MarshalAs(UnmanagedType.I1)]
	private static extern bool _applyAngularAcceleration(IntPtr collider, ref Vector3 acc);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_Intersects")]
	private static extern float _intersects(IntPtr collider, ref Ray r);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_UpdateTransform")]
	private static extern void _updateTransform(IntPtr collider);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_UpdateTransform2")]
	private static extern void _updateTransform2(IntPtr collider, ref Vector3 position, ref Quaternion rotation);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICollider_Destroy")]
	private static extern void _destroy(IntPtr collider);

	public float Mass
	{
		get => _getMass(_handle);
		set => _setMass(_handle, value);
	}

	public Vector3 Position
	{
		get => _getPosition(_handle);
		set => _setPosition(_handle, ref value);
	}

	public Quaternion Rotation
	{
		get => _getRotation(_handle);
		set => _setRotation(_handle, ref value);
	}

	public float LinearDamping
	{
		get => _getLinearDamping(_handle);
		set => _setLinearDamping(_handle, value);
	}

	public float AngularDamping
	{
		get => _getAngularDamping(_handle);
		set => _setAngularDamping(_handle, value);
	}

	public float StaticFriction
	{
		get => _getStaticFriction(_handle);
		set => _setStaticFriction(_handle, value);
	}

	public float DynamicFriction
	{
		get => _getDynamicFriction(_handle);
		set => _setDynamicFriction(_handle, value);
	}

	public float Restitution
	{
		get => _getRestitution(_handle);
		set => _setRestitution(_handle, value);
	}

	public Vector3 LinearVelocity
	{
		get => _getLinearVelocity(_handle);
		set => _setLinearVelocity(_handle, ref value);
	}

	public Vector3 AngularVelocity
	{
		get => _getAngularVelocity(_handle);
		set => _setAngularVelocity(_handle, ref value);
	}

	public Vector3 MaxAngularVelocity
	{
		get => _getMaxAngularVelocity(_handle);
		set => _setMaxAngularVelocity(_handle, ref value);
	}

	public IPhysicsEngine GetPhysics()
	{
		return new IPhysicsEngine(_getPhysics(_handle));
	}

	public bool ApplyForce(Vector3 force)
	{
		return _applyForce(_handle, ref force);
	}

	public bool ApplyForce(Vector3 force, Vector3 center)
	{
		return _applyForce2(_handle, ref force, ref center);
	}

	public bool ApplyTorque(Vector3 force)
	{
		return _applyTorque(_handle, ref force);
	}

	public bool ApplyAcceleration(Vector3 acc)
	{
		return _applyAcceleration(_handle, ref acc);
	}

	public bool ApplyAngularAcceleration(Vector3 acc)
	{
		return _applyAngularAcceleration(_handle, ref acc);
	}

	public float? Intersects(Ray r)
	{
		float result = _intersects(_handle, ref r);
		return float.IsNaN(result) ? null : result;
	}

	public void UpdateTransform()
	{
		_updateTransform(_handle);
	}

	public void UpdateTransform(Vector3 position, Quaternion rotation)
	{
		_updateTransform2(_handle, ref position, ref rotation);
	}

	public ICollider(IntPtr natPtr) : base(natPtr, _destroy)
	{
	}
}
