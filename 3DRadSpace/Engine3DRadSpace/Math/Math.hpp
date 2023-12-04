#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Math
{
	constexpr float DLLEXPORT ToRadians(float degrees);
	constexpr float DLLEXPORT ToDegrees(float radians);

	constexpr double DLLEXPORT ToRadians(double degrees);
	constexpr double DLLEXPORT ToDegrees(double radians);

	constexpr double DLLEXPORT CatmullRom(double value1, double value2, double value3, double value4, double amount);
	constexpr double DLLEXPORT Hermite(double value1, double tangent1, double value2, double tangent2, double amount);

	//Axis aglined check for one single axis.
	constexpr bool DLLEXPORT AABB(float p1, float w1, float p2, float w2);
	constexpr bool DLLEXPORT AABB(double p1, double w1, double p2, double w2);

	constexpr double DLLEXPORT SmoothStep(double value1, double value2, double amount);
	constexpr double DLLEXPORT ReLU(double x);

	constexpr bool DLLEXPORT WithinEpsilon(float a, float b);
}