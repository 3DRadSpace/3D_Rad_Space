#pragma once
#include "Globals.h"

struct DLLEXPORT Point
{
	int X, Y;
	Point() = default;
	Point(int x, int y) : X(x), Y(y) {};
	
	static Point Zero();
	static Point One();

	Point operator +=(const Point &p);
	Point operator -=(const Point& p);
	Point operator *=(const Point& p);
	Point operator /=(const Point& p);

	friend DLLEXPORT Point operator +(const Point& a, const Point& b);
	friend DLLEXPORT Point operator -(const Point& a, const Point& b);
	friend DLLEXPORT Point operator *(const Point& a, const Point& b);
	friend DLLEXPORT Point operator /(const Point& a, const Point& b);

	friend DLLEXPORT Point operator *(float s,const Point& p);
};

