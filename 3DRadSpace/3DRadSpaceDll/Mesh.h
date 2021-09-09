#pragma once
#include "MeshPart.h"

template<class T>
class Mesh
{
public:
	MeshPart<T>** MeshParts;
	size_t NumParts;
};

