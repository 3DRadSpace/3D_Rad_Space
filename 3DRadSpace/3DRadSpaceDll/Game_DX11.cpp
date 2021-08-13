#include "Game_DX11.h"

RS_DX11::Game::Game(HWND window)
{
	DXGI_SWAP_CHAIN_DESC swChDesc;
	memset(&swChDesc, 0, sizeof(DXGI_SWAP_CHAIN_DESC));
	swChDesc.Windowed = true;

	DXGI_MODE_DESC modeDesc;
	memset(&modeDesc, 0, sizeof(DXGI_MODE_DESC));
	modeDesc.Width = 800;
	modeDesc.Height = 600;
	modeDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_FLOAT;
	modeDesc.RefreshRate = { 60,1 };
	modeDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	modeDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_STRETCHED;

	swChDesc.BufferDesc = modeDesc;
	swChDesc.BufferCount = 2;
	swChDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swChDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swChDesc.SampleDesc = {1,0};
	swChDesc.Flags = 0;
	swChDesc.OutputWindow = window;

	HRESULT r = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &swChDesc, &_swapchain, &this->_gdev, nullptr, &this->_gcontext);

	if (SUCCEEDED(r)) this->_dc = true;
	else this->_dc = false;
}

ID3D11Device* RS_DX11::Game::GetDevice()
{
	return _gdev;
}

ID3D11DeviceContext* RS_DX11::Game::GetDeviceContext()
{
	return _gcontext;
}

IDXGISwapChain* RS_DX11::Game::GetSwapChain()
{
	return _swapchain;
}

bool RS_DX11::Game::IsDeviceCreated()
{
	return _dc;
}
