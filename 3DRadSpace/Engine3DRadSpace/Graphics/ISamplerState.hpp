#pragma once
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents a sampler state for texture sampling.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT ISamplerState : public IGPUResource	
	{
	protected:
		ISamplerState() = default;

		ISamplerState(const ISamplerState&) = delete;
		ISamplerState& operator=(const ISamplerState&) = delete;

		ISamplerState(ISamplerState&&) noexcept = default;
		ISamplerState& operator=(ISamplerState&&) noexcept = default;
	public:
		virtual ~ISamplerState() override = default;
	};
}	