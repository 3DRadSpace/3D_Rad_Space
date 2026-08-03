using System.Numerics;
using System.Runtime.InteropServices;
using Engine3DRadSpace.Math;

namespace Engine3DRadSpace.Physics;

public class IDynamicCollider : IStaticCollider
{
    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_GetAngularDamping")]
    private static extern float _getAngularDamping(IntPtr collider);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_SetAngularDamping")]
    private static extern void _setAngularDamping(IntPtr collider, float angularDamping);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_GetLinearVelocity")]
    private static extern Vector3 _getLinearVelocity(IntPtr collider);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_SetLinearVelocity")]
    private static extern void _setLinearVelocity(IntPtr collider, ref Vector3 linearVelocity);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_GetAngularVelocity")]
    private static extern Vector3 _getAngularVelocity(IntPtr collider);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_SetAngularVelocity")]
    private static extern void _setAngularVelocity(IntPtr collider, ref Vector3 angularVelocity);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_GetMaxAngularVelocity")]
    private static extern Vector3 _getMaxAngularVelocity(IntPtr collider);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_SetMaxAngularVelocity")]
    private static extern void _setMaxAngularVelocity(IntPtr collider, ref Vector3 linearVelocity);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_AttachShapeBox")]
    private static extern void _attachShapeBox(IntPtr collider, ref BoundingBox box);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_AttachShapeSphere")]
    private static extern void _attachShapeSphere(IntPtr collider, ref BoundingSphere sphere);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_UpdateMassAndInertia")]
    private static extern void _updateMassAndInertia(IntPtr collider);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_ApplyForce")]
    private static extern void _applyForce(IntPtr collider, ref Vector3 force);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_ApplyForceAtCenter")]
    private static extern void _applyForceAtCenter(IntPtr collider, ref Vector3 force, ref Vector3 center);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_ApplyTorque")]
    private static extern void _applyTorque(IntPtr collider, ref Vector3 force);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_ApplyAcceleration")]
    private static extern void _applyAcceleration(IntPtr collider, ref Vector3 acc);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_ApplyAngularAcceleration")]
    private static extern void _applyAngularAcceleration(IntPtr collider, ref Vector3 acc);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_SetKinematic")]
    private static extern void _setKinematic(IntPtr collider, [MarshalAs(UnmanagedType.I1)] bool isKinematic);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_AddLinearVelocity")]
    private static extern void _addLinearVelocity(IntPtr collider, ref Vector3 v);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_AddAngularVelocity")]
    private static extern void _addAngularVelocity(IntPtr collider, ref Vector3 v);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IDynamicCollider_Destroy")]
    private new static extern void _destroy(IntPtr collider);

    public float AngularDamping
    {
        get => _getAngularDamping(_handle);
        set => _setAngularDamping(_handle, value);
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

    public void AttachShape(BoundingBox box)
    {
        _attachShapeBox(_handle, ref box);
    }

    public void AttachShape(BoundingSphere sphere)
    {
        _attachShapeSphere(_handle, ref sphere);
    }

    public void UpdateMassAndInertia()
    {
        _updateMassAndInertia(_handle);
    }

    public void ApplyForce(Vector3 force)
    {
        _applyForce(_handle, ref force);
    }

    public void ApplyForce(Vector3 force, Vector3 center)
    {
        _applyForceAtCenter(_handle, ref force, ref center);
    }

    public void ApplyTorque(Vector3 force)
    {
        _applyTorque(_handle, ref force);
    }

    public void ApplyAcceleration(Vector3 acc)
    {
        _applyAcceleration(_handle, ref acc);
    }

    public void ApplyAngularAcceleration(Vector3 acc)
    {
        _applyAngularAcceleration(_handle, ref acc);
    }

    public void SetKinematic(bool isKinematic)
    {
        _setKinematic(_handle, isKinematic);
    }

    public void AddLinearVelocity(Vector3 v)
    {
        _addLinearVelocity(_handle, ref v);
    }

    public void AddAngularVelocity(Vector3 v)
    {
        _addAngularVelocity(_handle, ref v);
    }

    public IDynamicCollider(IntPtr natPtr) : base(natPtr)
    {
    }
}
