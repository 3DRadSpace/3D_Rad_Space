#pragma once
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ITexture2D;

	class IDepthStencilBuffer : public IGPUResource
	{
	protected:
		IDepthStencilBuffer() = default;

		IDepthStencilBuffer(const IDepthStencilBuffer&) = delete;
		IDepthStencilBuffer& operator=(const IDepthStencilBuffer&) = delete;

		IDepthStencilBuffer(IDepthStencilBuffer&&) noexcept = default;
		IDepthStencilBuffer& operator=(IDepthStencilBuffer&&) noexcept = default;
	public:
		virtual void* GetDepthTextureHandle() const noexcept = 0;
		virtual ITexture2D* GetDepthTexture() const noexcept = 0;

		virtual std::unique_ptr<ITexture2D> CloneDepthTexture() = 0;

		~IDepthStencilBuffer() override = default;
	};
}