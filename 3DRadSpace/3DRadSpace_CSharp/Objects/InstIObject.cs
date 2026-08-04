using Engine3DRadSpace.Graphics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects;

public class InstIObject : InstIUpdateable, IObject
{
	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_GetUUID")]
	extern static Reflection.UUID _getUUID(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_GetGizmo")]
	extern static IntPtr _getGizmo(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_GetGraphicsDeviceHandle")]
	extern static IntPtr _getGDevice(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_GetGame")]
	extern static IntPtr _getGame(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_Enable")]
	extern static void _enable(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_Disable")]
	extern static void _disable(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_Switch")]
	extern static byte _switch(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_IsEnabled")]
	extern static byte _isEnabled(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_Show")]
	extern static void _show(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_Hide")]
	extern static void _hide(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_SwitchVisibility")]
	extern static byte _switchVisibility(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_IsVisible")]
	extern static byte _isVisible(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_IObject_GetName")]
	extern static IntPtr _getName(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_IObject_SetName")]
	extern static void _setName(IntPtr obj, string name);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_Children")]
	extern static IntPtr _getChildren(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_GetChild")]
	extern static IntPtr _getChild(IntPtr obj, UIntPtr idxChild);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_GetChildrenCount")]
	extern static UIntPtr _getChildrenCount(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_GetParent")]
	extern static IntPtr _getParent(IntPtr obj);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IObject_SetParent")]
	extern static void _setParent(IntPtr obj, IntPtr currentOwner, IntPtr newParent);

	InstIInitializable _initializable;
	InstILoadable _loadable;
	ObjectCollection _children;

	public InstIObject(IntPtr handle) : base(handle)
	{
		_initializable = new InstIInitializable(handle);
		_loadable = new InstILoadable(handle);
		_children = new ObjectCollection(_getChildren(handle));
	}

	internal InstIObject(IntPtr handle, bool ownsHandle) : base(handle, ownsHandle)
	{
		_initializable = new InstIInitializable(handle);
		_loadable = new InstILoadable(handle);
		_children = new ObjectCollection(_getChildren(handle));
	}

	public IObject GetChild(int idx)
	{
		var ptr = _getChild(_handle, (UIntPtr)idx);
		if (ptr == IntPtr.Zero) return null;
		return new InstIObject(ptr, ownsHandle: false);
	}

	public int GetChildrenCount()
	{
		return (int)_getChildrenCount(_handle);
	}

	public IObject? Parent
	{
		get
		{
			var ptr = _getParent(_handle);
			if (ptr == IntPtr.Zero) return null;
			return new InstIObject(ptr);
		}
		set
		{
			var handleParent = _getParent(_handle);
			if(value is null) _setParent(_handle, handleParent, IntPtr.Zero);

			var obj = value as InstIObject;
            IntPtr newParentPtr = obj != null ? obj.Handle : IntPtr.Zero;
			_setParent(_handle, _handle, newParentPtr);
        }
	}

	public string Name
	{
		get => Marshal.PtrToStringAnsi(_getName(_handle));
        set => _setName(_handle, value);
	}

	public bool Enabled
	{
		get => _isEnabled(_handle) > 0;
		set
		{
			if (value)
			{
				_enable(_handle);
			}
			else
			{
				_disable(_handle);
			}
		}
	}

	public bool Visible
	{
		get => _isVisible(_handle) > 0;
		set
		{
			if (value)
			{
				_show(_handle);
			}
			else
			{
				_hide(_handle);
			}
		}
	}

	public void Enable()
	{
		_enable(_handle);
	}

	public void Disable()
	{
		_disable(_handle);
	}

	public bool Switch()
	{
		return _switch(_handle) > 0;
	}

	public void Show()
	{
		_show(_handle);
	}

	public void Hide()
	{
		_hide(_handle);
	}

	public bool SwitchVisibility()
	{
		return _switchVisibility(_handle) > 0;
	}

	public Reflection.UUID UUID => _getUUID(_handle);

	public IGame Game => new InstIGame(_getGame(_handle), ownsHandle: false);
	public IGraphicsDevice GraphicsDevice => new InstIGraphicsDevice(_getGDevice(_handle), ownsHandle: false);
	public IGizmo Gizmo => new InstIGizmo(_getGizmo(_handle), ownsHandle: false);

	public void Initialize()
	{
		_initializable.Initialize();
	}

	public void Load()
	{
		_loadable.Load();
	}

	public void Load(string path)
	{
		_loadable.Load(path);
	}

	public ObjectCollection Children
	{
		get => _children;
	}

	public override void Dispose()
	{
		base.Dispose();
		_initializable.Dispose();
		_loadable.Dispose();
	}
}
