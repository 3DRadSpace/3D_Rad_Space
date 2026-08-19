#pragma once

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Describes material properties.
	/// </summary>
	struct MaterialDescriptor
	{
		/// <summary>
		/// Are shadows enabled for this material?
		/// </summary>
		bool HasShadows = true;
		/// <summary>
		///	Extra data for the material that can be accessed by shaders and rendering passes.
		/// </summary>
		void* Extra = nullptr;
	};
}