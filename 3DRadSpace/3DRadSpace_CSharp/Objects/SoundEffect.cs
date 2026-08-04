using Engine3DRadSpace.Audio;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class SoundEffect : InstIObject
	{
		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundEffect_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundEffect_GetSoundID")]
		extern static uint _getSoundID(IntPtr soundEffect);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundEffect_SetSoundID")]
		extern static void _setSoundID(IntPtr soundEffect, uint soundID);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundEffect_GetSound")]
		extern static IntPtr _getSound(IntPtr soundEffect);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundEffect_GetSoundInstance")]
		extern static IntPtr _getSoundInstance(IntPtr soundEffect);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundEffect_GetVolume")]
		extern static float _getVolume(IntPtr soundEffect);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundEffect_SetVolume")]
		extern static float _setVolume(IntPtr soundEffect, float volume);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundEffect_GetPitch")]
		extern static float _getPitch(IntPtr soundEffect);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundEffect_SetPitch")]
		extern static float _setPitch(IntPtr soundEffect, float pitch);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundEffect_IsLooping")]
		extern static byte _looping(IntPtr soundEffect);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundEffect_SetLooping")]
		extern static void _looping(IntPtr soundEffect, byte looping);

		public SoundEffect() : base(_create())
		{
		}

		public uint SoundID
		{
			get => _getSoundID(_handle);
			set => _setSoundID(_handle, value);
		}

		public Sound GetSound()
		{
			return new Sound(_getSound(_handle), ownsHandle: false);
		}

		public SoundInstance GetSoundInstance()
		{
			return new SoundInstance(_getSoundInstance(_handle), ownsHandle: false);
		}

		public float Volume
		{
			get => _getVolume(_handle);
			set => _setVolume(_handle, value);
		}

		public float Pitch
		{
			get => _getPitch(_handle);
			set => _setPitch(_handle, value);
		}

		public bool Looping
		{
			get => _looping(_handle) > 0;
			set => _looping(_handle, value == true ? (byte)1 : (byte)0);
		}
	}
}
