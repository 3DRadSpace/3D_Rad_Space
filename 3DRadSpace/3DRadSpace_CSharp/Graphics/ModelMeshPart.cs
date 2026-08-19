using Engine3DRadSpace.Math;
using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class ModelMeshPart : NatPtrWrapper
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMeshPart_Destroy")]
	extern static void _destroy(IntPtr meshPart);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMeshPart_Create")]
	extern static unsafe IntPtr _create1(
		IntPtr device,
		IntPtr pVertexData,
		ulong numVerts,
		ulong structSize,
		uint* indices,
		ulong numIndices
	);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMeshPart_Create2")]
	extern static IntPtr _create2(
		IntPtr vBuffer,
		IntPtr iBuffer
	);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMeshPart_GetBoundingBox")]
	extern static BoundingBox _bbox(IntPtr meshPart);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMeshPart_GetBoundingSphere")]
	extern static BoundingSphere _bsph(IntPtr meshPart);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMeshPart_GetVertexBuffer")]
	extern static IntPtr _vbuff(IntPtr meshPart);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMeshPart_GetIndexBuffer")]
	extern static IntPtr _ibuff(IntPtr meshPart);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMeshPart_GetTransform")]
	extern static Matrix4x4 _getMatrix(IntPtr meshPart);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMeshPart_SetTransform")]
	extern static unsafe void _setMatrix(IntPtr meshPart, Matrix4x4 *matrix);

	public ModelMeshPart(IntPtr handle) : base(handle, _destroy)
	{
	}

	public unsafe ModelMeshPart(
		IGraphicsDevice device,
		IntPtr pVertexData,
		ulong numVerts,
		ulong structSize,
		uint* indices,
		ulong numIndices
	) : base(_create1(device.Handle, pVertexData, numVerts, structSize, indices, numIndices), _destroy)
	{
	}

	public ModelMeshPart(IVertexBuffer vbuff, IIndexBuffer ibuff, Effect effect) : base(_create2(vbuff.Handle, ibuff.Handle), _destroy)
	{
	}

	public BoundingBox BoundingBox
	{
		get => _bbox(_handle);
	}

	public BoundingSphere BoundingSphere
	{
		get => _bsph(_handle);
	}

	public IVertexBuffer VertexBuffer
	{
		get => new InstIVertexBuffer(_vbuff(_handle), ownsHandle: false);
	}

	public IIndexBuffer IndexBuffer
	{
		get => new InstIIndexBuffer(_ibuff(_handle), ownsHandle: false);
	}

	public unsafe Matrix4x4 Transform
	{
		get => _getMatrix(_handle);
		set => _setMatrix(_handle, &value);
	}
}
