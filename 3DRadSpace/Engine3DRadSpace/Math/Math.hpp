#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Math
{
	float DLLEXPORT ToRadians(float degrees);
	float DLLEXPORT ToDegrees(float radians);

	double DLLEXPORT ToRadians(double degrees);
	double DLLEXPORT ToDegrees(double radians);

	double DLLEXPORT CatmullRom(float value1, float value2, float value3, float value4, float amount);
}