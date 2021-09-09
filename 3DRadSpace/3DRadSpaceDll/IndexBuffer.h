#pragma once
#include "Globals.h"

#ifdef __DIRECTXVER

#include <d3d11.h>

class IndexBuffer
{
	unsigned int *_indexes;
	size_t _size;
	ID3D11Buffer* _indexbuffer;
	bool _createdbuffer;
public:
	IndexBuffer(unsigned int* indexes, size_t size);
	IndexBuffer(const std::vector<unsigned int> &initializer);

	void CreateIndexBuffer(ID3D11Device* device);
	ID3D11Buffer* GetCreatedBuffer();

	~IndexBuffer();
};
#endif
