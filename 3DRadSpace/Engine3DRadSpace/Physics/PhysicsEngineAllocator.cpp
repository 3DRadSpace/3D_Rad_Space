#include "PhysicsEngineAllocator.hpp"

void* PhysicsEngine::allocate(size_t size, const char* typeName, const char* filename, int line)
{
    return std::malloc(size);
}

void PhysicsEngine::deallocate(void* ptr)
{
    std::free(ptr);
}
