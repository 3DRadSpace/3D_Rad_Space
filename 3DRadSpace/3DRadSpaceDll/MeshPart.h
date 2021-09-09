#pragma once
#include "Globals.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture2D.h"
#include "Shader.h"

#ifdef __DIRECTXVER

template<class T>
class MeshPart
{
public:
	VertexBuffer<T> *Verticies;
	IndexBuffer *Indexes;
	std::vector<Texture2D*> Textures;
	Shader* VertexShader;
	Shader* PixelShader;

	MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer) : Verticies(vertexbuffer), Indexes(indexbuffer) {};
	MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer, Texture2D* texture) : 
		Verticies(vertexbuffer), Indexes(indexbuffer),Textures(texture) {};
	MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer, Texture2D** textures,size_t numTextures);
	MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer, Texture2D** textures,size_t numTextures, Shader* vertexshader, Shader* pixelshader);

	template<class S>
	void Draw(ID3D11DeviceContext* context, S constantBufferStruct);

};

template<class T>
inline MeshPart<T>::MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer, Texture2D** textures, size_t numTextures)
{
	Verticies = vertexbuffer;
	Indexes = indexbuffer;
	Textures = std::vector<Texture2D*>();

	for (int i = 0; i < numTextures; i++)
	{
		Textures[i] = textures[i];
	}
}

template<class T>
inline MeshPart<T>::MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer, Texture2D** textures,size_t numTextures, Shader* vertexshader, Shader* pixelshader)
{
	Verticies = vertexbuffer;
	Indexes = indexbuffer;
	Textures = std::vector<Texture2D*>();

	for (int i = 0; i < numTextures; i++)
	{
		Textures[i] = textures[i];
	}

	VertexShader = vertexshader;
	PixelShader = pixelshader;
}

template<class T>
template<class S>
inline void MeshPart<T>::Draw(ID3D11DeviceContext* context,S constantBufferStruct)
{
	//...
}

#endif