#pragma once
#include "Game.h"
#include "Globals.h"


#if __DIRECTXVER

#include <d3d11.h>

#pragma warning(push)
#pragma warning(disable: 26812)

#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

class Texture2D
{
	ID3D11Texture2D* _texture;
	ID3D11Device* _device;
	ID3D11DeviceContext* _context;
	ID3D11ShaderResourceView* _shaderresourceview;
public:
	Texture2D(Game *g,int width, int height, DXGI_FORMAT format);
	Texture2D(Game *g, const std::wstring &path);
	Texture2D(Game* game, const std::string &path);

	template<class T>
	Texture2D(Game* g, const T* data, size_t size);

	template<class T> void SetData(T* data, size_t size);
	//template<class T> T* GetData(size_t &size_out);

	ID3D11Texture2D* GetTexture2D();
	ID3D11ShaderResourceView* GetShaderResourceView();

	~Texture2D();
};

template<class T>
inline Texture2D::Texture2D(Game* g, const T* data, size_t size)
{
	_texture = nullptr;
	_shaderresourceview = nullptr;

	_context = g->GetDeviceContext();
	_device = g->GetDevice();

	HRESULT r = DirectX::CreateWICTextureFromMemory(this->_device, (const uint8_t*)data, sizeof(T), (ID3D11Resource**)&this->_texture, &this->_shaderresourceview);
	if (FAILED(r))
	{
		r = DirectX::CreateDDSTextureFromMemory(this->_device, (const uint8_t*)data, sizeof(T), (ID3D11Resource**)&this->_texture, &this->_shaderresourceview);
		if (FAILED(r))
		{
			throw ResourceCreationException("Failed to create a texture from memory!", typeid(ID3D11Texture2D));
		}
	}
}

template<class T>
inline void Texture2D::SetData(T* data, size_t size)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	_context->Map(this->_texture, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	memcpy(mappedSubresource.pData, data, size);
	_context->Unmap(this->_texture, 0);
}

#pragma warning(pop)
#endif