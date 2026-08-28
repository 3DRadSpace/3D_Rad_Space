using System.Runtime.InteropServices;
using System.Numerics;

namespace Engine3DRadSpace.Audio;

[StructLayout(LayoutKind.Sequential)]
public struct AudioSource
{
	float Pitch;

	float Gain;
	float MaxGain;
	float MinGain;

	Vector3 Position;
	Vector3 Velocity;
	Vector3 Direction;

	float MaxDistance;
	float ReferenceDistance;

	float RolloffFactor;

	float ConeOuterGain;
	float ConeInnerAngle;
	float ConeOuterAngle;
	byte Looping;
}
