#pragma once
#include "../../Math/Color.hpp"
#include "../../Math/Vector3.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
    struct DirectionalLight
    {
        Math::Color LightColor;
        Math::Color AmbientColor;
        Math::Vector3 LightDirection = Math::Vector3::Down();
        float Intensity = 0.5f;
    };
}