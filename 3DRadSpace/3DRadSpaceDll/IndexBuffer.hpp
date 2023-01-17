#pragma once
#include "Globals.hpp"

#ifdef __DIRECTXVER

#include <d3d11.h>

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents an buffer that tells the order of the verticies in a vertex buffer.
	/// </summary>
	class IndexBuffer
	{
		unsigned * _indexes;
		size_t _size;
		ID3D11Buffer* _indexbuffer;
		bool _createdbuffer;
	public:
		/// <summary>
		/// Constructs a index buffer from a given array allocated with operator new[].
		/// </summary>
		/// <param name="indexes">A array of indexes.</param>
		/// <param name="size">The size of the array</param>
		IndexBuffer(unsigned int* indexes, size_t size);
		/// <summary>
		/// Constructs a index buffer from a given std::vector or std::initializer_list.
		/// </summary>
		/// <param name="initializer">Given index values</param>
		explicit IndexBuffer(const std::vector<unsigned int>& initializer);
		/// <summary>
		/// Creates the infex buffer in the GPU
		/// </summary>
		/// <param name="device"></param>
		void CreateIndexBuffer(ID3D11Device* device);

		void SetIndexBuffer(ID3D11DeviceContext* context);
		/// <summary>
		/// Returns a handle of the index buffer that can be used by the graphics device handles
		/// </summary>
		/// <returns></returns>
		ID3D11Buffer* GetCreatedBuffer();

		~IndexBuffer();
	};
}
#endif
