#pragma once
#include "IGPUResource.hpp"
#include "RenderTargetBlendState.hpp"
#include "../Math/Color.hpp"

namespace Engine3DRadSpace::Graphics
{
    /// <summary>
    /// Represents blend state GPU handles.
    /// </summary>
    class E3DRSP_GRAPHICS_EXPORT IBlendState : public IGPUResource
    {
    protected:
		IBlendState() = default;

		IBlendState(const IBlendState&) = delete;
		IBlendState& operator=(const IBlendState&) = delete;

		IBlendState(IBlendState&&) noexcept = default;
		IBlendState& operator=(IBlendState&&) noexcept = default;
    public:
        /// <summary>
        /// Gets the blend factor.
        /// </summary>
        /// <returns>Blend factor.</returns>
        virtual Math::Color BlendFactor() const noexcept = 0;
        virtual unsigned int SampleMask() const noexcept = 0;

		~IBlendState() override = default;
    };
}
