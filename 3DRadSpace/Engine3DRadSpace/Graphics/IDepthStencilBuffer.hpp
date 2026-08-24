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
		/// <summary>
		/// Gets the depth texture handle.
		/// </summary>
		virtual void* GetDepthTextureHandle() const noexcept = 0;
		/// <summary>
		///	Gets the depth texture instance used by this instance.
		/// </summary>
		/// <returns>The depth texture instance.</returns>
		virtual ITexture2D* GetDepthTexture() const noexcept = 0;

		/// <summary>
		/// Deep clones this instance.
		/// </summary>
		/// <returns>A unique pointer to the cloned depth texture.</returns>
		virtual std::unique_ptr<ITexture2D> CloneDepthTexture() = 0;

		~IDepthStencilBuffer() override = default;
	};
}