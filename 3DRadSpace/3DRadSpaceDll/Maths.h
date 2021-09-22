#pragma once
#include "Globals.h"

namespace Math
{
	template<class N>
	N Pi()
	{
		return (N)3.141592653589793238462643383279;
	}
	template<class N>
	N ToRadians(N d)
	{
		return d * (N)0.01745329252;
	}
	template<class N>
	N ToDegrees(N r)
	{
		return r * (N)57.2957795131;
	}
}