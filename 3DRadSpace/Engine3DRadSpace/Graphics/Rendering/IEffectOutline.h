#pragma once
#include "IRenderingEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class DLLEXPORT IEffectOutline : public IRenderingEffect
	{
	public:
		Color OutlineColor;
		float OutlineWidth;
	};
}