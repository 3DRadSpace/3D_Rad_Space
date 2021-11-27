#pragma once
#include "Globals.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Texture2D.hpp"
#include "Shader.hpp"

#ifdef __DIRECTXVER

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a mesh. A mesh can be drawn or used in physics calculations.
	/// </summary>
	/// <typeparam name="T">A Vertex declaration. "void" can be used if not known</typeparam>
	template<class T>
	class MeshPart
	{
	public:
		/// <summary>
		/// Represents the vertex buffers
		/// </summary>
		VertexBuffer<T>* Verticies;
		/// <summary>
		/// Represents the index buffers
		/// </summary>
		IndexBuffer* Indexes;
		/// <summary>
		/// Represents the textures used for the models
		/// </summary>
		std::vector<Texture2D*> Textures;
		/// <summary>
		/// Represents the vertex shader used when drawing the mesh part.
		/// </summary>
		Shader* VertexShader;
		/// <summary>
		/// Represents the fragment shader used when drawing the mesh part
		/// </summary>
		Shader* PixelShader;

		/// <summary>
		/// Constructs an sub mesh the specified index and vertex buffers.
		/// </summary>
		/// <param name="vertexbuffer">Vertex buffer contaning the sub mesh geometry</param>
		/// <param name="indexbuffer">Index buffer representing the sub mesh order</param>
		MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer) : Verticies(vertexbuffer), Indexes(indexbuffer) {};
		/// <summary>
		/// Constructs an sub mesh from the specified index, vertex buffer and texture
		/// </summary>
		/// <param name="vertexbuffer">Vertex buffer contaning the sub mesh geometry</param>
		/// <param name="indexbuffer">Index buffer representing the sub mesh order</param>
		/// <param name="texture">A single color texture.</param>
		MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer, Texture2D* texture) :
			Verticies(vertexbuffer), Indexes(indexbuffer), Textures({ texture }), VertexShader(nullptr), PixelShader(nullptr) {};
		/// <summary>
		/// Constructs an sub mesh from the specified index, vertex buffer and multiple textures.
		/// Multiple textures can be used for an PBR shader, or any other specialized non-trivial shader.
		/// </summary>
		/// <param name="vertexbuffer">Vertex buffer contaning the sub mesh geometry</param>
		/// <param name="indexbuffer">Index buffer representing the sub mesh order</param>
		/// <param name="textures">A array of texture pointers.</param>
		/// <param name="numTextures">The number of textures.</param>
		MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer, Texture2D** textures, size_t numTextures);
		/// <summary>
		/// Constructs a submesh from the specified index, vertex buffer and multiple textures. Specialized shaders can be used.
		/// </summary>
		/// <param name="vertexbuffer">Vertex buffer contaning the sub mesh geometry</param>
		/// <param name="indexbuffer">Index buffer representing the sub mesh order</param>
		/// <param name="textures">A array of texture pointers.</param>
		/// <param name="numTextures">The number of textures.</param>
		/// <param name="vertexshader">Vertex shader used</param>
		/// <param name="pixelshader">Fragment/pixel shader used</param>
		MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer, Texture2D** textures, size_t numTextures, Shader* vertexshader, Shader* pixelshader);

		/// <summary>
		/// Sets the texture used by the sub mesh.
		/// </summary>
		/// <param name="texture"></param>
		void SetTexture(Texture2D* texture);
		/// <summary>
		/// Set the textures used by the submesh.
		/// </summary>
		/// <param name="textures"></param>
		/// <param name="NumTextures"></param>
		void SetTextures(Texture2D** textures, size_t NumTextures);

		/// <summary>
		/// Sets the shaders used by this mesh part.
		/// </summary>
		/// <param name="vertexshader">Vertex shader</param>
		/// <param name="fragmentshader">Fragment shader</param>
		void SetShaders(Shader* vertexshader, Shader* fragmentshader);

		/// <summary>
		/// Draws the mesh part.
		/// </summary>
		/// <param name="context">Device handle</param>
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
	inline MeshPart<T>::MeshPart(VertexBuffer<T>* vertexbuffer, IndexBuffer* indexbuffer, Texture2D** textures, size_t numTextures, Shader* vertexshader, Shader* pixelshader)
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
}
#endif