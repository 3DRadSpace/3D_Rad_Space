#pragma once
#include "../../Math/Matrix4x4.hpp"
#include "../../Math/Vector2.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	struct alignas(16) ShadowCBuffer
	{
		Math::Matrix4x4 matWorld; //World matrix
		Math::Matrix4x4 matLightViewProj; //Light view projection matrix
		Math::Vector2 ShadowOffset;
		float ShadowBias;
		float ShadowIntensity;
	};
}