#include "Model3D.hpp"
#include <PathCch.h>

inline Engine3DRadSpace::VertexDeclDeterminantFlag Engine3DRadSpace::operator|(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b)
{
	return static_cast<VertexDeclDeterminantFlag>(static_cast<int>(a) | static_cast<int>(b));
}

inline Engine3DRadSpace::VertexDeclDeterminantFlag Engine3DRadSpace::operator|=(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b)
{
	return static_cast<VertexDeclDeterminantFlag>(static_cast<int>(a) | static_cast<int>(b));
}

inline Engine3DRadSpace::VertexDeclDeterminantFlag Engine3DRadSpace::operator&(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b)
{
	return static_cast<VertexDeclDeterminantFlag>(static_cast<int>(a) & static_cast<int>(b));
}

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
	MeshFlags = new VertexDeclDeterminantFlag[NumMeshes];

	//NumTextures = scene->mNumTextures;
	NumTextures = 0;

	size_t i;

	for (i = 0; i < scene->mNumMaterials; i++)
	{
		aiString loadpath;
		aiReturn r = scene->mMaterials[i]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &loadpath);
		if (r == aiReturn::aiReturn_SUCCESS)
			NumTextures += 1;
	}

	Textures = new Texture2D * [NumTextures];

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

		//determine the vertex buffer layout
		MeshFlags[i] = VertexDeclDeterminantFlag::Position;
		if (scene->mMeshes[i]->HasNormals()) MeshFlags[i] |= VertexDeclDeterminantFlag::Normal;
		if (scene->mMeshes[i]->HasTangentsAndBitangents()) MeshFlags[i] |= VertexDeclDeterminantFlag::TangentBitangent;

		unsigned NumVColors = scene->mMeshes[i]->GetNumUVChannels();
		if (NumVColors == 1) MeshFlags[i] |= VertexDeclDeterminantFlag::SingleVertexColor;
		else if (NumVColors > 1) throw ResourceCreationException("Multiple color channels not supported");//MeshFlags[i] |= VertexDeclDeterminantFlag::MultipleVertexColors;

		unsigned NumUV = scene->mMeshes[i]->GetNumUVChannels();
		if (NumUV == 1) MeshFlags[i] |= VertexDeclDeterminantFlag::SingleUV;
		else if (NumUV > 1)  throw ResourceCreationException("Multiple UV channels not supported");//MeshFlags[i] |= VertexDeclDeterminantFlag::MultipleUVs;

		bool hasNormals = CheckVertexDeclDeterminant(MeshFlags[i], VertexDeclDeterminantFlag::Normal);
		bool hasVertexColor = CheckVertexDeclDeterminant(MeshFlags[i], VertexDeclDeterminantFlag::SingleVertexColor);
		bool hasTangentBitangent = CheckVertexDeclDeterminant(MeshFlags[i], VertexDeclDeterminantFlag::TangentBitangent);
		bool hasUV = CheckVertexDeclDeterminant(MeshFlags[i], VertexDeclDeterminantFlag::SingleUV);

		//determine vertex buffer size
		size_t vertexbuffersize = scene->mMeshes[i]->mNumVertices;

		size_t vertexdeclsize = sizeof(Vector4);

		if (hasNormals)
			vertexdeclsize += sizeof(Vector4);

		if (hasVertexColor)
			vertexdeclsize += sizeof(ColorShader);

		if (hasTangentBitangent)
			vertexdeclsize += 2 * sizeof(Vector4);

		if (hasUV)
			vertexdeclsize += sizeof(Vector4);

		//create vertex buffer in memory
		size_t finalvertexbuffersize = (vertexdeclsize * vertexbuffersize) / 4;
		float* vertexbuffer = new float[finalvertexbuffersize];
		//memset(vertexbuffer, 0, sizeof(float) * finalvertexbuffersize);

		for (unsigned pos = 0, j = 0; pos < finalvertexbuffersize; j++)
		{
			memcpy_s(vertexbuffer + pos, sizeof(Vector3), &(scene->mMeshes[i]->mVertices[j]), sizeof(Vector3));
			pos += 4;
			if (hasNormals)
			{
				memcpy_s(vertexbuffer + pos, sizeof(Vector3), &(scene->mMeshes[i]->mNormals[j]), sizeof(Vector3));
				pos += 4;
			}
			if (hasVertexColor)
			{
				memcpy_s(vertexbuffer + pos, sizeof(ColorShader), &(scene->mMeshes[i]->mColors[0][j]), sizeof(ColorShader));
				pos += 4;
			}
			if (hasTangentBitangent)
			{
				memcpy_s(vertexbuffer + pos, sizeof(Vector3), &(scene->mMeshes[i]->mTangents[j]), sizeof(Vector3));
				pos += 4;
				memcpy_s(vertexbuffer + pos, sizeof(Vector3), &(scene->mMeshes[i]->mBitangents[j]), sizeof(Vector3));
				pos += 4;
			}
			if (hasUV)
			{
				memcpy_s(vertexbuffer + pos, sizeof(Vector3), &(scene->mMeshes[i]->mTextureCoords[0][j]), sizeof(Vector3));
				pos += 4;
			}
		}

		//create index buffer
		size_t indexbuffersize = static_cast<size_t>(scene->mMeshes[i]->mNumFaces) * 3; //faces are triangulated, so multiply with 3

		unsigned* indexbuffer = new unsigned[indexbuffersize];

		for (unsigned j = 0; j < indexbuffersize / 3; j += 3)
		{
			memcpy_s(indexbuffer + j, sizeof(unsigned) * 3, scene->mMeshes[i]->mFaces[j].mIndices, sizeof(unsigned) * 3);
		}

		VertexBuffer<void>* vertexbuffer_f = new VertexBuffer<void>(vertexbuffer, vertexbuffersize, vertexdeclsize);
		IndexBuffer* indexbuffer_f = new IndexBuffer(indexbuffer, indexbuffersize);

		this->Meshes[i] = new MeshPart<void>(vertexbuffer_f, indexbuffer_f, Textures[scene->mMeshes[i]->mMaterialIndex]);
		this->_loaded = true;
	}
}

bool Engine3DRadSpace::Model3D::CheckVertexDeclDeterminant(VertexDeclDeterminantFlag flag, VertexDeclDeterminantFlag comp)
{
	return (comp == (flag & comp));
}

void Engine3DRadSpace::Model3D::Draw()
{
	for (size_t i = 0; i < NumMeshes; i++)
	{
		this->Meshes[i]->Draw(context);
	}
}

Engine3DRadSpace::Model3D::~Model3D()
{
	size_t i;
	for (i = 0; i < NumMeshes; i++)
	{
		if (this->Meshes[i] != nullptr) delete this->Meshes[i];
	}
	delete[] this->Meshes;
	delete[] this->MeshFlags;

	for (i = 0; i < NumTextures; i++)
	{
		if (this->Textures[i] != nullptr) delete this->Textures[i];
	}
	delete[] this->Textures;

	this->Meshes = nullptr;
	this->MeshFlags = nullptr;
	this->Textures = nullptr;
}
