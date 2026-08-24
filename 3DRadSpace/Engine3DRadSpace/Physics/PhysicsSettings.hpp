#pragma once
#include "../Math/Vector3.hpp"

namespace Engine3DRadSpace::Physics
{
	/// <summary>
	/// Physics engine configuration settings.
	/// </summary>
	struct PhysicsSettings
	{
		/// <summary>
		/// Whether the physics engine is enabled. If set to false, physics calculations will be skipped.
		/// </summary>
		bool PhysicsEnabled = true;
		/// <summary>
		/// Global gravity vector applied to all physics objects. Default is (0, -9.81, 0) representing Earth's gravity.
		/// </summary>
		Math::Vector3 Gravity = Math::Vector3(0.0f, -9.81f, 0.0f);
		/// <summary>
		/// The time step for the physics simulation in seconds. Default is 1/60 seconds.
		/// </summary>
		double TimeStep = 0.0166666666666667; // 1/60 seconds
		/// <summary>
		///	Extra data used for custom physics engine extensions or implementations.
		/// </summary>
		void* Extra = nullptr;
	};
}