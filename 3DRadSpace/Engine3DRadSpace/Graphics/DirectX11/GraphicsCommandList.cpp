#include "GraphicsCommandList.hpp"
#include "GraphicsDevice.hpp"
#include "RenderTarget.hpp"
#include "../Logging/Exception.hpp"
#include "../Logging/Message.hpp"
#include "../IShader.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "IGPUResource.hpp"

#include <directxtk/ScreenGrab.h>
#include <wincodec.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;

GraphicsCommandList::GraphicsCommandList(GraphicsDevice* device) :
	_device(device),
	_context(device->_context.Get())
{
}

void GraphicsCommandList::Clear(const Color& clearColor)
{
	_context->OMSetRenderTargets(
		1,
		_device->_backbufferRT->_renderTarget.GetAddressOf(),
		_device->_stencilBuffer->_depthView.Get()
	);

	float color[4] = { clearColor.R,clearColor.G,clearColor.B,clearColor.A };
	_context->ClearRenderTargetView(_device->_backbufferRT->_renderTarget.Get(), color);

	_context->ClearDepthStencilView(
		_device->_stencilBuffer->_depthView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, 
		0x00
	);
}

void GraphicsCommandList::ClearRenderTarget(IRenderTarget* rt, const Color& clearColor)
{
	auto dxrt = static_cast<DirectX11::RenderTarget*>(rt);

	float color[4] = { clearColor.R,clearColor.G,clearColor.B,clearColor.A };
	_context->ClearRenderTargetView(dxrt->_renderTarget.Get(), color);
}

void GraphicsCommandList::ClearDepthBuffer(IDepthStencilBuffer* depth)
{
	auto dxdepth = static_cast<DepthStencilBuffer*>(depth);
	_context->ClearDepthStencilView(dxdepth->_depthView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0x00);
}

void GraphicsCommandList::SetViewport()
{
	auto r = _device->_resolution;

	D3D11_VIEWPORT vp{};
	vp.TopLeftX = vp.TopLeftY = 0;
	vp.Width = static_cast<float>(r.X);
	vp.Height = static_cast<float>(r.Y);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	_context->RSSetViewports(1, &vp);
}

void GraphicsCommandList::SetViewport(const Viewport& viewport)
{
	D3D11_VIEWPORT vp{};
	vp.TopLeftX = viewport.ScreenRectangle.X;
	vp.TopLeftY = viewport.ScreenRectangle.Y;
	vp.Width = viewport.ScreenRectangle.Width;
	vp.Height = viewport.ScreenRectangle.Height;

	vp.MinDepth = viewport.MinDepth;
	vp.MaxDepth = viewport.MaxDepth;

	_context->RSSetViewports(1, &vp);
}

void GraphicsCommandList::SetViewports(std::span<Viewport> viewports)
{
	_context->RSSetViewports(static_cast<UINT>(viewports.size()), reinterpret_cast<D3D11_VIEWPORT*>(&viewports[0]));
}

Viewport GraphicsCommandList::GetViewport()
{
	UINT numVp = 1;
	D3D11_VIEWPORT vp{};
	_context->RSGetViewports(&numVp, &vp);

	return Viewport(RectangleF(vp.TopLeftX, vp.TopLeftY, vp.Width, vp.Height), vp.MinDepth, vp.MaxDepth);
}

void GraphicsCommandList::SetRenderTarget(IRenderTarget* renderTarget)
{
	auto dxrt = static_cast<RenderTarget*>(renderTarget);
	auto rt = dxrt != nullptr ? dxrt->_renderTarget.GetAddressOf() : _device->_backbufferRT->_renderTarget.GetAddressOf();
	_context->OMSetRenderTargets(1, rt, _device->_stencilBuffer->_depthView.Get());
}

void GraphicsCommandList::UnbindRenderTargetAndDepth()
{
	ID3D11RenderTargetView* nullRTV = nullptr;
	_context->OMSetRenderTargets(1, &nullRTV, nullptr);
}

void GraphicsCommandList::UnbindDepthBuffer()
{
	std::array<ID3D11RenderTargetView*, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> rts;
	_context->OMGetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, &rts[0], nullptr);

	_context->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, &rts[0], nullptr);

	for (auto& rt : rts)
	{
		if (rt) rt->Release();
	}
}

void GraphicsCommandList::SetRenderTargetAndDepth(IRenderTarget* renderTarget, IDepthStencilBuffer* depthBuffer)
{
	auto dxrt = static_cast<RenderTarget*>(renderTarget);
	auto dxdepth = static_cast<DepthStencilBuffer*>(depthBuffer);

	auto depthviewBuffer = dxrt != nullptr ? dxdepth->_depthView.Get() : _device->_stencilBuffer->_depthView.Get();
	auto renderTargetView = dxrt != nullptr ? dxrt->_renderTarget.GetAddressOf() : _device->_backbufferRT->_renderTarget.GetAddressOf();
	_context->OMSetRenderTargets(1, renderTargetView, depthviewBuffer);
}

void GraphicsCommandList::SetRenderTargetAndDisableDepth(IRenderTarget* renderTarget)
{
	auto dxrt = static_cast<RenderTarget*>(renderTarget);
	auto renderTargetView = renderTarget != nullptr ? dxrt->_renderTarget.GetAddressOf() : _device->_backbufferRT->_renderTarget.GetAddressOf();
	_context->OMSetRenderTargets(1, renderTargetView, nullptr);
}

void GraphicsCommandList::DrawVertexBuffer(IVertexBuffer* vertexBuffer, unsigned startSlot)
{
	auto dxvb = static_cast<VertexBuffer*>(vertexBuffer);
	UINT strides = UINT(dxvb->_structSize);
	UINT offsets = 0;
	_context->IASetVertexBuffers(startSlot, 1, dxvb->_buffer.GetAddressOf(), &strides, &offsets);
	_context->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	_context->Draw(UINT(dxvb->_numVerts), UINT(startSlot));
}

void GraphicsCommandList::DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer)
{
	auto dxvb = static_cast<VertexBuffer*>(vertexBuffer);
	auto dxib = static_cast<IndexBuffer*>(indexBuffer);

	UINT strides = UINT(dxvb->_structSize);
	UINT offsets = 0;
	_context->IASetIndexBuffer(dxib->_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	_context->IASetVertexBuffers(0, 1, dxvb->_buffer.GetAddressOf(), &strides, &offsets);
	_context->DrawIndexed(UINT(dxib->_numIndices), 0u, 0u);
}

void GraphicsCommandList::DrawVertexBufferWithindices(IVertexBuffer* vertexBuffer, IIndexBuffer* indexBuffer, unsigned numIndices)
{
	auto dxvb = static_cast<VertexBuffer*>(vertexBuffer);
	auto dxib = static_cast<IndexBuffer*>(indexBuffer);

	UINT strides = UINT(dxvb->_structSize);
	UINT offsets = 0;
	_context->IASetIndexBuffer(dxib->_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	_context->IASetVertexBuffers(0, 1, dxvb->_buffer.GetAddressOf(), &strides, &offsets);
	_context->DrawIndexed(numIndices, 0u, 0u);
}

void GraphicsCommandList::Present()
{
	HRESULT r = _device->_swapChain->Present(_device->EnableVSync ? 1 : 0, 0);
	if (SUCCEEDED(r)) return; //if Present call succeded, skip error reporting.

	if (r == DXGI_ERROR_DEVICE_RESET) throw Exception("Graphics device reset");
	if (r == DXGI_ERROR_DEVICE_REMOVED)
	{
		HRESULT reason = _device->_device->GetDeviceRemovedReason();
		switch (reason)
		{
		case DXGI_ERROR_DEVICE_HUNG:
			throw Exception("Graphics device hung");
			break;
		case DXGI_ERROR_DEVICE_REMOVED:
			throw Exception("Graphics device removed");
			break;
		case DXGI_ERROR_DEVICE_RESET:
			throw Exception("Graphics device reset");
			break;
		case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
			throw Exception("Internal driver error!");
			break;
		case DXGI_ERROR_INVALID_CALL:
			throw Exception("Invalid call");
			break;
		default: break;
		}
	}

	if (FAILED(r)) throw Exception("Unknown error when presenting a frame");
}

void GraphicsCommandList::SaveBackBufferToFile(const std::filesystem::path& path)
{
	UnbindRenderTargetAndDepth();

	HRESULT r = DirectX::SaveWICTextureToFile(_context, _device->_backbufferRT->_texture.Get(), GUID_ContainerFormatPng, path.wstring().c_str(), nullptr, nullptr, true);
	if(FAILED(r)) throw std::exception("Failed to save file!");

	SetRenderTargetAndDepth(nullptr, nullptr);

	Logging::SetLastMessage(std::format("Saved backbuffer image to {}", path.string()));
}

void GraphicsCommandList::SetShader(IShader* shader)
{
	shader->SetShader();
}

void GraphicsCommandList::SetTopology(VertexTopology topology)
{
	D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	switch (topology)
	{
	case VertexTopology::PointList:
		t = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		break;
	case VertexTopology::LineList:
		t = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	case VertexTopology::LineStrip:
		t = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
		break;
	case VertexTopology::TriangleList:
		t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	case VertexTopology::LineList_Adj:
		t = D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ;
		break;
	case VertexTopology::LineStrip_Adj:
		t = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ;
		break;
	case VertexTopology::TriangleList_Adj:
		t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ;
		break;
	case VertexTopology::TriangleStrip_Adj:
		t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ;
		break;
	default:
		break;
	}

	_context->IASetPrimitiveTopology(t);
}

void GraphicsCommandList::DrawAuto()
{
	this->_context->DrawAuto();
}

void GraphicsCommandList::SetRasterizerState(const IRasterizerState* state)
{
	auto dxraster = static_cast<const RasterizerState*>(state);
	if (state != nullptr)
		_context->RSSetState(dxraster->_rasterizerState.Get());
	else
		_context->RSSetState(nullptr);
}

void GraphicsCommandList::SetDepthStencilBuffer(IDepthStencilBuffer* depthBuffer)
{
	ID3D11RenderTargetView* renderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	_context->OMGetRenderTargets(
		D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT,
		renderTargets,
		nullptr
	);

	auto dxdepth = static_cast<DepthStencilBuffer*>(depthBuffer);

	_context->OMSetRenderTargets(
		D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT,
		renderTargets,
		dxdepth != nullptr ? dxdepth->_depthView.Get() : nullptr
	);

	for (auto& rt : renderTargets)
	{
		if (rt) rt->Release();
	}
}

void GraphicsCommandList::SetDepthStencilState(IDepthStencilState* depthState, unsigned ref = 0)
{
	auto dxDepth = static_cast<DepthStencilState*>(depthState);
	if (depthState == nullptr)
		_context->OMSetDepthStencilState(nullptr, ref);
	else
	{
		_context->OMSetDepthStencilState(dxDepth->_state.Get(), ref);
		dxDepth->_stencilRef = ref;
	}
}

void GraphicsCommandList::SetBlendState(IBlendState* blendState, const Color& blendColor, unsigned sampleMask)
{
	auto dxBlendState = static_cast<BlendState*>(blendState);

	dxBlendState->_blendFactor = blendColor;
	dxBlendState->_sampleMask = sampleMask;
	_context->OMSetBlendState(
		dxBlendState->_blendState.Get(),
		reinterpret_cast<const float*>(&blendColor),
		sampleMask
	);
}

void GraphicsCommandList::ResizeBackBuffer(const Math::Point& newResolution)
{
	UnbindRenderTargetAndDepth();
	_device->_context->Flush();
	_device->_context->ClearState();
	_device->_backbufferRT.reset();

	HRESULT r = _device->_swapChain->ResizeBuffers(0, newResolution.X, newResolution.Y, DXGI_FORMAT_UNKNOWN, 0);
	if (FAILED(r))
	{
		throw std::exception("Failed to resize buffers!");
	}

	_device->_createBackBuffer();
}

void GraphicsCommandList::SetFullScreen(bool fullscreen)
{
	UnbindRenderTargetAndDepth();
	_device->_context->Flush();
	_device->_context->ClearState();
	_device->_backbufferRT.reset();

	HRESULT r = _device->_swapChain->SetFullscreenState(
		fullscreen,
		nullptr
	);
	if(FAILED(r)) throw Exception("SetFullScreen failed!");

	auto s = _device->_resolution;
	r = _device->_swapChain->ResizeBuffers(0, s.X, s.Y, DXGI_FORMAT_UNKNOWN, 0);
	if(FAILED(r)) throw Exception(std::format("ResizeBuffers failed: {:x}", r));

	_device->_createBackBuffer();

	_device->_fullscreen = fullscreen;
}

bool GraphicsCommandList::IsFullScreen() const
{
	return _device->_fullscreen;
}

void* GraphicsCommandList::GetHandle() const noexcept
{
	return _context;
}

IGraphicsDevice* GraphicsCommandList::GetGraphicsDevice() const noexcept
{
	return _device;
}

void GraphicsCommandList::Copy(IGPUBuffer* dest, IGPUBuffer* src)
{
	if (dest == nullptr || src == nullptr) return;

	auto rscDest = static_cast<ID3D11Resource*>(dest->GetHandle());
	auto rscSrc = static_cast<ID3D11Resource*>(src->GetHandle());

	_context->CopyResource(rscDest, rscSrc);
}

void GraphicsCommandList::Copy(IGPUMultiBuffer* dest, IGPUMultiBuffer* src)
{
	if(dest == nullptr || src == nullptr) return;

	auto rscDest = dynamic_cast<Texture2D*>(dest)->_texture.Get();
	auto rscSrc = dynamic_cast<Texture2D*>(src)->_texture.Get();

	_context->CopyResource(rscDest, rscSrc);
}