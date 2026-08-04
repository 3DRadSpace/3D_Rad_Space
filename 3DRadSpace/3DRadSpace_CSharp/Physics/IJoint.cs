using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Physics;

public class IJoint : NatPtrWrapper
{
    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_GetType")]
    private static extern JointType _getType(IntPtr joint);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetActors")]
    private static extern void _setActors(IntPtr joint, IntPtr actor0, IntPtr actor1);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_GetActor0")]
    private static extern IntPtr _getActor0(IntPtr joint);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_GetActor1")]
    private static extern IntPtr _getActor1(IntPtr joint);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetLocalFrame0")]
    private static extern void _setLocalFrame0(IntPtr joint, ref Vector3 position, ref Quaternion rotation);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetLocalFrame1")]
    private static extern void _setLocalFrame1(IntPtr joint, ref Vector3 position, ref Quaternion rotation);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_GetLocalFrame0Position")]
    private static extern Vector3 _getLocalFrame0Position(IntPtr joint);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_GetLocalFrame0Rotation")]
    private static extern Quaternion _getLocalFrame0Rotation(IntPtr joint);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_GetLocalFrame1Position")]
    private static extern Vector3 _getLocalFrame1Position(IntPtr joint);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_GetLocalFrame1Rotation")]
    private static extern Quaternion _getLocalFrame1Rotation(IntPtr joint);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetBreakForce")]
    private static extern void _setBreakForce(IntPtr joint, float force, float torque);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_GetBreakForce")]
    private static extern float _getBreakForce(IntPtr joint);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_GetBreakTorque")]
    private static extern float _getBreakTorque(IntPtr joint);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_IsBroken")]
    [return: MarshalAs(UnmanagedType.I1)]
    private static extern bool _isBroken(IntPtr joint);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_GetForce")]
    private static extern void _getForce(IntPtr joint, ref Vector3 linear, ref Vector3 angular);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetDistanceLimit")]
    private static extern void _setDistanceLimit(IntPtr joint, float minDistance, float maxDistance);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetSphericalLimit")]
    private static extern void _setSphericalLimit(IntPtr joint, float yAngle, float zAngle);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetRevoluteLimit")]
    private static extern void _setRevoluteLimit(IntPtr joint, float lower, float upper);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetRevoluteDrive")]
    private static extern void _setRevoluteDrive(IntPtr joint, float velocity, float forceLimit, [MarshalAs(UnmanagedType.I1)] bool freespin);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetPrismaticLimit")]
    private static extern void _setPrismaticLimit(IntPtr joint, float lower, float upper);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetD6Motion")]
    private static extern void _setD6Motion(IntPtr joint, int axis, int motionType);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetD6LinearLimit")]
    private static extern void _setD6LinearLimit(IntPtr joint, float limit);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetD6TwistLimit")]
    private static extern void _setD6TwistLimit(IntPtr joint, float lower, float upper);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetD6SwingLimit")]
    private static extern void _setD6SwingLimit(IntPtr joint, float yAngle, float zAngle);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetD6Drive")]
    private static extern void _setD6Drive(IntPtr joint, int driveType, float stiffness, float damping, float forceLimit, [MarshalAs(UnmanagedType.I1)] bool acceleration);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetD6DrivePosition")]
    private static extern void _setD6DrivePosition(IntPtr joint, ref Vector3 position, ref Quaternion rotation);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_SetD6DriveVelocity")]
    private static extern void _setD6DriveVelocity(IntPtr joint, ref Vector3 linear, ref Vector3 angular);

    [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IJoint_Destroy")]
    private static extern void _destroy(IntPtr joint);

    public JointType Type => _getType(_handle);

    public void SetActors(IDynamicCollider actor0, IDynamicCollider actor1)
    {
        _setActors(_handle, actor0.Handle, actor1.Handle);
    }

    public IDynamicCollider GetActor0()
    {
        var ptr = _getActor0(_handle);
        return ptr != IntPtr.Zero ? new IDynamicCollider(ptr, ownsHandle: false) : null;
    }

    public IDynamicCollider GetActor1()
    {
        var ptr = _getActor1(_handle);
        return ptr != IntPtr.Zero ? new IDynamicCollider(ptr, ownsHandle: false) : null;
    }

    public void SetLocalFrame0(Vector3 position, Quaternion rotation)
    {
        _setLocalFrame0(_handle, ref position, ref rotation);
    }

    public void SetLocalFrame1(Vector3 position, Quaternion rotation)
    {
        _setLocalFrame1(_handle, ref position, ref rotation);
    }

    public Vector3 GetLocalFrame0Position() => _getLocalFrame0Position(_handle);

    public Quaternion GetLocalFrame0Rotation() => _getLocalFrame0Rotation(_handle);

    public Vector3 GetLocalFrame1Position() => _getLocalFrame1Position(_handle);

    public Quaternion GetLocalFrame1Rotation() => _getLocalFrame1Rotation(_handle);

    public void SetBreakForce(float force, float torque)
    {
        _setBreakForce(_handle, force, torque);
    }

    public float GetBreakForce() => _getBreakForce(_handle);

    public float GetBreakTorque() => _getBreakTorque(_handle);

    public bool IsBroken() => _isBroken(_handle);

    public void GetForce(out Vector3 linear, out Vector3 angular)
    {
        linear = Vector3.Zero;
        angular = Vector3.Zero;
        _getForce(_handle, ref linear, ref angular);
    }

    public void SetDistanceLimit(float minDistance, float maxDistance)
    {
        _setDistanceLimit(_handle, minDistance, maxDistance);
    }

    public void SetSphericalLimit(float yAngle, float zAngle)
    {
        _setSphericalLimit(_handle, yAngle, zAngle);
    }

    public void SetRevoluteLimit(float lower, float upper)
    {
        _setRevoluteLimit(_handle, lower, upper);
    }

    public void SetRevoluteDrive(float velocity, float forceLimit, bool freespin)
    {
        _setRevoluteDrive(_handle, velocity, forceLimit, freespin);
    }

    public void SetPrismaticLimit(float lower, float upper)
    {
        _setPrismaticLimit(_handle, lower, upper);
    }

    public void SetD6Motion(int axis, int motionType)
    {
        _setD6Motion(_handle, axis, motionType);
    }

    public void SetD6LinearLimit(float limit)
    {
        _setD6LinearLimit(_handle, limit);
    }

    public void SetD6TwistLimit(float lower, float upper)
    {
        _setD6TwistLimit(_handle, lower, upper);
    }

    public void SetD6SwingLimit(float yAngle, float zAngle)
    {
        _setD6SwingLimit(_handle, yAngle, zAngle);
    }

    public void SetD6Drive(int driveType, float stiffness, float damping, float forceLimit, bool acceleration)
    {
        _setD6Drive(_handle, driveType, stiffness, damping, forceLimit, acceleration);
    }

    public void SetD6DrivePosition(Vector3 position, Quaternion rotation)
    {
        _setD6DrivePosition(_handle, ref position, ref rotation);
    }

    public void SetD6DriveVelocity(Vector3 linear, Vector3 angular)
    {
        _setD6DriveVelocity(_handle, ref linear, ref angular);
    }

    public IJoint(IntPtr natPtr) : base(natPtr, _destroy)
    {
    }
}
