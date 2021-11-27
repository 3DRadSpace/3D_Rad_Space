#pragma once
#include "Mesh.hpp"

#pragma warning(push)
#pragma warning(disable: 26812)
#pragma warning(disable: 26495)

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents 3D model flags when importing.
	/// </summary>
	enum class VertexDeclDeterminantFlag
	{
		Null = 1 << 0,
		Position = 1 << 1,
		Normal = 1 << 2,
		TangentBitangent = 1 << 3,
		SingleUV = 1 << 4,
		MultipleUVs = 1 << 5,
		SingleVertexColor = 1 << 6,
		MultipleVertexColors = 1 << 7
	};

	/// <summary>
	/// Flag OR operator.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	inline VertexDeclDeterminantFlag operator |(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b);
	/// <summary>
	/// Flag OR operator
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	inline VertexDeclDeterminantFlag operator |=(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b);
	/// <summary>
	/// Flag AND operator
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	inline VertexDeclDeterminantFlag operator &(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b);

	/// <summary>
	/// Represents a 3D model
	/// </summary>
	class DLLEXPORT Model3D
	{
		ID3D11Device* device;
		ID3D11DeviceContext* context;

		bool _loaded;
		size_t NumTextures;
		Texture2D** Textures;
	public:
		/// <summary>
		/// Loads a 3D model from a file.
		/// </summary>
		/// <param name="game">Graphics handle</param>
		/// <param name="file">File path</param>
		Model3D(Game* game, const char* file);
		/// <summary>
		/// A array of sub meshes.
		/// </summary>
		MeshPart<void>** Meshes;
		/// <summary>
		/// Importing flags.
		/// </summary>
		VertexDeclDeterminantFlag* MeshFlags;
		/// <summary>
		/// The number of sub meshes this model has.
		/// </summary>
		size_t NumMeshes;

		/// <summary>
		/// Used internally when importing.
		/// </summary>
		/// <param name="flag"></param>
		/// <param name="comp"></param>
		/// <returns></returns>
		static bool CheckVertexDeclDeterminant(VertexDeclDeterminantFlag flag, VertexDeclDeterminantFlag comp);

		/// <summary>
		/// Draws the 3D model.
		/// </summary>
		void Draw();

		~Model3D();
	};
}
#pragma warning(pop)