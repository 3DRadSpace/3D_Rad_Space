#pragma once
#if __DIRECTXVER
#include <d3d11.h>
#endif
#include "Game.h"
#include "Globals.h"

#if __DIRECTXVER
class Texture2D
{
	ID3D11Texture2D* _texture;
	ID3D11Device* _device;
	ID3D11DeviceContext* _context;
public:
	Texture2D(Game *g,int width, int height, DXGI_FORMAT format);
	Texture2D(std::string path);

	template<class T> T* GetData(size_t &size);
	template<class T> void SetData(T* data, size_t size);

	~Texture2D();
};
#endif