#pragma once
#include "IGPUResource.hpp"
#include "RasterizerFillMode.hpp"
#include "RasterizerCullMode.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents the rasterizer state.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT IRasterizerState : public IGPUResource
	{
	protected:
		IRasterizerState() = default;

		IRasterizerState(const IRasterizerState&) = delete;
		IRasterizerState& operator=(const IRasterizerState&) = delete;

		IRasterizerState(IRasterizerState&&) noexcept = default;
		IRasterizerState& operator=(IRasterizerState&&) noexcept = default;
	public:
		~IRasterizerState() override = default;
	};
}