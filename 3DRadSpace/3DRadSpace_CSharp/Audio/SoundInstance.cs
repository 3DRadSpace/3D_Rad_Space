using System.Runtime.InteropServices;
using System.Numerics;

namespace Engine3DRadSpace.Audio;
public class SoundInstance : NatPtrWrapper
{
	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_Create")]
	private static extern IntPtr create(IntPtr sound, IntPtr source);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_Destroy")]
	private static extern void destroy(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetPitch")]
	private static extern float getPitch(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetPitch")]
	private static extern void setPitch(IntPtr sound, float pitch);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetGain")]
	private static extern float getGain(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetGain")]
	private static extern void setGain(IntPtr sound, float gain);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetMaxGain")]
	private static extern float getMaxGain(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetMaxGain")]
	private static extern void setMaxGain(IntPtr sound, float gain);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetMinGain")]
	private static extern float getMinGain(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetMinGain")]
	private static extern void setMinGain(IntPtr sound, float gain);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetPosition")]
	private static extern IntPtr getPosition(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetPosition")]
	private static extern void setPostion(IntPtr sound, IntPtr pos);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetVelocity")]
	private static extern IntPtr getVelocity(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetVelocity")]
	private static extern void setVelocity(IntPtr sound, IntPtr vel);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetDirection")]
	private static extern IntPtr getDirection(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetDirection")]
	private static extern void setDirection(IntPtr sound, IntPtr dir);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetMaxDistance")]
	private static extern float getMaxDistance(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetMaxDistance")]
	private static extern void setMaxDistance(IntPtr sound, float dst);


	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetReferenceDistance")]
	private static extern float getReferenceDistance(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetReferenceDistance")]
	private static extern void setReferenceDistance(IntPtr sound, float refDst);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetRolloffFactor")]
	private static extern float getRolloffFactor(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetRolloffFactor")]
	private static extern void setRolloffFactor(IntPtr sound, float rolloff);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetConeOuterGain")]
	private static extern float getConeOuterGain(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetConeOuterGain")]
	private static extern void setConeOuterGain(IntPtr sound, float gain);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetConeInnerAngle")]
	private static extern float getConeInnerAngle(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetConeInnerAngle")]
	private static extern void setConeInnerAngle(IntPtr sound, float angle);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_GetConeOuterAngle")]
	private static extern float getConeOuterAngle(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetConeOuterAngle")]
	private static extern void setConeOuterAngle(IntPtr sound, float rolloff);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_IsLooping")]
	private static extern byte isLooping(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_SetLooping")]
	private static extern void setLooping(IntPtr sound, byte looping);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_Play")]
	private static extern void play(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_Stop")]
	private static extern void stop(IntPtr sound);

	[DllImport("3DRadSpace.FFI.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "E3DRSP_handle_Pause")]
	private static extern void pause(IntPtr sound);

	public unsafe SoundInstance(Sound sound, AudioSource source) : base(create(sound.Handle, (nint)(&source)), destroy)
	{
	}

	public SoundInstance(IntPtr ptrSI) : base(ptrSI, destroy)
	{
	}

	internal SoundInstance(IntPtr ptrSI, bool ownsHandle) : base(ptrSI, ownsHandle ? destroy : null)
	{
	}

	public float Pitch
	{
		get => getPitch(_handle);
		set => setPitch(_handle, value);
	}

	public float Gain
	{
		get => getGain(_handle);
		set => setGain(_handle, value);
	}

	public float MaxGain
	{
		get => getMaxGain(_handle);
		set => setMaxGain(_handle, value);
	}

	public float MinGain
	{
		get => getMinGain(_handle);
		set => setMinGain(_handle, value);
	}

	public unsafe Vector3 Position
	{
		get => *(Vector3*)getPosition(_handle);
		set => setPostion(_handle, (IntPtr)(&value));
	}

	public unsafe Vector3 Velocity
	{
		get => *((Vector3*)getVelocity(_handle));
		set => setVelocity(_handle, (IntPtr)(&value));
	}

	public unsafe Vector3 Direction
	{
		get => *((Vector3*)getDirection(_handle));
		set => setDirection(_handle, (IntPtr)(&value));
	}

	public float MaxDistance
	{
		get => getMaxDistance(_handle);
		set => setMaxDistance(_handle, value);
	}

	public float RerefenceDistance
	{
		get => getReferenceDistance(_handle);
		set => setReferenceDistance(_handle, value);
	}

	public float RolloffFactor
	{
		get => getRolloffFactor(_handle);
		set => setRolloffFactor(_handle, value);
	}

	public float ConeOuterGain
	{
		get => getConeOuterGain(_handle);
		set => setConeOuterGain(_handle, value);
	}

	public float ConeInnerAngle
	{
		get => getConeInnerAngle(_handle);
		set => setConeInnerAngle(_handle, value);
	}

	public float ConeOuterAngle
	{
		get => getConeOuterAngle(_handle);
		set => setConeOuterAngle(_handle, value);
	}

	public bool IsLooping
	{
		get => isLooping(_handle) > 0;
		set => setLooping(_handle, (byte)(value ? 1 : 0));
	}

	public void Play()
	{
		play(_handle);
	}

	public void Stop()
	{
		stop(_handle);
	}

	public void Pause()
	{
		pause(_handle);
	}
}
