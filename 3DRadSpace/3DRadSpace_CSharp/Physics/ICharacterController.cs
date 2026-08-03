using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Physics;

public class ICharacterController : ICollider
{
    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_Move")]
    private static extern void _move(IntPtr controller, ref Vector3 displacement);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_Jump")]
    private static extern void _jump(IntPtr controller, float height);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_GetHeight")]
    private static extern float _getHeight(IntPtr controller);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_SetHeight")]
    private static extern void _setHeight(IntPtr controller, float height);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_GetRadius")]
    private static extern float _getRadius(IntPtr controller);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_SetRadius")]
    private static extern void _setRadius(IntPtr controller, float radius);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_SetMaxSlopeAngle")]
    private static extern void _setMaxSlopeAngle(IntPtr controller, float angle);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_GetMaxSlopeAngle")]
    private static extern float _getMaxSlopeAngle(IntPtr controller);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_SetGravity")]
    private static extern void _setGravity(IntPtr controller, ref Vector3 gravity);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_GetGravity")]
    private static extern Vector3 _getGravity(IntPtr controller);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_IsGrounded")]
    [return: MarshalAs(UnmanagedType.I1)]
    private static extern bool _isGrounded(IntPtr controller);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ICharacterController_Destroy")]
    private static extern void _destroy(IntPtr controller);

    public void Move(Vector3 displacement)
    {
        _move(_handle, ref displacement);
    }

    public void Jump(float height)
    {
        _jump(_handle, height);
    }

    public float Height
    {
        get => _getHeight(_handle);
        set => _setHeight(_handle, value);
    }

    public float Radius
    {
        get => _getRadius(_handle);
        set => _setRadius(_handle, value);
    }

    public float MaxSlopeAngle
    {
        get => _getMaxSlopeAngle(_handle);
        set => _setMaxSlopeAngle(_handle, value);
    }

    public Vector3 Gravity
    {
        get => _getGravity(_handle);
        set => _setGravity(_handle, ref value);
    }

    public bool IsGrounded()
    {
        return _isGrounded(_handle);
    }

    public ICharacterController(IntPtr natPtr) : base(natPtr, _destroy)
    {
    }
}
