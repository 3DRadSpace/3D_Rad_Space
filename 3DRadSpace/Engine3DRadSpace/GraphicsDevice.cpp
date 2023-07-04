#include "GraphicsDevice.hpp"
#include "Logging/Error.hpp"
//include shader types

#include <cassert>
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/RenderTarget.hpp"
#include "Graphics/DepthStencilBuffer.hpp"

#ifdef  _DX11
#pragma comment(lib,"d3d11.lib")
#endif //  _DX11
#include <ScreenGrab.h>
#include <wincodec.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

Engine3DRadSpace::GraphicsDevice::GraphicsDevice(void* nativeWindowHandle, unsigned width, unsigned height) :
	EnableVSync(true),
	_resolution(width, height)
{
#ifdef _DX11
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	swapChainDesc.BufferDesc.RefreshRate = { 1,60 }; // 1/60
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc = { 1, 0 }; //count, quality
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = static_cast<HWND>(nativeWindowHandle);
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

#if _DEBUG
	UINT flags = D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT flags = 0;
#endif

	HRESULT r = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		flags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&_swapChain,
		&_device,
		nullptr,
		&_context
	);
	RaiseFatalErrorIfFailed(r, "D3D11CreateDeviceAndSwapChain failed!");

	r = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), static_cast<void**>(&_screenTexture));
	RaiseFatalErrorIfFailed(r, "Failed to get the back buffer texture!");

	r = _device->CreateRenderTargetView(_screenTexture.Get(), nullptr, &_mainRenderTarget);
	RaiseFatalErrorIfFailed(r, "Failed to create the main render target!");

	_stencilBuffer = std::make_unique<DepthStencilBuffer>(this);
	_stencilState = std::make_unique<DepthStencilState>(this);
	_blendState = std::make_unique<BlendState>(this);

	_context->OMSetDepthStencilState(_stencilState->_state.Get(), 1);

	r = CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
	RaiseFatalErrorIfFailed(r, "Failed to initialize COM!");
#endif
}

void Engine3DRadSpace::GraphicsDevice::Clear(const Color& clearColor)
{
#ifdef _DX11
	_context->OMSetRenderTargets(1, _mainRenderTarget.GetAddressOf(), _stencilBuffer->_depthView.Get());

	float color[4] = { clearColor.R,clearColor.G,clearColor.B,clearColor.A };
	_context->ClearRenderTargetView(_mainRenderTarget.Get(), color);
	_context->ClearDepthStencilView(_stencilBuffer->_depthView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0xFF);
#endif
}

void Engine3DRadSpace::GraphicsDevice::SetViewport(const Viewport& viewport)
{
#ifdef _DX11
	D3D11_VIEWPORT vp{};
	vp.TopLeftX = viewport.ScreenRectangle.X;
	vp.TopLeftY = viewport.ScreenRectangle.Y;
	vp.Width = viewport.ScreenRectangle.Width;
	vp.Height = viewport.ScreenRectangle.Height;

	vp.MinDepth = viewport.MinDepth;
	vp.MaxDepth = viewport.MaxDepth;

	_context->RSSetViewports(1, &vp);
#endif
}

void Engine3DRadSpace::GraphicsDevice::SetViewports(std::span<Viewport> viewports)
{
#ifdef _DX11
	_context->RSSetViewports(static_cast<UINT>(viewports.size()), reinterpret_cast<D3D11_VIEWPORT*>(&viewports[0]));
#endif // _DX11
}

void Engine3DRadSpace::GraphicsDevice::SetRenderTarget(Graphics::RenderTarget *renderTarget)
{
#ifdef _DX11
	auto rt = renderTarget != nullptr ? renderTarget->_renderTarget.GetAddressOf() : _mainRenderTarget.GetAddressOf();
	_context->OMSetRenderTargets(1, rt, _stencilBuffer->_depthView.Get());
#endif
}

void Engine3DRadSpace::GraphicsDevice::SetRenderTargetAndDepth(Graphics::RenderTarget *renderTarget, Graphics::DepthStencilBuffer *depthBuffer)
{
#ifdef _DX11
	auto depthviewBuffer = depthBuffer != nullptr ? depthBuffer->_depthView.Get() : _stencilBuffer->_depthView.Get();
	auto renderTargetView = renderTarget != nullptr ? renderTarget->_renderTarget.GetAddressOf() : _mainRenderTarget.GetAddressOf();
	_context->OMSetRenderTargets(1, renderTargetView, depthviewBuffer);
#endif
}

void Engine3DRadSpace::GraphicsDevice::DrawVertexBuffer(Engine3DRadSpace::Graphics::VertexBuffer* vertexBuffer, unsigned startSlot)
{
#ifdef _DX11
	UINT strides = UINT(vertexBuffer->_structSize);
	UINT offsets = 0;
	_context->IASetVertexBuffers(startSlot, 1, vertexBuffer->_buffer.GetAddressOf(), &strides, &offsets);
	_context->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	_context->Draw(UINT(vertexBuffer->_numVerts), UINT(startSlot));
#endif
}
void Engine3DRadSpace::GraphicsDevice::DrawVertexBufferWithindices(Engine3DRadSpace::Graphics::VertexBuffer* vertexBuffer, Engine3DRadSpace::Graphics::IndexBuffer* indexBuffer)
{
#ifdef _DX11
	UINT strides = UINT(vertexBuffer->_structSize);
	UINT offsets = 0;
	_context->IASetIndexBuffer(indexBuffer->_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	_context->IASetVertexBuffers(0, 1, vertexBuffer->_buffer.GetAddressOf(), &strides, &offsets);
	_context->DrawIndexed(UINT(indexBuffer->_numIndices),0u, 0u);
#endif
}
void Engine3DRadSpace::GraphicsDevice::Present()
{
#ifdef _DX11
	HRESULT r = _swapChain->Present(EnableVSync ? 1 : 0, 0);
	if (SUCCEEDED(r)) return; //if Present call succeded, skip error reporting.

	if (r == DXGI_ERROR_DEVICE_RESET) RaiseFatalError(Error(r, "Graphics device reset"));
	if (r == DXGI_ERROR_DEVICE_REMOVED)
	{
		HRESULT reason = _device->GetDeviceRemovedReason();
		switch (reason)
		{
			case DXGI_ERROR_DEVICE_HUNG:
				RaiseFatalError(Error(reason, "Graphics device hung"));
				break;
			case DXGI_ERROR_DEVICE_REMOVED:
				RaiseFatalError(Error(reason, "Graphics device removed"));
				break;
			case DXGI_ERROR_DEVICE_RESET:
				RaiseFatalError(Error(reason, "Graphics device reset"));
				break;
			case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
				RaiseFatalError(Error(reason, "Internal driver error!"));
				break;
			case DXGI_ERROR_INVALID_CALL:
				RaiseFatalError(Error(reason, "Invalid call"));
				break;
			default: break;
		}
	}
	
	RaiseFatalErrorIfFailed(r, "Unknown error when presenting a frame", this);
#endif // _DX11
}

void Engine3DRadSpace::GraphicsDevice::SaveBackBufferToFile(const std::string &path)
{
#ifdef _DX11
	wchar_t wpath[_MAX_PATH]{};
	MultiByteToWideChar(CP_ACP, 0, path.c_str(), -1, wpath, _MAX_PATH);

	HRESULT r = DirectX::SaveWICTextureToFile(_context.Get(), _screenTexture.Get(), GUID_ContainerFormatPng, wpath, nullptr, nullptr, true);
	if(FAILED(r)) throw std::exception("Failed to save file!");
#endif
}

void Engine3DRadSpace::GraphicsDevice::SaveBackBufferToFile(const std::wstring &path)
{
#ifdef _DX11
	HRESULT r = DirectX::SaveWICTextureToFile(_context.Get(), _screenTexture.Get(), GUID_ContainerFormatPng, path.c_str(), nullptr, nullptr, true);
	if(FAILED(r)) throw std::exception("Failed to save file!");
#endif
}

void Engine3DRadSpace::GraphicsDevice::SetShader(Engine3DRadSpace::Graphics::IShader *shader)
{
	shader->SetShader();
}

void Engine3DRadSpace::GraphicsDevice::SetTopology(Graphics::VertexTopology topology)
{
#ifdef _DX11
	D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	switch(topology)
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
#endif
}

void Engine3DRadSpace::GraphicsDevice::DrawAuto()
{
#ifdef _DX11
	this->_context->DrawAuto();
#endif
}

void Engine3DRadSpace::GraphicsDevice::SetRasterizerState(const RasterizerState *state)
{
#ifdef _DX11
	_context->RSSetState(state->_rasterizerState.Get());
#endif
}

void Engine3DRadSpace::GraphicsDevice::SetDepthStencilBuffer(DepthStencilBuffer *depthBuffer)
{
#ifdef _DX11
	ID3D11RenderTargetView *renderTargets[16];
	_context->OMGetRenderTargets(16, renderTargets, nullptr);
	
	_context->OMSetRenderTargets(16, renderTargets, depthBuffer->_depthView.Get());
#endif
}

void Engine3DRadSpace::GraphicsDevice::SetDepthStencilState(DepthStencilState *depthState, unsigned ref = 0)
{
#ifdef _DX11
	if(depthState == nullptr)
		_context->OMSetDepthStencilState(nullptr, ref);
	else _context->OMSetDepthStencilState(depthState->_state.Get(), ref);
#endif
}

void Engine3DRadSpace::GraphicsDevice::SetBlendState(Graphics::BlendState *blendState,const Color &blendColor, unsigned sampleMask)
{
#if _DX11
	_context->OMSetBlendState(blendState->_blendState.Get(), reinterpret_cast<const float *>(&blendColor), sampleMask);
#endif
}

Engine3DRadSpace::Math::Point Engine3DRadSpace::GraphicsDevice::Resolution()
{
	return this->_resolution;
}

Engine3DRadSpace::GraphicsDevice::~GraphicsDevice()
{
#ifdef _DX11
//
//		UNCOMMENT THE COMMENT BLOCK BELOW IF THERE ARE DIRECTX OBJECTS LEAKING! 
//

/*
#if _DEBUG
	Microsoft::WRL::ComPtr<ID3D11Debug> debug;
	device->QueryInterface<ID3D11Debug>(&debug);
	debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
#endif
*/
	CoUninitialize();
#endif
}
