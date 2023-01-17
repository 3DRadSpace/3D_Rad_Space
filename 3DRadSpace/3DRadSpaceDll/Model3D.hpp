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
		/// The number of sub meshes this model has.
		/// </summary>
		size_t NumMeshes;

		/// <summary>
		/// Draws the 3D model.
		/// </summary>
		void Draw();

		void SetTransformation(Matrix& m);
		Matrix&& GetTransformation();

		~Model3D();
	};
}
#pragma warning(pop)