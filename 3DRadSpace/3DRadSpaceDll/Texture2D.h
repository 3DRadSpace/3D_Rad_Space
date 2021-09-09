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

	template<class T> void SetData(T* data, size_t size);

	ID3D11Texture2D* GetTexture2D();
	ID3D11ShaderResourceView* GetShaderResourceView();

	~Texture2D();
};

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