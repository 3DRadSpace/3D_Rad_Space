#include "Game.h"

#ifdef __DIRECTXVER

Game::Game(HWND window)
{
	this->_stencilstate = nullptr;
	this->_resolution = Point(800, 600);
	this->hWindow = window;
	this->LostDeviceEvent = nullptr;

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
	else
	{
		this->_dc = false;
		this->_backbuffer_rendertarget = nullptr;
		return;
	}

	ID3D11Texture2D* _backbuffer_texture = nullptr;
	_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&_backbuffer_texture);
	if (FAILED(r) || _backbuffer_texture == nullptr) throw std::runtime_error("Failed to get the swap chain back buffer!");

	this->_backbuffer_rendertarget = nullptr;
	_gdev->CreateRenderTargetView(_backbuffer_texture, nullptr, &this->_backbuffer_rendertarget);
	_backbuffer_texture->Release();
}

Game::Game(HWND window, const Point &resolution)
{
	this->_stencilstate = nullptr;
	this->_resolution = resolution;
	this->hWindow = window;
	this->LostDeviceEvent = nullptr;

	DXGI_SWAP_CHAIN_DESC swChDesc;
	memset(&swChDesc, 0, sizeof(DXGI_SWAP_CHAIN_DESC));
	swChDesc.Windowed = true;

	DXGI_MODE_DESC modeDesc;
	memset(&modeDesc, 0, sizeof(DXGI_MODE_DESC));
	modeDesc.Width = resolution.X;
	modeDesc.Height = resolution.Y;
	modeDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_FLOAT;
	modeDesc.RefreshRate = { 60,1 };
	modeDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	modeDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_STRETCHED;

	swChDesc.BufferDesc = modeDesc;
	swChDesc.BufferCount = 2;
	swChDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swChDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swChDesc.SampleDesc.Count = 1;
	swChDesc.SampleDesc.Quality = 0;
	swChDesc.Flags = 0;
	swChDesc.OutputWindow = window;

#if _DEBUG
	HRESULT r = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &swChDesc, &_swapchain, &this->_gdev, nullptr, &this->_gcontext);
#else
	HRESULT r = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swChDesc, &_swapchain, &this->_gdev, nullptr, &this->_gcontext);
#endif

	if (SUCCEEDED(r)) this->_dc = true;
	else
	{
		this->_dc = false;
		this->_backbuffer_rendertarget = nullptr;
		return;
	}

	ID3D11Texture2D* _backbuffer_texture = nullptr;
	_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&_backbuffer_texture);
	if (FAILED(r) || _backbuffer_texture == nullptr) throw std::runtime_error("Failed to get the swap chain back buffer!");

	this->_backbuffer_rendertarget = nullptr;
	r = _gdev->CreateRenderTargetView(_backbuffer_texture, nullptr, &this->_backbuffer_rendertarget);
	if (FAILED(r))
	{
		throw std::runtime_error("Failed to extract the back buffer!");
	}

	_backbuffer_texture->Release();
}

ID3D11Device* Game::GetDevice()
{
	return _gdev;
}

ID3D11DeviceContext* Game::GetDeviceContext()
{
	return _gcontext;
}

IDXGISwapChain* Game::GetSwapChain()
{
	return _swapchain;
}

bool Game::IsDeviceCreated()
{
	return _dc;
}
ID3D11RenderTargetView* Game::GetRenderTargetBackBuffer()
{
	return _backbuffer_rendertarget;
}
Point Game::GetResolution()
{
	return this->_resolution;
}

void Game::SetTopology(PrimitiveTopology topology)
{
	D3D11_PRIMITIVE_TOPOLOGY set_topology;
	switch (topology)
	{
		case PrimitiveTopology::Points:
		{
			set_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
			break;
		}
		case PrimitiveTopology::Lines:
		{
			set_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINELIST;
			break;
		}
		case PrimitiveTopology::TriangleList:
		{
			set_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		}
		case PrimitiveTopology::TriangleStrip:
		{
			set_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
			break;
		}
		default:
		{
			set_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		}
	}

	this->_gcontext->IASetPrimitiveTopology(set_topology);
}

void Game::SetStencilState(StencilState* stencil)
{
	this->_stencilstate = stencil;
}

void Game::Clear(ColorShader clearcolor)
{
	this->_gcontext->ClearRenderTargetView(this->_backbuffer_rendertarget, (float*)&clearcolor);
	this->_gcontext->ClearDepthStencilView(this->_stencilstate->GetStencilView(), D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH | D3D11_CLEAR_FLAG::D3D11_CLEAR_STENCIL, 1.0f, 0);
	this->_gcontext->OMSetDepthStencilState(this->_stencilstate->GetStencilState(), 1);
	this->_gcontext->OMSetRenderTargets(1, &_backbuffer_rendertarget, this->_stencilstate->GetStencilView());
}

void Game::Present()
{
	HRESULT r = this->_swapchain->Present(1,0);
	if (r == NO_ERROR) return;
	if (r == DXGI_ERROR_DEVICE_RESET || r == DXGI_ERROR_DEVICE_REMOVED)
	{
		if (this->LostDeviceEvent == nullptr)
			throw std::runtime_error("Lost the graphics device.");
		else this->LostDeviceEvent();
	}
	else
		throw std::runtime_error("Unknown error when attepmting to render the scene.");
}

HWND Game::GetWindow()
{
	return this->hWindow;
}

Game::~Game()
{
	if(_backbuffer_rendertarget != nullptr) _backbuffer_rendertarget->Release();
	if(_gcontext != nullptr) _gcontext->Release();
	if(_swapchain != nullptr) _swapchain->Release();
	if(_gdev != nullptr) _gdev->Release();

	this->_backbuffer_rendertarget = nullptr;
	this->_gcontext = nullptr;
	this->_swapchain = nullptr;
	this->_gdev = nullptr;
}
#endif // __DIRECTXVER