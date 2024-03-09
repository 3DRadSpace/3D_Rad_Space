#pragma once
#include "PhysicsEngine.hpp"
#include "IPhysicsObject.hpp"

namespace Engine3DRadSpace::Physics
{
	class StaticRigidbody : public IPhysicsObject
	{
	public:
		StaticRigidbody(
			const std::string& name = "StaticRigidbody",
			bool enabled = true,
			Math::Vector3 pos = Math::Vector3::One(),
			Math::Quaternion rotation = Math::Quaternion(),
			Math::Vector3 scale = Math::Vector3::One()
		);
	};
}