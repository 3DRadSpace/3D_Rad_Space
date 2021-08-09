#pragma once
#include "Libs.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"

class __declspec(dllexport) IObject
{
	std::string Name;

	Vector3 Position;
	Quaternion Rotation;
	Vector3 Scale;

	std::string Resource;

	Matrix GetTranslation();

	virtual char* WriteToFileBuffer(size_t& s) = 0;
	virtual IObject* ReadFromFileBuffer(char* fbuff, size_t s) = 0;
	~IObject();
};

