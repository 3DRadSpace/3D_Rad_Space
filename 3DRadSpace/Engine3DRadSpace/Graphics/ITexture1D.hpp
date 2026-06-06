#pragma once
#include "IGPUMultiBuffer.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT ITexture1D : public IGPUMultiBuffer
	{
	protected:
		ITexture1D() = default;

		ITexture1D(const ITexture1D&) = delete;
		ITexture1D& operator=(const ITexture1D&) = delete;

		ITexture1D(ITexture1D&&) noexcept = default;
		ITexture1D& operator=(ITexture1D&&) noexcept = default;
	public:
		virtual size_t Length() const noexcept = 0;
		virtual void* GetViewHandle() const noexcept = 0;
		[[nodiscard]] virtual std::unique_ptr<ITexture1D> CreateStaging() = 0;
	
		virtual ~ITexture1D() override = default;
	};
}