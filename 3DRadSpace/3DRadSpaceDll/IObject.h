#pragma once
#include "Globals.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"

#pragma warning( push )
#pragma warning( disable : 4251 )

class DLLEXPORT IObject
{
	std::string Name;

	Vector3 Position;
	
	Vector3 Center;
	Quaternion Rotation;

	Vector3 Scale;

	std::string Resource;

	Matrix GetTranslation();

	virtual char* WriteToFileBuffer(size_t& s) = 0;
	virtual IObject* ReadFromFileBuffer(char* fbuff, size_t s) = 0;
	~IObject();
};

#pragma warning( pop )
