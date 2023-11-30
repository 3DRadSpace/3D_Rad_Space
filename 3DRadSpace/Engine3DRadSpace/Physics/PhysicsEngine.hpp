#pragma once
#include "PhysicsSettings.hpp"

//PhysX class forward declarations
namespace physx
{
	class PxFoundation;
	class PxDefaultAllocator;
	class PxDefaultErrorCallback;

	class PxPvd;
	class PxPvdTransport;

	class PxPhysics;
	class PxDefaultCpuDispatcher;

	class PxScene;
}

namespace Engine3DRadSpace::Physics
{
	/*
		Manages physics scene, and physics object factory.
	*/
	class DLLEXPORT PhysicsEngine
	{
		std::unique_ptr<physx::PxDefaultAllocator> _allocator;
		std::unique_ptr<physx::PxDefaultErrorCallback> _errCallback;

		physx::PxFoundation* _foundation;
		physx::PxPvd* _pvd;
		physx::PxPvdTransport* _pvdTransport;

		physx::PxPhysics* _physics;
		physx::PxDefaultCpuDispatcher* _cpuDispatcher;

		physx::PxScene* _scene;
	public:
		PhysicsEngine(const PhysicsSettings& settings);

		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine(PhysicsEngine&&) = delete;

		PhysicsEngine& operator=(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(PhysicsEngine&&) = delete;

		void SetGravity(const Math::Vector3 &gravity);
		Math::Vector3 GetGravity();

		void Simulate(float dt);

		~PhysicsEngine();
	};
}