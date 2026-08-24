#pragma once
#include "../IRenderTarget.hpp"
#include "Texture2D.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
	class GraphicsDevice;
	class E3DRSP_GRAPHICS_NULL_EXPORT RenderTarget final : public IRenderTarget, public Texture2D
	{
	public:
		RenderTarget(GraphicsDevice*device, PixelFormat format = PixelFormat::R16G16B16A16_Float);
		RenderTarget(GraphicsDevice* device, size_t x, size_t y, PixelFormat format = PixelFormat::R16G16B16A16_Float);

		RenderTarget(const RenderTarget&) = delete;
		RenderTarget& operator=(const RenderTarget&) = delete;

		RenderTarget(RenderTarget&&) noexcept = default;
		RenderTarget& operator=(RenderTarget&&) noexcept = default;

		void* RenderTargetHandle() const noexcept override;

		~RenderTarget() = default;

		friend class GraphicsDevice;
	};
}