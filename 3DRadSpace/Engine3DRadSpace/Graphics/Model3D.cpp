#include "Model3D.hpp"
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "../Logging/Error.hpp"
#include <filesystem>
#include "../Logging/ResourceLoadingError.hpp"
#include "Shaders/BasicTextured_NBT.hpp"

using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace;

Assimp::Importer importer;

std::unique_ptr<Shaders::BasicTextured_NBT> basicTexturedNBT;

Model3D::Model3D(GraphicsDevice* Device, const std::string& path):
	device(Device)
{
	if(basicTexturedNBT == nullptr)
	{
		basicTexturedNBT = std::make_unique<Shaders::BasicTextured_NBT>(Device);
	}

	if(!std::filesystem::exists(path)) throw ResourceLoadingError(Tag<Model3D>{}, path, "This file doesn't exist!");

	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_Triangulate | 
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs | 
		aiProcess_CalcTangentSpace |
		aiProcess_JoinIdenticalVertices | 
		aiProcess_SplitLargeMeshes | 
		aiProcess_SortByPType
	);

	if(scene == nullptr)
		throw ResourceLoadingError(Tag<Model3D>{}, path, importer.GetErrorString());
	if(!scene->HasMeshes())
		throw ResourceLoadingError(Tag<Model3D>{}, path, "The scene doesn't contain any models!");

	//load textures
	for (unsigned i = 0; i < scene->mNumMaterials; i++)
	{
		aiString texturePath;
		aiReturn r = scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
		if (r == aiReturn_SUCCESS)
		{
			std::filesystem::path p(path);
			p.remove_filename();
			p += texturePath.C_Str();

			textures.push_back(std::make_unique<Texture2D>(Device, p.c_str()));
		}
	}
	
	//loop meshes
	std::vector<std::unique_ptr<ModelMeshPart>> meshParts;
	for (unsigned i = 0; i < scene->mNumMeshes; i++) 
	{
		//validate current mesh
		if (!scene->mMeshes[i]->HasFaces())
		{
			continue;
		}
		if (!scene->mMeshes[i]->HasPositions())
		{
			continue;
		}

		//Create index buffer
		std::vector<unsigned> indices;
		for (unsigned j = 0; j < scene->mMeshes[i]->mNumFaces; j++) //loop faces
		{
			unsigned numIndices = scene->mMeshes[i]->mFaces[j].mNumIndices;
			if (numIndices < 3) continue; //skip lines and points

			unsigned* face = scene->mMeshes[i]->mFaces[j].mIndices;

			indices.insert(indices.end(), face, face + numIndices);
		}

		//Find the vertex buffer type
		int numVertexColors = scene->mMeshes[i]->GetNumColorChannels();
		bool hasNormals = scene->mMeshes[i]->HasNormals();
		bool hasBitangents = scene->mMeshes[i]->HasTangentsAndBitangents();
		int numUVMaps = scene->mMeshes[i]->GetNumUVChannels();

		size_t structSize = sizeof(Vector3) * 12; // 3 (position) + 3 (normals) + 3 (tangents) + 3 (bitangents)
		if (numUVMaps == 1) structSize += sizeof(Vector2);
		if (numVertexColors == 1) structSize += sizeof(Color);

		//create the vertex buffer
		unsigned numVerts = scene->mMeshes[i]->mNumVertices;
		std::vector<float> vertices;

		if (hasNormals && hasBitangents)
		{
			for (unsigned j = 0; j < numVerts; j++) //Copy vertices
			{
				auto position = scene->mMeshes[i]->mVertices[j];
				vertices.insert(vertices.end(), {position.x, position.y, position.z});

				auto normal = scene->mMeshes[i]->mNormals[j];
				vertices.insert(vertices.end(), { normal.x, normal.y, normal.z });

				auto tangent = scene->mMeshes[i]->mTangents[j];
				vertices.insert(vertices.end(), { tangent.x, tangent.y, tangent.z });

				auto bitangent = scene->mMeshes[i]->mBitangents[j];
				vertices.insert(vertices.end(), { bitangent.x, bitangent.y, bitangent.z });

				if (numUVMaps == 1)
				{
					auto uv = scene->mMeshes[i]->mTextureCoords[0][j];
					vertices.insert(vertices.end(), { uv.x, uv.y });
				}

				if (numVertexColors == 1)
				{
					auto color = scene->mMeshes[i]->mColors[0][j];
					vertices.insert(vertices.end(), { color.r, color.g, color.b, color.a });
				}
			}
		}
		meshParts.push_back(std::make_unique<ModelMeshPart>(basicTexturedNBT.get(), Device, &vertices[0], numVerts, structSize, indices));
	}

	//generate node structure
	unsigned numChildren = scene->mRootNode->mNumChildren;
	meshes.reserve(numChildren);

	for (unsigned i = 0; i < numChildren; i++)
	{
		processNode(meshParts,scene->mRootNode->mChildren[i]);
	}
}

void Model3D::processNode(std::vector<std::unique_ptr<ModelMeshPart>> &parts, void* currentNode)
{
	if (currentNode == nullptr) return;
	auto node = static_cast<aiNode*>(currentNode);
	
	if(node->mNumMeshes == 0) return;

	std::vector<std::unique_ptr<ModelMeshPart>> lparts;
	for (unsigned i = 0; i < node->mNumMeshes; i++)
	{
		lparts.push_back(std::move(parts[node->mMeshes[i]]));
		lparts[i]->Transform = Matrix(reinterpret_cast<float*>(&node->mTransformation));
	}
	meshes.push_back(std::make_unique<ModelMesh>(lparts));

	for (unsigned i = 0; i < node->mNumChildren; i++)
	{
		processNode(parts,node->mChildren[i]);
	}
}

void Model3D::Draw()
{
	for (auto& mesh : meshes)
	{
		mesh->Draw();
	}
}

Engine3DRadSpace::Graphics::Model3D::iterator Engine3DRadSpace::Graphics::Model3D::begin()
{
	return meshes.begin();
}

Engine3DRadSpace::Graphics::Model3D::iterator Engine3DRadSpace::Graphics::Model3D::end()
{
	return meshes.end();
}

ModelMesh *Engine3DRadSpace::Graphics::Model3D::operator[](unsigned i)
{
	return meshes.at(i).get();
}
