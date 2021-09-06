#include "Viewport.h"

#ifdef __DIRECTXVER

void Viewport::SetViewport(ID3D11DeviceContext* context)
{
	D3D11_VIEWPORT view;
	view.TopLeftX = (float)this->TopLeftX;
	view.TopLeftY = (float)this->TopLeftY;
	view.Width = (float)this->Width;
	view.Height = (float)this->Height;
	view.MinDepth = (float)this->MinDepth;
	view.MaxDepth = (float)this->MaxDepth;

	context->RSSetViewports(1, &view);
}

#endif