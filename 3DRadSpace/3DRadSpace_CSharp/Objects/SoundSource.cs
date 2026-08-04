using Engine3DRadSpace.Audio;
using System.Numerics;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class SoundSource : InstIObject3D
	{
		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetSoundID")]
		extern static uint _getSoundID(IntPtr soundSource);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_SetSoundID")]
		extern static void _setSoundID(IntPtr soundSource, uint soundID);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetSound")]
		extern static IntPtr _getSound(IntPtr soundSource);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetSoundInstance")]
		extern static IntPtr _getSoundInstance(IntPtr soundSource);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetVolume")]
		extern static float _getVolume(IntPtr soundSource);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_SetVolume")]
		extern static float _setVolume(IntPtr soundSource, float volume);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetPitch")]
		extern static float _getPitch(IntPtr soundSource);

		[DllImport("3DRadSpa ce.Objects.dll", EntryPoint = "E3DRSP_SoundSource_SetPitch")]
		extern static float _setPitch(IntPtr soundSource, float pitch);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_IsLooping")]
		extern static byte _looping(IntPtr soundSource);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_SetLooping")]
		extern static void _looping(IntPtr soundSource, byte looping);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetVelocity")]
		extern static Vector3 _getVelocity(IntPtr soundSource);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_SetVelocity")]
        extern static unsafe void _setVelocity(IntPtr soundSource, Vector3* velocity);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetDirection")]
        extern static Vector3 _getDirection(IntPtr soundSource);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_SetDirection")]
		extern static unsafe void _setDirection(IntPtr soundSource, Vector3* direction);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetMaxDistance")]
        extern static float _getMaxDistance(IntPtr soundSource);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_SetMaxDistance")]
        extern static float _setMaxDistance(IntPtr soundSource, float distance);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetReferenceDistance")]
        extern static float _getRefDistance(IntPtr soundSource);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_SetReferenceDistance")]
        extern static float _setRefDistance(IntPtr soundSource, float distance);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetRolloffFactor")]
        extern static float _getRolloff(IntPtr soundSource);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_SetRolloffFactor")]
        extern static float _setReolloff(IntPtr soundSource, float rolloff);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetConeInnerAngle")]
        extern static float _getConeInnerAngle(IntPtr soundSource);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_SetConeInnerAngle")]
        extern static float _setConeInnerAngle(IntPtr soundSource, float angle);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetConeInnerAngle")]
        extern static float _getConeOuterAngle(IntPtr soundSource);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_SetConeInnerAngle")]
        extern static float _setConeOuterAngle(IntPtr soundSource, float angle);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_GetConeInnerGain")]
        extern static float _getConeOuterGain(IntPtr soundSource);

        [DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_SoundSource_SetConeInnerGain")]
        extern static float _setConeOuterGain(IntPtr soundSource, float angle);

        public SoundSource() : base(_create())
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

		public unsafe Vector3 Velocity
		{
			get => _getVelocity(_handle);
			set => _setVelocity(_handle, &value);
		}

		public unsafe Vector3 Direction
		{
			get => _getDirection(_handle);
			set => _setDirection(_handle, &value);
		}

		public float MaxDistance
		{
			get => _getMaxDistance(_handle);
			set => _setMaxDistance(_handle, value);
		}

		public float ReferenceDistance
		{
			get => _getRefDistance(_handle);
			set => _setRefDistance(_handle, value);
		}

		public float RolloffFactor
		{
			get => _getRolloff(_handle);
			set => _setReolloff(_handle, value);
		}

		public float ConeInnerAngle
		{
			get => _getConeInnerAngle(_handle);
			set => _setConeInnerAngle(_handle, value);
		}

		public float ConeOuterAngle
		{
			get => _getConeOuterAngle(_handle);
			set => _setConeOuterAngle(_handle, value);
		}

		public float ConeOuterGain
		{
			get => _getConeOuterGain(_handle);
			set => _setConeOuterGain(_handle, value);
		}
	}
}
