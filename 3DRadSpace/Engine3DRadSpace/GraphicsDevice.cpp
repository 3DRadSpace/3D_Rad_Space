#include "GraphicsDevice.hpp"
#include "Error.hpp"
#include "IShader.hpp"

using namespace Engine3DRadSpace::Logging;

Engine3DRadSpace::GraphicsDevice::GraphicsDevice(void* nativeWindowHandle, unsigned width, unsigned height):
	EnableVSync(true)
{
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
		this->_swapChain.GetAddressOf(),
		this->_device.GetAddressOf(),
		nullptr,
		this->_context.GetAddressOf());

	RaiseFatalErrorIfFailed(r, "D3D11CreateDeviceAndSwapChain failed!");

	r = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(_screenTexture.GetAddressOf()));
	RaiseFatalErrorIfFailed(r, "Failed to get the back buffer texture!");

	r = _device->CreateRenderTargetView(_screenTexture.Get(), nullptr, _mainRenderTarget.GetAddressOf());
	RaiseFatalErrorIfFailed(r, "Failed to create the main render target!");
	_screenTexture->Release();

}

void Engine3DRadSpace::GraphicsDevice::Clear(const Color& clearColor)
{
	_context->OMSetRenderTargets(1, _mainRenderTarget.GetAddressOf(), nullptr);

	float color[4] = { clearColor.R,clearColor.G,clearColor.B,clearColor.A };
	_context->ClearRenderTargetView(_mainRenderTarget.Get(), color);
}

void Engine3DRadSpace::GraphicsDevice::SetViewport(const Viewport& viewport)
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

void Engine3DRadSpace::GraphicsDevice::SetViewports(std::span<Viewport> viewports)
{
	_context->RSSetViewports((UINT)viewports.size(), reinterpret_cast<D3D11_VIEWPORT*>(viewports.begin()._Myptr));
}

void Engine3DRadSpace::GraphicsDevice::Present()
{
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
}

void Engine3DRadSpace::GraphicsDevice::SetShader(Engine3DRadSpace::Graphics::IShader *shader)
{
	ID3D11Buffer * ppConstantBuffers[14] = { nullptr };
	unsigned i = 0;
	for (; i < 14; i++)
	{
		ID3D11Buffer *constBuffer = shader->_constantBuffers[i].Get();
		if (constBuffer == nullptr) break;

		ppConstantBuffers[i] = constBuffer;
	}

	switch (shader->_type)
	{
		case Engine3DRadSpace::Graphics::ShaderType::VertexShader:
		{
			_context->VSSetConstantBuffers(0, i, ppConstantBuffers);
			_context->IASetInputLayout(shader->_inputLayout.Get());
			_context->VSSetShader(static_cast<ID3D11VertexShader *>(shader->_shader), nullptr, 0);
			break;
		}
		case Engine3DRadSpace::Graphics::ShaderType::HullShader:
		{
			_context->HSSetConstantBuffers(0, i, ppConstantBuffers);
			_context->HSSetShader(static_cast<ID3D11HullShader *>(shader->_shader), nullptr, 0);
			break;
		}
		case Engine3DRadSpace::Graphics::ShaderType::DomainShader:
		{
			_context->DSSetConstantBuffers(0, i, ppConstantBuffers);
			_context->DSSetShader(static_cast<ID3D11DomainShader *>(shader->_shader), nullptr, 0);
			break;
		}
		case Engine3DRadSpace::Graphics::ShaderType::GeometryShader:
		{
			_context->GSSetConstantBuffers(0, i, ppConstantBuffers);
			_context->GSSetShader(static_cast<ID3D11GeometryShader *>(shader->_shader), nullptr, 0);
			break;
		}
		case Engine3DRadSpace::Graphics::ShaderType::PixelShader:
		{
			_context->PSSetConstantBuffers(0, i, ppConstantBuffers);
			_context->PSSetShader(static_cast<ID3D11PixelShader *>(shader->_shader), nullptr, 0);
			break;
		}
		default:
			break;
	}
}

Engine3DRadSpace::GraphicsDevice::~GraphicsDevice()
{
}
