#pragma once
#include "IRenderingEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class DLLEXPORT IEffectFog : public IRenderingEffect
	{
	protected:
		IEffectFog() = default;

		IEffectFog(IEffectFog&) = delete;
		IEffectFog& operator=(IEffectFog&) = delete;

		IEffectFog(IEffectFog&&) = default;
		IEffectFog& operator=(IEffectFog&&) = default;
	public:
		Color FogColor;
		float FogBegin;
		float FogEnd;

		~IEffectFog() override = default;
	};
}