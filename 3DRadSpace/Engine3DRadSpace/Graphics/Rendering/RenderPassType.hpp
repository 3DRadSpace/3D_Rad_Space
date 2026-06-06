#pragma once

namespace Engine3DRadSpace::Graphics::Rendering
{
	enum class RenderPassType : uint8_t
	{
		Hidden,
		Opaque,
		OpaqueNoShadow,
		Transparent,
		TransparentNoShadow,
		ShadowMap,
		DepthPrePass,
		Custom
	};
}