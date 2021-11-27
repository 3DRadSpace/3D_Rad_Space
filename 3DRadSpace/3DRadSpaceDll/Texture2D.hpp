#pragma once
#include "Game.hpp"
#include "Globals.hpp"


#if __DIRECTXVER

#include <d3d11.h>

#pragma warning(push)
#pragma warning(disable: 26812)

#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Describes a 2D texture
	/// </summary>
	class Texture2D
	{
		ID3D11Texture2D* _texture;
		ID3D11Device* _device;
		ID3D11DeviceContext* _context;
		ID3D11ShaderResourceView* _shaderresourceview;
	public:
		/// <summary>
		/// Constructs a empty texture 
		/// </summary>
		/// <param name="g">Device handles</param>
		/// <param name="width">Texture width</param>
		/// <param name="height">Texture height</param>
		/// <param name="format">Texture color format</param>
		Texture2D(Game* g, int width, int height, DXGI_FORMAT format);
		/// <summary>
		/// Loads a texture from a file
		/// </summary>
		/// <param name="g">Device handles</param>
		/// <param name="path">Path to texture</param>
		Texture2D(Game* g, const std::wstring& path);
		/// <summary>
		/// Loads a texture from a file
		/// </summary>
		/// <param name="g">Device handles</param>
		/// <param name="path">Path to texture in UTF-16</param>
		Texture2D(Game* game, const std::string& path);

		/// <summary>
		/// Sets texture pixels
		/// </summary>
		/// <typeparam name="T">Color struct</typeparam>
		/// <param name="g">Device handles</param>
		/// <param name="data">Colour data</param>
		/// <param name="size">Size of the data</param>
		template<class T>
		Texture2D(Game* g, const T* data, size_t size);

		/// <summary>
		/// Sets texture pixels
		/// </summary>
		/// <typeparam name="T">Color struct</typeparam>	
		/// <param name="data">Colour data</param>
		/// <param name="size">Size of the data</param>
		template<class T> void SetData(T* data, size_t size);
		//template<class T> T* GetData(size_t &size_out);

		/// <summary>
		/// Returns a handle to the texture in the context of the current GAPI
		/// </summary>
		/// <returns></returns>
		ID3D11Texture2D* GetTexture2D();
		/// <summary>
		/// Returns a handle to the texture shader resource view
		/// </summary>
		/// <returns></returns>
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
}
#pragma warning(pop)
#endif