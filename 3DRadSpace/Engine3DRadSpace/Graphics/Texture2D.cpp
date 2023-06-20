#include "Texture2D.hpp"
#ifdef _DX11
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include <Windows.h>
#include <ScreenGrab.h>
#include <wincodec.h>
#endif // _DX11
#include "../Logging/Error.hpp"
#include "../Logging/ResourceLoadingError.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;

Texture2D::Texture2D(GraphicsDevice* device, const std::string &filename):
	_device(device),
	_width(0),
	_height(0)
{
#ifdef _DX11
	ID3D11Resource **resource = reinterpret_cast<ID3D11Resource **>(_texture.GetAddressOf());

	wchar_t path[_MAX_PATH]{};
	MultiByteToWideChar(CP_ACP, 0, filename.c_str(), (int)filename.length(), path, _MAX_PATH);

	HRESULT r = DirectX::CreateWICTextureFromFile(
		device->_device.Get(),
		device->_context.Get(),
		path,
		resource,
		_resourceView.GetAddressOf()
	);
	if (FAILED(r))
	{
		r = DirectX::CreateDDSTextureFromFile(
			device->_device.Get(),
			device->_context.Get(),
			path,
			resource,
			_resourceView.GetAddressOf()
			);
		return;
	}

	if(FAILED(r)) throw ResourceLoadingError(Tag<Texture2D>{}, filename, "Failed to create a texture!");

	_retrieveSize();
#endif
}

Engine3DRadSpace::Graphics::Texture2D::Texture2D(GraphicsDevice* device, const std::wstring &filename):
	_device(device)
{
#ifdef _DX11
	ID3D11Resource** resource = reinterpret_cast<ID3D11Resource**>(_texture.GetAddressOf());

	HRESULT r = DirectX::CreateWICTextureFromFile(
		device->_device.Get(),
		device->_context.Get(),
		filename.c_str(),
		resource,
		_resourceView.GetAddressOf()
	);
	if (FAILED(r))
	{
		r = DirectX::CreateDDSTextureFromFile(
			device->_device.Get(),
			device->_context.Get(),
			filename.c_str(),
			resource,
			_resourceView.GetAddressOf()
		);
	}

	if(FAILED(r))
	{
		char mbPath[_MAX_PATH]{};
		WideCharToMultiByte(CP_ACP, 0, filename.c_str(), filename.length(), mbPath, _MAX_PATH, nullptr, nullptr);
		throw ResourceLoadingError(Tag<Texture2D>{}, mbPath, "Failed to create a texture!");
	}

	_retrieveSize();
#endif
}

Texture2D::Texture2D(GraphicsDevice *device, std::span<Color> colors, unsigned x, unsigned y):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef _DX11
	D3D11_TEXTURE2D_DESC tDesc{};
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	tDesc.Height = y;
	tDesc.Width = x;
	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	Color **colorsCopy = new Color*[y];

	int k = 0;
	for (unsigned i = 0; i < y; i++)
	{
		colorsCopy[i] = new Color[x];
		for (unsigned j = 0; j < x; j++, k++)
		{
			colorsCopy[j][i] = colors[k];
		}
	}

	D3D11_SUBRESOURCE_DATA textureData{};
	textureData.pSysMem = new Color[x * y];
	textureData.SysMemPitch = sizeof(Color) * x;

	HRESULT r = device->_device->CreateTexture2D(&tDesc, nullptr, _texture.GetAddressOf());
	delete[] textureData.pSysMem;
	Logging::RaiseFatalErrorIfFailed(r, "Failed to initialize a 2D texture!");

	D3D11_SHADER_RESOURCE_VIEW_DESC resViewDesc{};
	resViewDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	resViewDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D10_1_SRV_DIMENSION_TEXTURE2D;

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to create a shader resource view!");
#endif
}

Texture2D::Texture2D(GraphicsDevice* device, void* colors, unsigned x, unsigned y):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef _DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = x;
	desc.Height = y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = colors;
	data.SysMemPitch = sizeof(Color) * x;

	HRESULT r = device->_device->CreateTexture2D(&desc, &data, _texture.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to initialize a 2D texture!");

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to create a shader resource view!");
#endif
}

Engine3DRadSpace::Graphics::Texture2D::Texture2D(GraphicsDevice* device,const uint8_t* imageBuffer, size_t size):
	_device(device)
{
#ifdef _DX11
	ID3D11Resource** resource = reinterpret_cast<ID3D11Resource**>(_texture.GetAddressOf());

	HRESULT r = DirectX::CreateWICTextureFromMemory(
		device->_device.Get(),
		device->_context.Get(),
		imageBuffer,
		size,
		resource,
		_resourceView.GetAddressOf()
	);
	if (FAILED(r))
	{
		r = DirectX::CreateWICTextureFromMemory(
			device->_device.Get(),
			device->_context.Get(),
			imageBuffer,
			size,
			resource,
			_resourceView.GetAddressOf()
		);
	}
	RaiseFatalErrorIfFailed(r, "Failed to create texture from memory!");

	_retrieveSize();
#endif
}

Engine3DRadSpace::Graphics::Texture2D::Texture2D(GraphicsDevice *device, unsigned x, unsigned y):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef _DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = x;
	desc.Height = y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _texture.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to initialize a 2D texture!");

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to create a shader resource view!");
#endif
}

void Engine3DRadSpace::Graphics::Texture2D::_retrieveSize()
{
	//Retrieve the image size
	D3D11_TEXTURE2D_DESC desc;
	_texture->GetDesc(&desc);

	_width = desc.Width;
	_height = desc.Height;
}

Engine3DRadSpace::Graphics::Texture2D::Texture2D(GraphicsDevice *device, unsigned x, unsigned y, bool bindRenderTarget):
	_device(device),
	_width(x),
	_height(y)
{
#ifdef _DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = x;
	desc.Height = y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | (bindRenderTarget ? D3D11_BIND_RENDER_TARGET : 0);
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _texture.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to initialize a 2D texture!");

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to create a shader resource view!");
#endif
}

Engine3DRadSpace::Graphics::Texture2D::Texture2D(GraphicsDevice *device, bool bindRenderTarget):
	_device(device)
{
#ifdef _DX11
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = device->_resolution.X;
	desc.Height = device->_resolution.Y;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | (bindRenderTarget ? D3D11_BIND_RENDER_TARGET : 0);
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	HRESULT r = device->_device->CreateTexture2D(&desc, nullptr, _texture.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to initialize a 2D texture!");

	r = device->_device->CreateShaderResourceView(_texture.Get(), nullptr, _resourceView.GetAddressOf());
	Logging::RaiseFatalErrorIfFailed(r, "Failed to create a shader resource view!");
#endif

	_width = device->_resolution.X;
	_height = device->_resolution.Y;
}

void Texture2D::SetColors(Color **colors, unsigned x, unsigned y)
{
#ifdef _DX11
	D3D11_MAPPED_SUBRESOURCE resource;
	
	HRESULT r = _device->_context->Map(_texture.Get(), 0, D3D11_MAP_WRITE, 0, &resource);
	if(FAILED(r)) throw std::exception("Failed to map a texture!");

	memcpy(resource.pData, colors, sizeof(Color) * x * y);
	_device->_context->Unmap(_texture.Get(), 0);
#endif
}

void Texture2D::SaveToFile(const std::string &path)
{
#ifdef _DX11
	wchar_t wpath[_MAX_PATH]{};
	MultiByteToWideChar(CP_ACP, 0, path.c_str(), -1, wpath, _MAX_PATH);

	HRESULT r = DirectX::SaveWICTextureToFile(_device->_context.Get(), _texture.Get(), GUID_ContainerFormatPng, wpath, nullptr, nullptr, true);
	if(FAILED(r)) throw std::exception("Failed to save file!");
#endif
}

unsigned Engine3DRadSpace::Graphics::Texture2D::Width()
{
	return _width;
}

unsigned Engine3DRadSpace::Graphics::Texture2D::Height()
{
	return _height;
}

