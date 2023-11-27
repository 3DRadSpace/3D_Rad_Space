#pragma once
#include "../Libs.hpp"
#include <physx/PxScene.h>

class PhysicsEngine : public physx::PxAllocatorCallback
{
	// Inherited via PxAllocatorCallback
	void* allocate(size_t size, const char* typeName, const char* filename, int line) override;
	void deallocate(void* ptr) override;
};