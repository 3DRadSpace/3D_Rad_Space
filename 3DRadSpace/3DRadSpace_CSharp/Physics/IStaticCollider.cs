using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Physics;

public class IStaticCollider : ICollider
{
    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IStaticCollider_GetLinearDamping")]
    private static extern float _getLinearDamping(IntPtr collider);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IStaticCollider_SetLinearDamping")]
    private static extern void _setLinearDamping(IntPtr collider, float linearDamping);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IStaticCollider_GetStaticFriction")]
    private static extern float _getStaticFriction(IntPtr collider);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IStaticCollider_SetStaticFriction")]
    private static extern void _setStaticFriction(IntPtr collider, float friction);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IStaticCollider_GetDynamicFriction")]
    private static extern float _getDynamicFriction(IntPtr collider);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IStaticCollider_SetDynamicFriction")]
    private static extern void _setDynamicFriction(IntPtr collider, float friction);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IStaticCollider_GetRestitution")]
    private static extern float _getRestitution(IntPtr collider);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IStaticCollider_SetRestitution")]
    private static extern void _setRestitution(IntPtr collider, float restitution);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IStaticCollider_Destroy")]
    private static extern void _destroy(IntPtr collider);

    public float LinearDamping
    {
        get => _getLinearDamping(_handle);
        set => _setLinearDamping(_handle, value);
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

    public IStaticCollider(IntPtr natPtr) : base(natPtr)
    {
    }

    protected IStaticCollider(IntPtr natPtr, bool ownsHandle) : base(natPtr, ownsHandle)
    {
    }
}
