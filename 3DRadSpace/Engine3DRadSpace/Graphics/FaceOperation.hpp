#pragma once
#include "StencilOperation.hpp"
#include "ComparisonFunction.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents the operations to perform on a face of a stencil buffer.
	/// </summary>
	struct FaceOperation
	{
		/// <summary>
		/// Stencil operation to perform when the stencil test fails.
		/// </summary>
		StencilOperation StencilFail;
		/// <summary>
		///	Stencil operation to perform when the stencil test passes but the depth test fails.
		/// </summary>
		StencilOperation DepthFail;
		/// <summary>
		/// Stecil operation to perform when both the stencil and depth tests pass.
		/// </summary>
		StencilOperation PassOp;
		/// <summary>
		///	Comparison function used for the depth and stencil test.
		/// </summary>
		ComparisonFunction Function;
	};
}