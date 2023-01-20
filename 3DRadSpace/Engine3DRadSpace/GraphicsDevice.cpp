#include "GraphicsDevice.hpp"
#include "Error.hpp"

using namespace Engine3DRadSpace::Logging;

Engine3DRadSpace::GraphicsDevice::GraphicsDevice(void* nativeWindowHandle, unsigned width, unsigned height)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	swapChainDesc.BufferDesc.RefreshRate = { 1,60 }; // 1/60
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
	swapChainDesc.Windowed = false;
	swapChainDesc.SampleDesc = { 1, 0 }; //count, quality
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
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
}

Engine3DRadSpace::GraphicsDevice::~GraphicsDevice()
{
}
