#pragma once
#include "../../Math/Color.hpp"
#include "../../Math/Vector3.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
    struct DirectionalLight
    {
        Math::Color LightColor;
        Math::Color AmbientColor;
        Math::Vector3 LightDirection;
        float Intensity;
    };
}