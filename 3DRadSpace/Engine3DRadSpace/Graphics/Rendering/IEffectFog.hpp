#pragma once
#include "IRenderingEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class DLLEXPORT IEffectFog : public IRenderingEffect
	{
	protected:
		IEffectFog() = default;
	public:
		Color FogColor;
		float FogBegin;
		float FogEnd;
	};
}