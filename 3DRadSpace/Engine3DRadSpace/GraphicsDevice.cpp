#include "GraphicsDevice.hpp"
#include "Error.hpp"

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
	_screenTexture.ReleaseAndGetAddressOf();

}

void Engine3DRadSpace::GraphicsDevice::Clear(const Color& clearColor) const
{
	_context->OMSetRenderTargets(1, _mainRenderTarget.GetAddressOf(), nullptr);

	float color[4] = { clearColor.R,clearColor.G,clearColor.B,clearColor.A };
	_context->ClearRenderTargetView(_mainRenderTarget.Get(), color);
}

void Engine3DRadSpace::GraphicsDevice::Present() const
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

Engine3DRadSpace::GraphicsDevice::~GraphicsDevice()
{
}
