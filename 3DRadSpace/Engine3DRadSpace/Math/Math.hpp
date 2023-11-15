#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Math
{
	float DLLEXPORT ToRadians(float degrees);
	float DLLEXPORT ToDegrees(float radians);

	double DLLEXPORT ToRadians(double degrees);
	double DLLEXPORT ToDegrees(double radians);

	double DLLEXPORT CatmullRom(double value1, double value2, double value3, double value4, double amount);
	double DLLEXPORT Hermite(double value1, double tangent1, double value2, double tangent2, double amount);

	//Axis aglined check for one single axis.
	bool DLLEXPORT AABB(float p1, float w1, float p2, float w2);
	bool DLLEXPORT AABB(double p1, double w1, double p2, double w2);

	double DLLEXPORT SmoothStep(double value1, double value2, double amount);
	double DLLEXPORT ReLU(double x);
}