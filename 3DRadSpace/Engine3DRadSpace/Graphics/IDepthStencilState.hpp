#pragma once
#include "FaceOperation.hpp"
#include "IGPUResource.hpp"
#include "DepthWriteMask.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IDepthStencilState : public IGPUResource
	{
	protected:
		IDepthStencilState() = default;

		IDepthStencilState(const IDepthStencilState&) = delete;
		IDepthStencilState& operator=(const IDepthStencilState&) = delete;

		IDepthStencilState(IDepthStencilState&&) noexcept = default;
		IDepthStencilState& operator=(IDepthStencilState&&) noexcept = default;
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual unsigned int StencilRef() const noexcept = 0;

		/// <summary>
		/// Gets the stencil reference value.
		/// </summary>
		/// <returns>The stencil reference value.</returns>
		~IDepthStencilState() override = default;
	};
}