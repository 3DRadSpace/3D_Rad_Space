#pragma once
#include "IGPUMultiBuffer.hpp"
#include "../Math/UPoint.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents an cubemap made of 6 2D textures.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT ITextureCube : public IGPUMultiBuffer
	{
	protected:
		ITextureCube() = default;

		ITextureCube(const ITextureCube&) = delete;
		ITextureCube& operator=(const ITextureCube&) = delete;

		ITextureCube(ITextureCube&&) noexcept = default;
		ITextureCube& operator=(ITextureCube&&) noexcept = default;
	public:
		/// <summary>
		/// Returns the size of the cubemap texture in pixels as a UPoint, where X is the width and Y is the height.
		/// </summary>
		/// <returns>(Width(), Height())</returns>
		virtual Math::UPoint Size() const noexcept = 0;

		/// <summary>
		/// Gets the width of the cubemap texture in pixels.
		/// </summary>
		/// <returns>The width of the cubemap texture in pixels.</returns>
		virtual unsigned Width() const noexcept = 0;
		/// <summary>
		/// Gets the height of the cubemap texture in pixels.
		/// </summary>
		/// <returns>The height of the cubemap texture in pixels.</returns>
		virtual unsigned Height() const noexcept = 0;

		/// <summary>
		/// Gets an opaque handle to the underlying GPU resource view for the cubemap texture.
		/// </summary>
		/// <returns></returns>
		virtual void* GetViewHandle() const noexcept = 0;

		/// <summary>
		/// Creates a staging texture cube that can be used for CPU read/write operations.
		/// </summary>
		/// <returns>A unique pointer to the created staging texture cube.</returns>
		[[nodiscard]] virtual std::unique_ptr<ITextureCube> CreateStaging() = 0;

		virtual ~ITextureCube() override = default;
	};
}