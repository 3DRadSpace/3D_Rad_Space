#include "GraphicsDevice.hpp"
#include "Logging/Exception.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/RenderTarget.hpp"
#include "Graphics/DepthStencilBuffer.hpp"

#ifdef  USING_DX11
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")

#include <ScreenGrab.h>
#include <wincodec.h>
#include <dxgidebug.h>
#include <dxgi.h>
#include <dxgi1_3.h>
#endif //  USING_DX11

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;

GraphicsDevice::GraphicsDevice(void* nativeWindowHandle, unsigned width, unsigned height) :
	EnableVSync(true),
	_resolution(width, height)
{
#ifdef USING_DX11
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
	if (FAILED(r)) throw Exception("D3D11CreateDeviceAndSwapChain failed!");

	r = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), static_cast<void**>(&_screenTexture));
	if (FAILED(r)) throw Exception("Failed to get the back buffer texture!");

	r = _device->CreateRenderTargetView(_screenTexture.Get(), nullptr, &_mainRenderTarget);
	if (FAILED(r)) throw Exception("Failed to create the main render target!");

	_stencilBuffer = std::make_unique<DepthStencilBuffer>(this);
	_stencilState = std::make_unique<DepthStencilState>(this);
	_blendState = std::make_unique<BlendState>(this);

	_context->OMSetDepthStencilState(_stencilState->_state.Get(), 1);

#if _DEBUG
	const char deviceName[] = "GraphicsDevice::_device";
	_device->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(deviceName) - 1, deviceName);

	const char contextName[] = "GraphicsDevice::_context";
	_context->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(contextName) - 1, contextName);
#endif
#endif
}

void GraphicsDevice::Clear(const Color& clearColor)
{
#ifdef USING_DX11
	_context->OMSetRenderTargets(1, _mainRenderTarget.GetAddressOf(), _stencilBuffer->_depthView.Get());

	float color[4] = { clearColor.R,clearColor.G,clearColor.B,clearColor.A };
	_context->ClearRenderTargetView(_mainRenderTarget.Get(), color);
	_context->ClearDepthStencilView(_stencilBuffer->_depthView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0xFF);
#endif
}

void GraphicsDevice::SetViewport()
{
#ifdef USING_DX11
	D3D11_VIEWPORT vp{};
	vp.TopLeftX = vp.TopLeftY = 0;
	vp.Width = static_cast<float>(_resolution.X);
	vp.Height = static_cast<float>(_resolution.Y);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	_context->RSSetViewports(1, &vp);
#endif
}

void GraphicsDevice::SetViewport(const Viewport& viewport)
{
#ifdef USING_DX11
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

void GraphicsDevice::SetViewports(std::span<Viewport> viewports)
{
#ifdef USING_DX11
	_context->RSSetViewports(static_cast<UINT>(viewports.size()), reinterpret_cast<D3D11_VIEWPORT*>(&viewports[0]));
#endif // USING_DX11
}

Viewport Engine3DRadSpace::GraphicsDevice::GetViewport()
{
#ifdef USING_DX11
	UINT numVp = 1;
	D3D11_VIEWPORT vp{};
	_context->RSGetViewports(&numVp, &vp);

	return Viewport(RectangleF(vp.TopLeftX, vp.TopLeftY, vp.Width, vp.Height), vp.MinDepth, vp.MaxDepth);
#endif
}

void GraphicsDevice::SetRenderTarget(RenderTarget*renderTarget)
{
#ifdef USING_DX11
	auto rt = renderTarget != nullptr ? renderTarget->_renderTarget.GetAddressOf() : _mainRenderTarget.GetAddressOf();
	_context->OMSetRenderTargets(1, rt, _stencilBuffer->_depthView.Get());
#endif
}

void GraphicsDevice::SetRenderTargetAndDepth(RenderTarget *renderTarget, DepthStencilBuffer*depthBuffer)
{
#ifdef USING_DX11
	auto depthviewBuffer = depthBuffer != nullptr ? depthBuffer->_depthView.Get() : _stencilBuffer->_depthView.Get();
	auto renderTargetView = renderTarget != nullptr ? renderTarget->_renderTarget.GetAddressOf() : _mainRenderTarget.GetAddressOf();
	_context->OMSetRenderTargets(1, renderTargetView, depthviewBuffer);
#endif
}

void GraphicsDevice::DrawVertexBuffer(VertexBuffer* vertexBuffer, unsigned startSlot)
{
#ifdef USING_DX11
	UINT strides = UINT(vertexBuffer->_structSize);
	UINT offsets = 0;
	_context->IASetVertexBuffers(startSlot, 1, vertexBuffer->_buffer.GetAddressOf(), &strides, &offsets);
	_context->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	_context->Draw(UINT(vertexBuffer->_numVerts), UINT(startSlot));
#endif
}
void GraphicsDevice::DrawVertexBufferWithindices(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer)
{
#ifdef USING_DX11
	UINT strides = UINT(vertexBuffer->_structSize);
	UINT offsets = 0;
	_context->IASetIndexBuffer(indexBuffer->_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	_context->IASetVertexBuffers(0, 1, vertexBuffer->_buffer.GetAddressOf(), &strides, &offsets);
	_context->DrawIndexed(UINT(indexBuffer->_numIndices),0u, 0u);
#endif
}
void GraphicsDevice::Present()
{
#ifdef USING_DX11
	HRESULT r = _swapChain->Present(EnableVSync ? 1 : 0, 0);
	if (SUCCEEDED(r)) return; //if Present call succeded, skip error reporting.

	if (r == DXGI_ERROR_DEVICE_RESET) throw Exception( "Graphics device reset");
	if (r == DXGI_ERROR_DEVICE_REMOVED)
	{
		HRESULT reason = _device->GetDeviceRemovedReason();
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
#endif // USING_DX11
}

void GraphicsDevice::SaveBackBufferToFile(const std::string &path)
{
#ifdef USING_DX11
	wchar_t wpath[_MAX_PATH]{};
	MultiByteToWideChar(CP_ACP, 0, path.c_str(), -1, wpath, _MAX_PATH);

	HRESULT r = DirectX::SaveWICTextureToFile(_context.Get(), _screenTexture.Get(), GUID_ContainerFormatPng, wpath, nullptr, nullptr, true);
	if(FAILED(r)) throw std::exception("Failed to save file!");
#endif
}

void GraphicsDevice::SaveBackBufferToFile(const std::wstring &path)
{
#ifdef USING_DX11
	HRESULT r = DirectX::SaveWICTextureToFile(_context.Get(), _screenTexture.Get(), GUID_ContainerFormatPng, path.c_str(), nullptr, nullptr, true);
	if(FAILED(r)) throw std::exception("Failed to save file!");
#endif
}

void GraphicsDevice::SetShader(IShader*shader)
{
	shader->SetShader();
}

void GraphicsDevice::SetTopology(VertexTopology topology)
{
#ifdef USING_DX11
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

void GraphicsDevice::DrawAuto()
{
#ifdef USING_DX11
	this->_context->DrawAuto();
#endif
}

void GraphicsDevice::SetRasterizerState(const RasterizerState *state)
{
#ifdef USING_DX11
	if (state != nullptr)
		_context->RSSetState(state->_rasterizerState.Get());
	else 
		_context->RSSetState(nullptr);
#endif
}

void GraphicsDevice::SetDepthStencilBuffer(DepthStencilBuffer *depthBuffer)
{
#ifdef USING_DX11
	ID3D11RenderTargetView *renderTargets[8];
	_context->OMGetRenderTargets(8, renderTargets, nullptr);
	
	_context->OMSetRenderTargets(8, renderTargets, depthBuffer->_depthView.Get());
#endif
}

void GraphicsDevice::SetDepthStencilState(DepthStencilState *depthState, unsigned ref = 0)
{
#ifdef USING_DX11
	if(depthState == nullptr)
		_context->OMSetDepthStencilState(nullptr, ref);
	else _context->OMSetDepthStencilState(depthState->_state.Get(), ref);
#endif
}

void GraphicsDevice::SetBlendState(BlendState*blendState,const Color &blendColor, unsigned sampleMask)
{
#if USING_DX11
	_context->OMSetBlendState(blendState->_blendState.Get(), reinterpret_cast<const float *>(&blendColor), sampleMask);
#endif
}

Math::Point GraphicsDevice::Resolution()
{
	return this->_resolution;
}

void GraphicsDevice::ResizeBackBuffer(const Math::Point &newResolution)
{
	_context->ClearState();
	HRESULT r = _swapChain->ResizeBuffers(0, newResolution.X, newResolution.Y, DXGI_FORMAT_UNKNOWN, 0);
	if(FAILED(r))
	{
		throw std::exception("Failed to resize buffers!");
	}
	else
	{
		r = _swapChain->GetBuffer(0, IID_PPV_ARGS(_screenTexture.GetAddressOf()));
		if(FAILED(r)) throw std::exception("Failed to get the back buffer texture!");
	}
}

void GraphicsDevice::ToggleFullScreen()
{
	_swapChain->SetFullscreenState(_fullscreen = !_fullscreen, nullptr);
}

GraphicsDevice::~GraphicsDevice()
{
#ifdef USING_DX11
	_context->ClearState();
//
//		UNCOMMENT THE COMMENT BLOCK BELOW IF THERE ARE DIRECTX OBJECTS LEAKING! 
//

/*
#if _DEBUG
	Microsoft::WRL::ComPtr<ID3D11Debug> debug;
	_device->QueryInterface<ID3D11Debug>(&debug);
	debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
#endif
*/
#endif
}
