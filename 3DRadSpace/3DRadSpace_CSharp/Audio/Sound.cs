using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Audio;

public class Sound : IDisposable
{
    [DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Sound_Create")]
    private static extern IntPtr create(AudioEngine audio, string path);

    [DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_Sound_Destroy")]
    private static extern void destroy(IntPtr sound);

    IntPtr _sound;
    bool _disposed;
    bool _ownsHandle;

    public Sound(AudioEngine audio, string path)
    {
        _sound = create(audio, path);
        _disposed = false;
        _ownsHandle = true;
    }

    public Sound(IntPtr ptrSound)
    {
        _sound = ptrSound;
        _disposed = false;
        _ownsHandle = true;
    }

    internal Sound(IntPtr ptrSound, bool ownsHandle)
    {
        _sound = ptrSound;
        _disposed = false;
        _ownsHandle = ownsHandle;
    }

    public nint Handle
    {
        get => _sound;
    }

    public void Dispose()
    {
        Dispose(true);
        GC.SuppressFinalize(this);
    }

    protected virtual void Dispose(bool disposing)
    {
        if (_disposed)
        {
            return;
        }

        if (_sound != 0 && _ownsHandle)
        {
            destroy(_sound);
            _sound = 0;
        }

        _disposed = true;
    }

    ~Sound()
    {
        Dispose(false);
    }
}
