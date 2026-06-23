#include "PhysicsEngine.hpp"
#include "../../Logging/Exception.hpp"
#include "../../Logging/Message.hpp"
#include "StaticMeshCollider.hpp"
#include "DynamicCollider.hpp"
#include "CharacterController.hpp"
#include "Joint.hpp"
#include "ErrorCallback.hpp"
#include <extensions/PxDefaultCpuDispatcher.h>
#include <extensions/PxDefaultAllocator.h>
#include <PxPhysicsAPI.h>

using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::NVPhysX;
using namespace Engine3DRadSpace::Logging;

PhysicsEngine::PhysicsEngine(const PhysicsSettings& settings) :
	_timeStep(settings.TimeStep)
{
	if (!settings.PhysicsEnabled) return;

	_allocator = std::make_unique<physx::PxDefaultAllocator>();
	_errCallback = std::make_unique<ErrorCallback>();

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

	// Enable CCD (Continuous Collision Detection) at scene level
	sceneDesc.flags |= physx::PxSceneFlag::eENABLE_CCD;

	_scene = _physics->createScene(sceneDesc);
	if (_scene == nullptr) throw Exception("Failed to create PxScene!");

	auto chrMan = PxCreateControllerManager(*_scene);
	_controllerManager.reset(chrMan);

	Logging::SetLastMessage("Initialized PhysX");
}

void PhysicsEngine::SetGravity(const Math::Vector3& gravity)
{
	static_cast<physx::PxScene*>(_scene)->setGravity(physx::PxVec3(gravity.X, gravity.Y, gravity.Z));
}

Vector3 PhysicsEngine::GetGravity() const
{
	auto g = _scene->getGravity();
	return Vector3(g.x, g.y, g.z);
}

void PhysicsEngine::Simulate(float dt)
{
	for (_accTimer += dt; _accTimer >= _timeStep; _accTimer -= _timeStep)
	{
		_scene->simulate(static_cast<float>(_timeStep));
		_scene->fetchResults(true);
	}
}

void* PhysicsEngine::GetFoundation() const noexcept
{
	return _foundation;
}

void* PhysicsEngine::GetPvd() const noexcept
{
	return _pvd;
}

void* PhysicsEngine::GetPhysics() const noexcept
{
	return _physics;
}

void* PhysicsEngine::GetCPUDispatcher() const noexcept
{
	return  _cpuDispatcher;
}

void* PhysicsEngine::GetScene() const noexcept
{
	return _scene;
}

PhysicsEngine::~PhysicsEngine()
{
	_controllerManager.reset();
	PX_RELEASE(_scene);
	PX_RELEASE(_cpuDispatcher);
	PX_RELEASE(_physics);

	if(_pvd)
	{
		auto transport = _pvd->getTransport();
		PX_RELEASE(transport);
		PX_RELEASE(_pvd);
	}

	PX_RELEASE(_foundation);
}

std::unique_ptr<IStaticCollider> PhysicsEngine::CreateStaticCollider(
	Graphics::Model3D* model,
	const Math::Vector3& position,
	const Math::Quaternion& rotation,
	const Math::Vector3 &scale
)
{
	return std::make_unique<StaticMeshCollider>(this, model, position, rotation, scale);
}

std::unique_ptr<IDynamicCollider> PhysicsEngine::CreateDynamicCollider()
{
	return std::make_unique<DynamicCollider>(this);
}

std::unique_ptr<ICharacterController> PhysicsEngine::CreateCharacterController(float radius, float height, const Math::Vector3& position)
{
	return std::make_unique<CharacterController>(this, height, radius, position);
}

std::unique_ptr<IJoint> PhysicsEngine::CreateJoint(JointType type)
{
	return std::make_unique<Joint>(this, type);
}

double PhysicsEngine::dt() const noexcept
{
	return _timeStep;
}