#include "FlipMode.hpp"
using namespace Engine3DRadSpace::Graphics;

FlipMode Engine3DRadSpace::Graphics::operator&(FlipMode a, FlipMode b)
{
    return static_cast<FlipMode>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

FlipMode DLLEXPORT Engine3DRadSpace::Graphics::operator|(FlipMode a, FlipMode b)
{
    return static_cast<FlipMode>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}
