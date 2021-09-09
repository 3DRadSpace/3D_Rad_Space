#pragma once
#include "Mesh.h"

#pragma warning(push)
#pragma warning(disable: 26812)
#pragma warning(disable: 26495)

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

class Model3D
{
	bool _loaded;
public:
	Model3D() :_loaded(false), Meshes(nullptr) {};

	Mesh<VertexPositionNormalTextureTangentBitangentDeclaration>* Meshes;

	Model3D(const char* file)
	{
		Assimp::Importer importer;
		aiScene* scene = (aiScene*)importer.ReadFile(file, aiProcess_Triangulate);
		if (!scene->HasMeshes()) throw ResourceCreationException("Attempted to load a model without any meshes!", typeid(Model3D));
		
		int numMeshes = scene->mNumMeshes;

		this->Meshes = new Mesh<VertexPositionNormalTextureTangentBitangentDeclaration>[numMeshes];
		for (int i = 0; i < numMeshes; i++)
		{
			//i'm taking a break
		}
	}

	
};

#pragma warning(pop)