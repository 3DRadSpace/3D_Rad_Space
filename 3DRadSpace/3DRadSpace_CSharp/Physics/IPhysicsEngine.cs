using System.Numerics;
using System.Runtime.InteropServices;
using Engine3DRadSpace.Graphics;
using Engine3DRadSpace.Math;

namespace Engine3DRadSpace.Physics;

public class IPhysicsEngine : InstIService
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IPhysicsEngine_Simulate")]
	private static extern void _simulate(IntPtr physics, float dt);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IPhysicsEngine_GetScene")]
	private static extern IntPtr _getScene(IntPtr physics);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IPhysicsEngine_CreateStaticCollider")]
	private static extern IntPtr _createStaticCollider(IntPtr physics, IntPtr model, ref Vector3 position, ref Quaternion rotation, ref Vector3 scale);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IPhysicsEngine_CreateDynamicCollider")]
	private static extern IntPtr _createDynamicCollider(IntPtr physics);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IPhysicsEngine_CreateCharacterController")]
	private static extern IntPtr _createCharacterController(IntPtr physics, float radius, float height, ref Vector3 position);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IPhysicsEngine_CreateJoint")]
	private static extern IntPtr _createJoint(IntPtr physics, JointType type);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IPhysicsEngine_GetDT")]
	private static extern double _getDT(IntPtr physics);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IPhysicsEngine_SetGravity")]
	private static extern void _setGravity(IntPtr physics, ref Vector3 gravity);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IPhysicsEngine_GetGravity")]
	private static extern Vector3 _getGravity(IntPtr physics);

	public void Simulate(float dt)
	{
		_simulate(_handle, dt);
	}

	public IntPtr GetScene()
	{
		return _getScene(_handle);
	}

	public IStaticCollider CreateStaticCollider(Model3D model, Vector3 position, Quaternion rotation, Vector3 scale)
	{
		var ptr = _createStaticCollider(_handle, model.Handle, ref position, ref rotation, ref scale);
		return new IStaticCollider(ptr);
	}

	public IDynamicCollider CreateDynamicCollider()
	{
		var ptr = _createDynamicCollider(_handle);
		return new IDynamicCollider(ptr);
	}

	public ICharacterController CreateCharacterController(float radius, float height, Vector3 position)
	{
		var ptr = _createCharacterController(_handle, radius, height, ref position);
		return new ICharacterController(ptr);
	}

	public IJoint CreateJoint(JointType type)
	{
		var ptr = _createJoint(_handle, type);
		return new IJoint(ptr);
	}

	public double DT => _getDT(_handle);

	public Vector3 Gravity
	{
		get => _getGravity(_handle);
		set => _setGravity(_handle, ref value);
	}

	public IPhysicsEngine(IntPtr natPtr) : base(natPtr)
	{
	}

	internal IPhysicsEngine(IntPtr natPtr, bool ownsHandle) : base(natPtr, ownsHandle)
	{
	}
}
