#pragma once
#include "../Math/Vector3.hpp"

namespace Engine3DRadSpace::Physics
{
	struct PhysicsSettings
	{
		bool PhysicsEnabled;
		Math::Vector3 Gravity;
		double TimeStep;
	};
}