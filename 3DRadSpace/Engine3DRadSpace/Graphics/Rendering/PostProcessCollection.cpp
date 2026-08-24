#include "PostProcessCollection.hpp"
#include "../IDepthStencilBuffer.hpp"
#include "../IGraphicsDevice.hpp"
#include "../IGraphicsCommandList.hpp"
#include "../ITexture2D.hpp"

using namespace Engine3DRadSpace::Graphics::Rendering;

PostProcessCollection::PostProcessCollection(IGraphicsDevice* device):
	_device(device),
	_backbuffer_cpy(device->CreateTexture2D(
		nullptr,
		device->Resolution().X,
		device->Resolution().Y,
		PixelFormat::R16G16B16A16_Float,
		BufferUsage::ReadOnlyGPU_WriteOnlyCPU
	)),
	_depthbuffer_cpy(device->GetDepthBuffer().CloneDepthTexture())
{
	//TODO - Get the backbuffer and depth buffer format from the device, don't hardcode them.
}

size_t PostProcessCollection::Length() const noexcept
{
	return _effects.size();
}

void PostProcessCollection::ApplyAll()
{
	for(auto& effect : _effects)
	{
		if(!effect->Enabled) continue;
		
		auto cmd = _device->ImmediateContext();

		cmd->UnbindRenderTargetAndDepth();

		cmd->Copy(_backbuffer_cpy.get(), _device->GetBackBufferTexture());
		cmd->Copy(_depthbuffer_cpy.get(), _device->GetDepthBuffer().GetDepthTexture());

		effect->_backbuffer_copy = _backbuffer_cpy.get();
		effect->_depthBuffer_copy = _depthbuffer_cpy.get();

		effect->Apply();
		cmd->SetRenderTargetAndDisableDepth(nullptr);
		effect->Draw();
	}
}

void PostProcessCollection::EnableAll()
{
	for(auto& effect : _effects)
	{
		effect->Enabled = true;
	}
}

void PostProcessCollection::DisableAll()
{
	for(auto& effect : _effects)
	{
		effect->Enabled = false;
	}
}