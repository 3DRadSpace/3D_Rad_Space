#include "GraphicsDevice.hpp"
#include "Error.hpp"
#include "IShader.hpp"
#include <cassert>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

using namespace Engine3DRadSpace::Logging;

Engine3DRadSpace::GraphicsDevice::GraphicsDevice(void* nativeWindowHandle, unsigned width, unsigned height) :
	EnableVSync(true),
	resoultion(width, height)
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
		&this->swapChain,
		&this->device,
		nullptr,
		&this->context
	);
	RaiseFatalErrorIfFailed(r, "D3D11CreateDeviceAndSwapChain failed!");

	r = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), static_cast<void**>(&screenTexture));
	RaiseFatalErrorIfFailed(r, "Failed to get the back buffer texture!");

	r = device->CreateRenderTargetView(screenTexture.Get(), nullptr, &mainRenderTarget);
	RaiseFatalErrorIfFailed(r, "Failed to create the main render target!");

	createDepthStencil();
	context->OMSetDepthStencilState(this->depthState.Get(), 1);
#endif
}

void Engine3DRadSpace::GraphicsDevice::createDepthStencil()
{
#ifdef WIN32
	createDepthTexture();

	D3D11_DEPTH_STENCIL_DESC dsDesc;

	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HRESULT r = device->CreateDepthStencilState(&dsDesc, &depthState);
	RaiseFatalErrorIfFailed(r, "Failed to create a depth stencil state with default settings");

	createDepthView();
#endif
}

void Engine3DRadSpace::GraphicsDevice::createDepthTexture()
{
#ifdef WIN32
	D3D11_TEXTURE2D_DESC desc{};
	desc.Format = DXGI_FORMAT_R32_TYPELESS;
	desc.ArraySize = 1;
	desc.Width = resoultion.X;
	desc.Height = resoultion.Y;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	HRESULT r = device->CreateTexture2D(&desc, nullptr, &depthTexture);
	RaiseFatalErrorIfFailed(r, "Failed to create the depth stencil texture!");
#endif
}

void Engine3DRadSpace::GraphicsDevice::createDepthView()
{
#ifdef WIN32
	D3D11_DEPTH_STENCIL_VIEW_DESC viewDesc{};
	viewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	viewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	HRESULT r = device->CreateDepthStencilView(this->depthTexture.Get(), &viewDesc, &this->depthView); //the & operator release the previous stencil view object
	RaiseFatalErrorIfFailed(r, "Failed to create a depth stencil view!");
#endif
}

void Engine3DRadSpace::GraphicsDevice::Clear(const Color& clearColor)
{
#ifdef _DX11
	context->OMSetRenderTargets(1, mainRenderTarget.GetAddressOf(), this->depthView.Get());

	float color[4] = { clearColor.R,clearColor.G,clearColor.B,clearColor.A };
	context->ClearRenderTargetView(mainRenderTarget.Get(), color);
	context->ClearDepthStencilView(depthView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0xFF);
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

	context->RSSetViewports(1, &vp);
#endif
}

void Engine3DRadSpace::GraphicsDevice::SetViewports(std::span<Viewport> viewports)
{
#ifdef _DX11
	context->RSSetViewports(static_cast<UINT>(viewports.size()), reinterpret_cast<D3D11_VIEWPORT*>(viewports.begin()._Myptr));
#endif // _DX11
}

void Engine3DRadSpace::GraphicsDevice::SetNewDepthStencil(const DepthStencilState& state)
{
	//create a description matching the state parameter.
	D3D11_DEPTH_STENCIL_DESC dsDesc;

	dsDesc.DepthEnable = state.EnableDepthCheck;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK(state.WriteMask); //REFACTORING-NOTE: don't use initialization, may prefer a switch-case.
	dsDesc.DepthFunc = D3D11_COMPARISON_FUNC(state.Function);

	dsDesc.StencilEnable = state.EnableStencilCheck;
	dsDesc.StencilReadMask = state.ReadMask;
	dsDesc.StencilWriteMask = state.WriteMask;

	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP(state.FrontFace.StencilFail);
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP(state.FrontFace.DepthFail);
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP(state.FrontFace.PassOp);
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_FUNC(state.FrontFace.Function);

	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP(state.BackFace.StencilFail);
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP(state.BackFace.DepthFail);
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP(state.BackFace.PassOp);
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC(state.BackFace.Function);

	HRESULT r = device->CreateDepthStencilState(&dsDesc, &depthState);
	RaiseFatalErrorIfFailed(r, "Failed to create a depth stencil state");

	//recreate depth view resource.
	createDepthView();
}

void Engine3DRadSpace::GraphicsDevice::DrawVertexBuffer(Engine3DRadSpace::Graphics::VertexBuffer* vertexBuffer, unsigned startSlot)
{
#ifdef _DX11
	UINT strides = 0;
	UINT offsets = 0;
	context->IASetVertexBuffers(startSlot, 1, vertexBuffer->buffer.GetAddressOf(), &strides, &offsets);
	context->Draw(UINT(vertexBuffer->numVerts), UINT(startSlot));
#endif
}
void Engine3DRadSpace::GraphicsDevice::DrawVertexBufferWithindices(Engine3DRadSpace::Graphics::VertexBuffer* vertexBuffer, Engine3DRadSpace::Graphics::IndexBuffer* indexBuffer)
{
#ifdef _DX11
	UINT strides = 0;
	UINT offsets = 0;
	context->IASetIndexBuffer(indexBuffer->indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, vertexBuffer->buffer.GetAddressOf(), &strides, &offsets);
	context->Draw(UINT(vertexBuffer->numVerts), 0u);
#endif
}
void Engine3DRadSpace::GraphicsDevice::Present()
{
#ifdef _DX11
	HRESULT r = swapChain->Present(EnableVSync ? 1 : 0, 0);
	if (SUCCEEDED(r)) return; //if Present call succeded, skip error reporting.

	if (r == DXGI_ERROR_DEVICE_RESET) RaiseFatalError(Error(r, "Graphics device reset"));
	if (r == DXGI_ERROR_DEVICE_REMOVED)
	{
		HRESULT reason = device->GetDeviceRemovedReason();
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

void Engine3DRadSpace::GraphicsDevice::SetShader(Engine3DRadSpace::Graphics::IShader *shader)
{
#ifdef _DX11
	const unsigned maxConstBuffers = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;

	ID3D11Buffer * ppConstantBuffers[maxConstBuffers] = { nullptr };
	unsigned i = 0;
	for (; i < maxConstBuffers; i++)
	{
		ID3D11Buffer *constBuffer = shader->constantBuffers[i].Get();
		if (constBuffer == nullptr) break;

		ppConstantBuffers[i] = constBuffer;
	}

	switch (shader->type)
	{
		case Engine3DRadSpace::Graphics::ShaderType::VertexShader:
		{
			context->VSSetConstantBuffers(0, i, ppConstantBuffers);
			context->IASetInputLayout(shader->inputLayout.Get());
			context->VSSetShader(static_cast<ID3D11VertexShader *>(shader->shader.Get()), nullptr, 0);
			break;
		}
		case Engine3DRadSpace::Graphics::ShaderType::HullShader:
		{
			context->HSSetConstantBuffers(0, i, ppConstantBuffers);
			context->HSSetShader(static_cast<ID3D11HullShader *>(shader->shader.Get()), nullptr, 0);
			break;
		}
		case Engine3DRadSpace::Graphics::ShaderType::DomainShader:
		{
			context->DSSetConstantBuffers(0, i, ppConstantBuffers);
			context->DSSetShader(static_cast<ID3D11DomainShader *>(shader->shader.Get()), nullptr, 0);
			break;
		}
		case Engine3DRadSpace::Graphics::ShaderType::GeometryShader:
		{
			context->GSSetConstantBuffers(0, i, ppConstantBuffers);
			context->GSSetShader(static_cast<ID3D11GeometryShader *>(shader->shader.Get()), nullptr, 0);
			break;
		}
		case Engine3DRadSpace::Graphics::ShaderType::PixelShader:
		{
			context->PSSetConstantBuffers(0, i, ppConstantBuffers);
			context->PSSetShader(static_cast<ID3D11PixelShader *>(shader->shader.Get()), nullptr, 0);
			break;
		}
		default:
			break;
	}
#endif
}

void Engine3DRadSpace::GraphicsDevice::SetTopology(Graphics::VertexTopology topology)
{
#ifdef _DX11
	context->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(topology));
#endif
}

void Engine3DRadSpace::GraphicsDevice::DrawAuto()
{
#ifdef _DX11
	this->context->DrawAuto();
#endif
}

void Engine3DRadSpace::GraphicsDevice::SetRasterizerState(const RasterizerState *state)
{
#ifdef _DX11
	context->RSSetState(state->rasterizerState.Get());
#endif
}

Engine3DRadSpace::Math::Point Engine3DRadSpace::GraphicsDevice::Resolution()
{
	return this->resoultion;
}

Engine3DRadSpace::GraphicsDevice::~GraphicsDevice()
{

}
