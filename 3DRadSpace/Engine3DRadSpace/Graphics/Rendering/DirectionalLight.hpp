#pragma once
#include "../../Math/Color.hpp"
#include "../../Math/Vector3.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
    struct DirectionalLight
    {
        Math::Color LightColor;
        Math::Color AmbientColor;
        Math::Vector3 LightDirection = -Math::Vector3::UnitY();//Math::Vector3( std::numbers::inv_sqrt3, -std::numbers::inv_sqrt3, std::numbers::inv_sqrt3 );
        float Intensity = 0.5f;
    };
}