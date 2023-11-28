#include "PhysicsEngine.hpp"
#include <physx/PxPhysicsAPI.h>
#include <physx/extensions/PxDefaultAllocator.h>
#include "../Logging/Exception.hpp"

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Logging;

PhysicsEngine::PhysicsEngine(const PhysicsSettings& settings)
{
	if (!settings.PhysicsEnabled) return;

	_allocator = std::make_unique<physx::PxDefaultAllocator>();
	_errCallback = std::make_unique<physx::PxDefaultErrorCallback>();

	_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, *_allocator, *_errCallback);
	if (_foundation == nullptr) throw Exception("Failed to create PxFoundation");

	_pvd = physx::PxCreatePvd(*_foundation);
	_pvdTransport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	_pvd->connect(*_pvdTransport, physx::PxPvdInstrumentationFlag::eALL);

	bool trackMemoryAllocations = false;
#if _DEBUG
	trackMemoryAllocations = true;
#endif

	_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_foundation, physx::PxTolerancesScale(), trackMemoryAllocations, _pvd);
	if (_physics == nullptr) throw Exception("Failed to create PxPhysics!");

	_cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(4);

	physx::PxSceneDesc sceneDesc(_physics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(settings.Gravity.X, settings.Gravity.Y, settings.Gravity.Z);
	sceneDesc.cpuDispatcher = _cpuDispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

	_scene = _physics->createScene(sceneDesc);
	if (_scene == nullptr) throw Exception("Failed to create PxScene!");
}

void PhysicsEngine::SetGravity(const Math::Vector3& gravity)
{
	_scene->setGravity(physx::PxVec3(gravity.X, gravity.Y, gravity.Z));
}

Vector3 PhysicsEngine::GetGravity()
{
	auto g = _scene->getGravity();
	return Vector3(g.x, g.y, g.z);
}

void PhysicsEngine::Simulate(float dt)
{
	_scene->simulate(dt);
	_scene->fetchResults(false);
}

PhysicsEngine::~PhysicsEngine()
{
	PX_RELEASE(_scene);
	PX_RELEASE(_cpuDispatcher);
	PX_RELEASE(_physics);

	if (_pvd)
	{
		physx::PxPvdTransport* transport = _pvd->getTransport();
		PX_RELEASE(transport);

		_pvd->release();
		_pvd = nullptr;
	}

	PX_RELEASE(_foundation);
}
