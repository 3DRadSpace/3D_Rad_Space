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
		Verticies(vertexbuffer), Indexes(indexbuffer), Textures({ texture }),VertexShader(nullptr),PixelShader(nullptr) {};
	MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer, Texture2D** textures,size_t numTextures);
	MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer, Texture2D** textures,size_t numTextures, Shader* vertexshader, Shader* pixelshader);

	void SetTexture(Texture2D* texture);
	void SetTextures(Texture2D** textures, size_t NumTextures);

	void SetShaders(Shader* vertexshader, Shader* fragmentshader);

	void Draw(ID3D11DeviceContext* context);

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
inline void MeshPart<T>::SetTexture(Texture2D* texture)
{
	Textures[0] = texture;
}

template<class T>
inline void MeshPart<T>::SetTextures(Texture2D** textures, size_t NumTextures)
{
	unsigned j = 0;
	for (unsigned i = 0; i < NumTextures; i++)
	{
		this->Textures[i] = textures[i];
	}
}

template<class T>
inline void MeshPart<T>::SetShaders(Shader* vertexshader, Shader* fragmentshader)
{
	this->VertexShader = vertexshader;
	this->PixelShader = fragmentshader;
}

template<class T>
inline void MeshPart<T>::Draw(ID3D11DeviceContext* context)
{
	this->VertexShader->SetShader(context);
	this->PixelShader->SetShader(context);
	this->Verticies->Draw(context);
}

#endif