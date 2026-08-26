using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Audio;

public class AudioEngine : IDisposable
{
	private IntPtr _audio;
	private bool _disposed;

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioEngine_Create")]
	private static extern IntPtr create();

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioEngine_Create1")]
	private static extern IntPtr create1(string deviceName);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_AudioEngine_ListAudioDevices")]
	private static extern IntPtr listAudioDevices();

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_IAudioEngine_SwitchAudioDevice")]
	private static extern void switchDevice(IntPtr audio, string name);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_IAudioEngine_Update")]
	private static extern void update(IntPtr audio);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_IAudioEngine_CheckErrors")]
	private static extern int checkErrors(IntPtr audio);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_IAudioEngine_Destroy")]
	private static extern void destroy(IntPtr audio);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IAudioEngine_GetListener")]
	private static extern Listener getListener(IntPtr audio);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_IAudioEngine_SetListener")]
	private static extern void setListener(IntPtr audio,in Listener listener);

	public AudioEngine()
	{
		_audio = create();
		_disposed = false;
	}

	public AudioEngine(string deviceName)
	{
		_audio = create1(deviceName);
		_disposed = false;
	}

	public unsafe static List<string>? ListAudioDevices()
	{
		List<string> result = new();

		IntPtr ptr = listAudioDevices();
		if (ptr == IntPtr.Zero)
		{
			return null;
		}

		char* currentString = null;
		do
		{
			currentString = *((char**)ptr);

			if (currentString != null)
			{
				var strPtr = Marshal.PtrToStringAnsi((IntPtr)currentString);
				result.Add(strPtr != null ? strPtr : "");
				ptr += 1;
			}
			else
			{
				break;
			}
		}
		while (true);

		return result;
	}

	public void SwitchAudioDevice(string deviceName)
	{
		switchDevice(_audio, deviceName);
	}

	public void Update()
	{
		update(_audio);
	}

	public AudioError CheckErrors()
	{
		return (AudioError)checkErrors(_audio);
	}

	public nint Handle
	{
		get => _audio;
	}

	public Listener Listener
    {
        get => getListener(_audio);
        set => setListener(_audio, value);
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

		if (_audio != 0)
		{
			destroy(_audio);
			_audio = 0;
		}

		_disposed = true;
	}

	~AudioEngine()
	{
		Dispose(false);
	}
}
