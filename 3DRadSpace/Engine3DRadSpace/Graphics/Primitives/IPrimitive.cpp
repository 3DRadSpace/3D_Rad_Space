#include "IPrimitive.hpp"
#include "../IShaderCompiler.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;

IPrimitive::IPrimitive(IGraphicsDevice* device, std::nullptr_t nullShader) :
    _device(device),
    _shader(nullptr)
{
}

IPrimitive::IPrimitive(IGraphicsDevice* device) :
	_device(device),
    _shader(nullptr)
{
    constexpr const char* trivialShader = "Data\\Shaders\\PositionColor.hlsl";

    auto vsBlankShader = ShaderDescFile(
        trivialShader,
        "VS_Main",
        ShaderType::Vertex
    );

    auto psBlankShader = ShaderDescFile(
        trivialShader,
        "PS_Main",
        ShaderType::Fragment
    );

    std::array<ShaderDesc*, 2> blankShaderDesc =
    {
        &vsBlankShader,
        &psBlankShader
    };

    auto [blankEffect, result] = device->ShaderCompiler()->CompileEffect(blankShaderDesc);
    if (result.Succeded)
    {
        _shader = blankEffect;
    }
}

Math::Matrix4x4 IPrimitive::_mvp() const noexcept
{
	return Transform * View * Projection;
}

void IPrimitive::Draw3D()
{
    auto mvp = _mvp();

    _shader->SetAll();
    _shader->operator[](0)->SetData(0, &mvp, sizeof(mvp));

    auto cmd = _device->ImmediateContext();

    cmd->SetTopology(VertexTopology::TriangleList);
    cmd->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}