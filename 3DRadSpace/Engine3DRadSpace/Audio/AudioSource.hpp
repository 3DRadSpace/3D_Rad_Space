#pragma once
#include "../Math/Vector3.hpp"

namespace Engine3DRadSpace::Audio
{
	struct AudioSource
	{
		float Pitch;

		float Gain;
		float MaxGain;
		float MinGain;

		Math::Vector3 Position;
		Math::Vector3 Velocity;
		Math::Vector3 Direction;

		float MaxDistance;
		float ReferenceDistance;

		float RolloffFactor;

		float ConeOuterGain;
		float ConeInnerAngle;
		float ConeOuterAngle;

		bool Looping;
	};
}