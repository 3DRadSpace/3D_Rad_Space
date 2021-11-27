#pragma once
#include "Globals.hpp"

namespace Engine3DRadSpace
{
	namespace Math
	{
		/// <summary>
		/// Returns the mathematical constant Pi. Pi is the ratio between the circumference and by the diameter of any given circle.
		/// </summary>
		/// <typeparam name="N">A numeric type. Float or double.</typeparam>
		/// <returns></returns>
		template<class N>
		N Pi()
		{
			return (N)3.141592653589793238462643383279;
		}
		/// <summary>
		/// Converts d degrees to radians.
		/// </summary>
		/// <typeparam name="N"></typeparam>
		/// <param name="d">Degrees</param>
		/// <returns></returns>
		template<class N>
		N ToRadians(N d)
		{
			return d * (N)0.01745329252;
		}
		/// <summary>
		/// Converts r radians to degrees.
		/// </summary>
		/// <typeparam name="N">A numeric type. Float or double.</typeparam>
		/// <param name="r">Radians</param>
		/// <returns></returns>
		template<class N>
		N ToDegrees(N r)
		{
			return r * (N)57.2957795131;
		}
		/// <summary>
		/// Clamps the value t between a and b.
		/// </summary>
		/// <typeparam name="N">Any numeric type : float, double, int, unsigned, etc</typeparam>
		/// <param name="a">The left clamp value</param>
		/// <param name="t">The value that is being compared</param>
		/// <param name="b">The right clamp value</param>
		/// <returns>The clamped value</returns>
		template<class N>
		N Clamp(N a, N t, N b)
		{
			if (t < a) return a;
			if (t > b) return b;
			return t;
		}
	}
}