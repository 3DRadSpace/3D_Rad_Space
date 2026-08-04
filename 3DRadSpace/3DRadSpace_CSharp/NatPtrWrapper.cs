namespace Engine3DRadSpace;

/// <summary>
/// Wraps an unmanaged pointer with an destructor function.
/// </summary>
public class NatPtrWrapper : IDisposable, IPtrWrapper
{
	protected IntPtr _handle;
	protected bool _disposed;
	Action<IntPtr> _destroy;

	protected NatPtrWrapper(IntPtr handle, Action<IntPtr> fnDestroy)
	{
		_handle = handle;
		_disposed = false;
		_destroy = fnDestroy;
	}

	protected NatPtrWrapper(Action<IntPtr> fnDestroy)
	{
		_handle = IntPtr.Zero;
		_disposed = true;
		_destroy = fnDestroy;
	}

	protected void Reset(IntPtr newObj)
	{
		if (_handle != IntPtr.Zero)
		{
			_destroy(_handle);
		}

		_disposed = false;
		_handle = newObj;
	}

	public IntPtr Handle
	{
		get 
		{
			return _handle;
		} 
	}

	public virtual void Dispose()
	{
		Dispose(true);
		GC.SuppressFinalize(this);
	}

	protected void Dispose(bool disposing)
	{
		if (!_disposed)
		{
			if (_handle != IntPtr.Zero && _destroy != null)
			{
				_destroy(_handle);
			}
			_disposed = true;
			_handle = IntPtr.Zero;
		}
	}

	~NatPtrWrapper()
	{
		Dispose(false);
	}
}
