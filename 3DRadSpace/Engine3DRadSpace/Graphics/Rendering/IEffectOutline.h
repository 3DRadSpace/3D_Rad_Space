#pragma once
#include "IRenderingEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class DLLEXPORT IEffectOutline : public IRenderingEffect
	{
	protected:
		IEffectOutline() = default;
	public:
		Color OutlineColor;
		float OutlineWidth;

		~IEffectOutline() override = default;
	};
}