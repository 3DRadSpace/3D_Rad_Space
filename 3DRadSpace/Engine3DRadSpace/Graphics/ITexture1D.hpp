#pragma once
#include "IGPUMultiBuffer.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents a 1D texture resource.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT ITexture1D : public IGPUMultiBuffer
	{
	protected:
		ITexture1D() = default;

		ITexture1D(const ITexture1D&) = delete;
		ITexture1D& operator=(const ITexture1D&) = delete;

		ITexture1D(ITexture1D&&) noexcept = default;
		ITexture1D& operator=(ITexture1D&&) noexcept = default;
	public:
		/// <summary>
		/// Gets the number of texels in this 1D texture.
		/// </summary>
		/// <returns></returns>
		virtual size_t Length() const noexcept = 0;
		/// <summary>
		/// Gets the shader resource view handle for this 1D texture.
		/// </summary>
		/// <returns></returns>
		virtual void* GetViewHandle() const noexcept = 0;
		/// <summary>
		/// Creates a staging texture that can be used for CPU read/write operations.
		/// </summary>
		/// <returns>A unique pointer to the created staging texture.</returns>
		[[nodiscard]] virtual std::unique_ptr<ITexture1D> CreateStaging() = 0;
	
		virtual ~ITexture1D() override = default;
	};
}