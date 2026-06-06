#include "Statistics.hpp"
#include <cstdlib>
#include <cstdio>

unsigned long long Engine3DRadSpace::Memory::Statistics::AllocatedBytes = 0;
unsigned long long Engine3DRadSpace::Memory::Statistics::NumAllocations = 0;

static char memAllocStrBuffer[255]{};

/*
void *operator new(size_t numBytes)
{
	if(numBytes == 0) return nullptr;
	auto m = malloc(numBytes);
	
	if(m == nullptr) return nullptr;

	Engine3DRadSpace::Memory::Statistics::AllocatedBytes += numBytes;
	Engine3DRadSpace::Memory::Statistics::NumAllocations++;
	
	snprintf(memAllocStrBuffer, 255, "Allocated %zu bytes. Total allocated: %llu bytes in %llu allocations.\n", numBytes, Engine3DRadSpace::Memory::Statistics::AllocatedBytes, Engine3DRadSpace::Memory::Statistics::NumAllocations);
	return m;
}
void operator delete(void *ptr, size_t size)
{
	if(!ptr) return;
		
	Engine3DRadSpace::Memory::Statistics::AllocatedBytes -= size;
	Engine3DRadSpace::Memory::Statistics::NumAllocations--;
	snprintf(memAllocStrBuffer, 255, "Deallocated %zu bytes. Total allocated: %llu bytes in %llu allocations.\n", size, Engine3DRadSpace::Memory::Statistics::AllocatedBytes, Engine3DRadSpace::Memory::Statistics::NumAllocations);
	free(ptr);
}
*/