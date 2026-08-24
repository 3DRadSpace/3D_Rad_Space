#pragma once

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Comparison function used for depth and stencil testing in graphics rendering.
	/// </summary>
	enum class ComparisonFunction : int
	{
		/// <summary>
		/// The depth or stencil test never passes.
		/// </summary>
		Never = 1,
		/// <summary>
		///	The depth/stencil tests passes if the new value is less than the existing value.
		/// </summary>
		Less,
		/// <summary>
		/// The depth/stencil tests passes if the new value is equal to the existing value.
		/// </summary>
		Equal,
		/// <summary>
		/// The depth/stencil tests passes if the new value is less than or equal to the existing value.
		///	</summary>
		LessEqual,
		/// <summary>
		/// The depth/stencil tests passes if the new value is greater than the existing value.
		/// </summary>
		Greater,
		/// <summary>
		///	The depth/stencil tests passes if the new value is not equal to the existing value.
		/// </summary>
		NotEqual,
		/// <summary>
		/// The depth/stencil tests passes if the new value is greater than or equal to the existing value.
		/// </summary>
		GreaterEqual,
		/// <summary>
		///	The depth/stencil test always passes.
		/// </summary>
		Always,
	};
}