#pragma once
#include "../Libs.hpp"
#include "PhysicsEngineAllocator.hpp"
#include <physx/PxScene.h>

namespace Engine3DRadSpace::Physics
{
	class PhysicsEngine
	{
		std::unique_ptr<physx::PxScene> _scene;
	public:
		//PhysicsEngine();

		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;

		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;
	};
}