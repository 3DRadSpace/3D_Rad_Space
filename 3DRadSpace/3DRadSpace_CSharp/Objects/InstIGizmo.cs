using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects;

public class InstIGizmo : InstIUpdateable, IGizmo
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGizmo_GetObject")]
	static extern IntPtr _getObject(IntPtr gizmoHandle);
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGizmo_SetObject")]
	static extern IntPtr _setObject(IntPtr gizmoHandle, IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGizmo_IsSelected")]
	static extern byte _isSelected(IntPtr gizmoHandle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGizmo_SetSelection")]
	static extern void _select(IntPtr gizmoHandle, byte selection);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGizmo_Is3DRenderingAllowed")]
	static extern byte _3d(IntPtr gizmoHandle);
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGizmo_Set3DRenderingAllowed")]
	static extern byte _3d(IntPtr gizmoHandle, byte allow3D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGizmo_Is2DRenderingAllowed")]
	static extern byte _2d(IntPtr gizmoHandle);
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGizmo_Set2DRenderingAllowed")]
	static extern byte _2d(IntPtr gizmoHandle, byte allow3D);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGizmo_IsUpdatingAllowed")]
	static extern byte _update(IntPtr gizmoHandle);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IGizmo_SetUpdatingAllowed")]
	static extern byte _update(IntPtr gizmoHandle, byte allow3D);

	public InstIGizmo(IntPtr handle) : base(handle)
	{
	}

	internal InstIGizmo(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle)
	{
	}

	public IObject Object
	{
		get => new InstIObject(_getObject(_handle), ownsHandle: false);
		set
		{
			var instIobj = value as InstIObject;
			if (instIobj != null)
			{
				_setObject(_handle, instIobj.Handle);
			}
		}
	}
	public bool Selected
	{
		get => _isSelected(_handle) > 0;
		set => _select(_handle, (byte)(value ? 1 : 0));
	}
	public bool Is3DRenderingAllowed
	{
		get => _3d(_handle) > 0;
		set => _3d(_handle, (byte)(value ? 1 : 0));
	}
	public bool Is2DRenderingAllowed
	{
		get => _2d(_handle) > 0;
		set => _2d(_handle, (byte)(value ? 1 : 0));
	}
	public bool IsUpdatingAllowed
	{
		get => _update(_handle) > 0;
		set => _update(_handle, (byte)(value ? 1 : 0));
	}

	public void Draw2D()
	{
		InstIDrawable2D._draw2D(_handle);
	}

	public void Draw3D()
	{
		InstIDrawable3D._draw3D(_handle);
	}

	public void Load()
	{
		InstILoadable._load(_handle);
	}

	public void Load(string path)
	{
		InstILoadable._load2(_handle, path);
	}
}
