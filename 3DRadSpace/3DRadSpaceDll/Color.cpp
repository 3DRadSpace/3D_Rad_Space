#include "Color.h"

Engine3DRadSpace::ColorShader Engine3DRadSpace::Color::Normalize()
{
    return { ((float)this->R) / 255, ((float)this->G) / 255,((float)this->B) / 255, ((float)this->A) / 255 };
}
