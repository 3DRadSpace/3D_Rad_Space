#include "IShaderCompiler.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

IShaderCompiler::IShaderCompiler() : _manager(std::make_unique<EffectManager>())
{
}
