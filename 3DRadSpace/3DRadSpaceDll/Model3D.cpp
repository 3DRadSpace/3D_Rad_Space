#include "Model3D.hpp"
#include <PathCch.h>

Engine3DRadSpace::Model3D::Model3D(Game* game, const char* file)
{
	this->device = game->GetDevice();
	this->context = game->GetDeviceContext();
	this->_loaded = false;

	Assimp::Importer importer;
	aiScene* scene = (aiScene*)importer.ReadFile(file, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace | aiProcess_ImproveCacheLocality | aiProcess_RemoveRedundantMaterials | aiProcess_OptimizeMeshes | aiProcess_MakeLeftHanded | aiProcess_OptimizeGraph);

	if (scene == nullptr)
		throw ResourceCreationException("Failed to load the file while attempting to create a model!");

	NumMeshes = scene->mNumMeshes;

	if (NumMeshes == 0 || !scene->HasMeshes())
		throw ResourceCreationException("Attempted to load a model without any meshes!");

	Meshes = new MeshPart<void>*[NumMeshes];

	//NumTextures = scene->mNumTextures;
	NumTextures = 0;

	size_t i;
	for (i = 0;i < scene->mNumMaterials; i++)
	{
		aiString loadpath;
		aiReturn r = scene->mMaterials[i]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &loadpath);
		if (r == aiReturn::aiReturn_SUCCESS)
			NumTextures += 1;
	}

	if(NumTextures > 0)
	{
		Textures = new Texture2D * [NumTextures];
	}
	else Textures = nullptr;

	for (i = 0; i < scene->mNumMaterials; i++)
	{
		aiString loadpath;
		aiReturn r = scene->mMaterials[i]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &loadpath);
		
		if(r == aiReturn::aiReturn_SUCCESS)
		{
			char texturepath[MAX_PATH]{};
			strcpy_s(texturepath, strlen(file) + 1, file);
			for(int j = strlen(texturepath); j >= 0; j--)
			{
				if(texturepath[j] == '\\')
					memset(texturepath + j + 1, 0, strlen(texturepath) - j - 1);
			}
			strcat_s(texturepath, loadpath.C_Str());

			Textures[i] = new Texture2D(game, texturepath);
		}
		else Textures[i] = nullptr;
	}

	/*
	for (i = 0; i < NumTextures; i++)
	{
		if (scene->mTextures[i]->mHeight != 0)
		{
			this->Textures[i] = new Texture2D(game, scene->mTextures[i]->pcData, scene->mTextures[i]->mWidth * scene->mTextures[i]->mHeight);
		}
	}*/

	for (i = 0; i < NumMeshes; i++)
	{
		//We won't allow creating lines, dots and empty meshes
		if (!scene->mMeshes[i]->HasFaces() || scene->mMeshes[i]->mNumVertices < 2)
		{
			Meshes[i] = nullptr;
			continue;
		}

		bool hasNormals = scene->mMeshes[i]->HasNormals();
		bool hasVertexColor = scene->mMeshes[i]->HasVertexColors(0);
		bool hasTangentBitangent = scene->mMeshes[i]->HasTangentsAndBitangents();
		bool hasUV = scene->mMeshes[i]->HasTextureCoords(0);

		//determine vertex buffer size
		size_t numVerts = scene->mMeshes[i]->mNumVertices;

		size_t vertexdeclsize = sizeof(Vector3);

		if (hasNormals)
			vertexdeclsize += sizeof(Vector3);

		if (hasVertexColor)
			vertexdeclsize += sizeof(ColorShader);

		if (hasTangentBitangent)
			vertexdeclsize += 2 * sizeof(Vector3);

		if (hasUV)
			vertexdeclsize += sizeof(Vector3);

		//create vertex buffer in memory
		size_t finalvertexbuffersize = (vertexdeclsize * numVerts);
		float* vertexbuffer = new float[finalvertexbuffersize];
		memset(vertexbuffer, 0, sizeof(float) * finalvertexbuffersize);

		for (unsigned pos = 0, j = 0; j < numVerts; j++)
		{
			memcpy_s(vertexbuffer + pos, sizeof(Vector3), &(scene->mMeshes[i]->mVertices[j]), sizeof(Vector3));
			pos += 3;
			if (hasNormals)
			{
				memcpy_s(vertexbuffer + pos, sizeof(Vector3), &(scene->mMeshes[i]->mNormals[j]), sizeof(Vector3));
				pos += 3;
			}
			if (hasVertexColor)
			{
				memcpy_s(vertexbuffer + pos, sizeof(ColorShader), &(scene->mMeshes[i]->mColors[0][j]), sizeof(ColorShader));
				pos += 4;
			}
			if (hasTangentBitangent)
			{
				memcpy_s(vertexbuffer + pos, sizeof(Vector3), &(scene->mMeshes[i]->mTangents[j]), sizeof(Vector3));
				pos += 3;
				memcpy_s(vertexbuffer + pos, sizeof(Vector3), &(scene->mMeshes[i]->mBitangents[j]), sizeof(Vector3));
				pos += 3;
			}
			if (hasUV)
			{
				memcpy_s(vertexbuffer + pos, sizeof(Vector3), &(scene->mMeshes[i]->mTextureCoords[0][j]), sizeof(Vector3));
				pos += 3;
			}
		}

		//create index buffer
		size_t indexbuffersize = static_cast<size_t>(scene->mMeshes[i]->mNumFaces) * 3; //faces are triangulated, so multiply with 3

		unsigned* indexbuffer = new unsigned[indexbuffersize];

		for (unsigned j = 0; j < indexbuffersize / 3; j += 3)
		{
			memcpy_s(indexbuffer + j, sizeof(unsigned) * 3, scene->mMeshes[i]->mFaces[j].mIndices, sizeof(unsigned) * 3);
		}

		VertexBuffer<void>* vertexbuffer_f = new VertexBuffer<void>(vertexbuffer, numVerts, vertexdeclsize);
		vertexbuffer_f->CreateVertexBuffer(device);

		IndexBuffer* indexbuffer_f = new IndexBuffer(indexbuffer, indexbuffersize);
		indexbuffer_f->CreateIndexBuffer(device);

		this->Meshes[i] = new MeshPart<void>(vertexbuffer_f, indexbuffer_f, Textures[scene->mMeshes[i]->mMaterialIndex]);
	}
	this->_loaded = true;
}

void Engine3DRadSpace::Model3D::Draw()
{
	for (size_t i = 0; i < NumMeshes; i++)
	{
		this->Meshes[i]->Draw(context);
	}
}

void Engine3DRadSpace::Model3D::SetTransformation(Matrix& m)
{
	for(size_t i = 0; i < NumMeshes; i++)
	{
		this->Meshes[i]->Transformation = m;
	}
}

Engine3DRadSpace::Matrix&& Engine3DRadSpace::Model3D::GetTransformation()
{
	return Matrix(this->Meshes[0]->Transformation);
}

Engine3DRadSpace::Model3D::~Model3D()
{
	size_t i;
	for (i = 0; i < NumMeshes; i++)
	{
		if (this->Meshes[i] != nullptr) delete this->Meshes[i];
	}
	delete[] this->Meshes;

	if(this->Textures != nullptr)
	{
		for(i = 0; i < NumTextures; i++)
		{
			if(this->Textures[i] != nullptr) delete this->Textures[i];
		}
		delete[] this->Textures;
	}

	this->Meshes = nullptr;
	this->Textures = nullptr;
}
