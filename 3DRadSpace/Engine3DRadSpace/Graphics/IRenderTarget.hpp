#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Graphics
{
	class E3DRSP_GRAPHICS_EXPORT IRenderTarget
	{
	protected:
		IRenderTarget() = default;

		IRenderTarget(const IRenderTarget&) = delete;
		IRenderTarget& operator=(const IRenderTarget&) = delete;

		IRenderTarget(IRenderTarget&&) noexcept = default;
		IRenderTarget& operator=(IRenderTarget&&) noexcept = default;
	public:
		virtual void* RenderTargetHandle() const noexcept = 0;
		virtual ~IRenderTarget() = default;
	};
}