using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class ModelMesh : NatPtrWrapper
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMesh_Create")]
	extern static unsafe IntPtr _create(IntPtr* parts, ulong numParts);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMesh_Destroy")]
	extern static void _destroy(IntPtr modelMesh);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMesh_AddMeshPart")]
	extern static void _addPart(IntPtr modelMesh, IntPtr part);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMesh_GetMeshPart")]
	extern static IntPtr _at(IntPtr modelMesh, uint idx);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMesh_NumMeshParts")]
	extern static ulong _count(IntPtr modelMesh);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMesh_GetBoundingBox")]
	extern static Math.BoundingBox _bbox(IntPtr modelMesh);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_ModelMesh_GetBoundingSphere")]
	extern static Math.BoundingSphere _bsph(IntPtr modelMesh);

	public ModelMesh(IntPtr handle) : base(handle, _destroy)
	{
	}

	unsafe static IntPtr _callCreate(ModelMeshPart[] parts)
	{
		ulong numParts = (ulong)parts.Length;

		IntPtr* ppParts = stackalloc IntPtr[(int)numParts];
		for (ulong i = 0; i < numParts; i++)
		{
			ppParts[i] = parts[i].Handle;
		}
		return _create(ppParts, numParts);
	}

	public ModelMesh(ModelMeshPart[] parts) : this(_callCreate(parts))
	{
	}

	public void AddPart(ModelMeshPart part)
	{
		_addPart(_handle, part.Handle);
	}

	public ModelMeshPart this[uint idx]
	{
		get => new ModelMeshPart(_at(_handle, idx));
	}

	public BoundingBox BoundingBox
	{
		get => _bbox(_handle);
	}

	public BoundingSphere BoundingSphere
	{
		get => _bsph(_handle);
	}
}
