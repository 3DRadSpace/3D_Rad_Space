#pragma once
#include "../Core/Libs.h"

namespace Engine3DRadSpace::Physics
{
	/// <summary>
	/// Enumeration of supported joint types.
	/// </summary>
	enum class JointType
	{
		/// <summary>
		/// Fixed joint - rigidly locks orientation and position of two actors.
		/// </summary>
		Fixed = 0,

		/// <summary>
		/// Distance joint - maintains a distance range between two actors.
		/// </summary>
		Distance = 1,

		/// <summary>
		/// Spherical joint (ball-and-socket) - locks positions but allows free rotation.
		/// </summary>
		Spherical = 2,

		/// <summary>
		/// Revolute joint (hinge) - allows rotation around a single axis.
		/// </summary>
		Revolute = 3,

		/// <summary>
		/// Prismatic joint (slider) - allows sliding along a single axis.
		/// </summary>
		Prismatic = 4,

		/// <summary>
		/// D6 joint - configurable 6-DOF joint with customizable constraints.
		/// </summary>
		D6 = 5
	};
}
