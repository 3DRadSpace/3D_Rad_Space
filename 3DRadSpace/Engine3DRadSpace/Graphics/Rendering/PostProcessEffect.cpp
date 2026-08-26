#include "PostProcessEffect.hpp"
#include "../IGraphicsDevice.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../IShaderCompiler.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Rendering;

PostProcessEffect::PostProcessEffect(
	IGraphicsDevice* device,
	const ShaderDesc& effectDesc
) :
	_vertex(nullptr),
	_device(device),
	_backbuffer_copy(nullptr),
	_depthBuffer_copy(nullptr),
	_effect(nullptr)
{
	//Compile base vertex effect
	auto desc = ShaderDescFile(
		"Data\\Shaders\\PostProcessBase.hlsl",
		"PostProcessBase_Main",
		ShaderType::Vertex
	);

	auto vs = _device->ShaderCompiler()->Compile(&desc);
	if (vs.second.Succeded)
	{
		_vertex = vs.first;
	}

	//Compile given post process effect
	auto ps = _device->ShaderCompiler()->Compile(&effectDesc);
	if (ps.second.Succeded)
	{
		_effect = ps.first;
	}
}

void PostProcessEffect::Apply()
{	
	//create a full screen quad and apply the shader to it.
	auto cmd = _device->ImmediateContext();

	cmd->SetShader(_vertex);
	cmd->SetShader(_effect);

	if (!NotDepthAware)
	{
		std::array<ITexture2D*, 2> textures = { _backbuffer_copy, _depthBuffer_copy };
		SetTextures(textures);
	}
	else SetTexture(0, _backbuffer_copy);

	_vertex->SetShader();
	_effect->SetShader();
}

void PostProcessEffect::SetTexture(unsigned index, ITexture1D* texture)
{
	_effect->SetTexture(index, texture);
}

void PostProcessEffect::SetTextures(std::span<ITexture1D*> textures)
{
	_effect->SetTextures(textures);
}

void PostProcessEffect::SetTexture(unsigned index, ITexture2D* texture)
{
	_effect->SetTexture(index, texture);
}

void PostProcessEffect::SetTextures(std::span<ITexture2D*> textures)
{
	_effect->SetTextures(textures);
}

void PostProcessEffect::SetTexture(unsigned index, ITextureCube* texture)
{
	_effect->SetTexture(index, texture);
}

void PostProcessEffect::SetTextures(std::span<ITextureCube*> textures)
{
	_effect->SetTextures(textures);
}

void PostProcessEffect::SetSampler(unsigned index, ISamplerState* sampler)
{
	_effect->SetSampler(index, sampler);
}

void PostProcessEffect::SetData(unsigned index, const void* data, size_t size)
{
	_effect->SetData(index, data, size);
}

void PostProcessEffect::Draw()
{
	auto cmd = _device->ImmediateContext();

	cmd->SetTopology(VertexTopology::TriangleList);
	cmd->DrawVertexBuffer(_device->GetScreenQuad());
}

void* PostProcessEffect::GetHandle() const noexcept
{
	return _vertex->GetHandle();
}

IGraphicsDevice* PostProcessEffect::GetGraphicsDevice() const noexcept
{
	return _device;
}

std::vector<Reflection::IReflectedField*> PostProcessEffect::GetVariables() const
{
	return _effect->GetVariables();
}

void PostProcessEffect::Set(const std::string& name, const void* data, size_t dataSize)
{
	_effect->Set(name, data, dataSize);
}

std::string_view PostProcessEffect::GetEntryName() const noexcept
{
	return _effect->GetEntryName();
}

const char* PostProcessEffect::GetCompilationErrorsAndWarnings() const noexcept
{
	return _effect->GetCompilationErrorsAndWarnings();
}

void PostProcessEffect::SetShader()
{
	_effect->SetShader();
}