#include "Model3D.hpp"
#include "../Logging/Exception.hpp"
#include "../Logging/AssetLoadingError.hpp"
#include "IShaderCompiler.hpp"

#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

Assimp::Importer importer;

Effect* Model3D::_loadBasicShader(IGraphicsDevice* device)
{
	constexpr const char* basicEffectPath = "Data\\Shaders\\PositionNormalTangentUV.hlsl";

	auto vsBasicEffect = ShaderDescFile(
		basicEffectPath,
		"VS_Main",
		ShaderType::Vertex
	);

	auto psBasicEffect = ShaderDescFile(
		basicEffectPath,
		"PS_Main",
		ShaderType::Fragment
	);

	std::array<ShaderDesc*, 2> basicEffectDesc =
	{
		&vsBasicEffect,
		&psBasicEffect
	};

	auto result = device->ShaderCompiler()->CompileEffect(basicEffectDesc);
	if (result.second.Succeded == false)
	{
		throw Exception("Failed to compile default shader for Model3D!" + result.second.Log);
	}
	return result.first;
}

Model3D::Model3D(IGraphicsDevice* Device, const std::filesystem::path& path) :
	_device(Device)
{
	auto basicEffect = _loadBasicShader(Device);

	if (!std::filesystem::exists(path)) throw AssetLoadingError(Tag<Model3D>{}, path, "This file doesn't exist!");

	auto steps = 
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_CalcTangentSpace |
		aiProcess_JoinIdenticalVertices |
		aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph |
		aiProcess_RemoveRedundantMaterials |
		aiProcess_SplitLargeMeshes |
		aiProcess_SortByPType |
		aiProcess_GenBoundingBoxes;

	std::unordered_map<std::string, int> backends =
	{
	/*	{"DirectX9", 1},
		{"DirectX10", 1},*/
		{"DirectX11", 1},
		{"DirectX12", 1},
	};

	if (backends[std::string(Device->BackendName())] == 1)
	{
		steps |= aiProcess_FlipUVs | aiProcess_FlipWindingOrder;
	}

	const aiScene* scene = importer.ReadFile(path.string(), steps);

	if(scene == nullptr)
		throw AssetLoadingError(Tag<Model3D>{}, path, importer.GetErrorString());
	if(!scene->HasMeshes())
		throw AssetLoadingError(Tag<Model3D>{}, path, "The scene doesn't contain any models!");
	
	//loop meshes
	std::vector<std::unique_ptr<ModelMeshPart>> meshParts;
	for (unsigned i = 0, k =0; i < scene->mNumMeshes; i++) 
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

		size_t structSize = sizeof(Vector3) * 4; //position + normal + tangent + bitangent
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

		if(vertices.empty() || indices.empty())
		{
			meshParts.push_back(nullptr);
			continue;
		}

		auto mesh = std::make_unique<ModelMeshPart>(Device, &vertices[0], numVerts, structSize, indices, basicEffect);
		
		//determine bounding box and sphere
		auto aabbMin = scene->mMeshes[i]->mAABB.mMin;
		auto aabbMax = scene->mMeshes[i]->mAABB.mMax;
		mesh->_box = BoundingBox(
			Vector3(aabbMin.x, aabbMin.y, aabbMin.z),
			Vector3(aabbMax.x - aabbMin.x, aabbMax.y - aabbMin.y, aabbMax.z - aabbMin.z)
		);
		mesh->_sphere = BoundingSphere(mesh->_box);
		std::unique_ptr<ITexture2D> diffuseTexture;

		if(numUVMaps == 1)
		{
			int materialindex = scene->mMeshes[i]->mMaterialIndex;
			aiString texturePath;
			aiReturn r = scene->mMaterials[materialindex]->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
			if(r == aiReturn_SUCCESS)
			{
				std::filesystem::path p(path); //get the current path of the model
				p.remove_filename(); //remove the model filename 
				p += texturePath.C_Str(); //concatenate the texture path.

				diffuseTexture = Device->CreateTexture2D(p.string());
			}
			else
			{
				aiColor3D color;
				r = scene->mMaterials[materialindex]->Get(AI_MATKEY_COLOR_DIFFUSE, color);

				auto createBlankTexture = [&](const Color& c)
				{
					std::array<Color, 4> tColors;
					tColors.fill(c);
					return Device->CreateTexture2D(tColors.data(), 2, 2, PixelFormat::R32G32B32A32_Float, BufferUsage::ReadOnlyGPU_WriteOnlyCPU);
				};

				if(r == aiReturn_SUCCESS)
				{
					float opacity = 1.0f;
					scene->mMaterials[materialindex]->Get(AI_MATKEY_OPACITY, opacity);

					diffuseTexture = createBlankTexture(Color(color.r, color.g, color.b, opacity));
				}
				else
				{
					diffuseTexture = createBlankTexture(Colors::White);
				}
			}
		}

		mesh->Textures.push_back(std::move(diffuseTexture));
		mesh->TextureSamplers.push_back(Device->CreateSamplerState());
		meshParts.push_back(std::move(mesh));
	}

	//generate node structure
	unsigned numChildren = scene->mRootNode->mNumChildren;

	if(numChildren != 0)
	{
		_meshes.reserve(numChildren);

		for(unsigned i = 0; i < numChildren; i++)
		{
			_processNode(meshParts, scene->mRootNode->mChildren[i]);
		}
	}
	else
	{
		_meshes.push_back(std::make_unique<ModelMesh>(meshParts));
	}

	if(_meshes.size() == 0)
	{
		_box = BoundingBox(Vector3(0, 0, 0), Vector3(0, 0, 0));
		_sphere = BoundingSphere(Vector3(0, 0, 0), 0);
		return;
	}

	_box = _meshes[0]->GetBoundingBox();
	_sphere = _meshes[0]->GetBoundingSphere();

	for (size_t i = 1; i < _meshes.size(); i++)
	{
		_box = BoundingBox(_box, _meshes[i]->GetBoundingBox());
		_sphere = BoundingSphere(_sphere, _meshes[i]->GetBoundingSphere());
	}
}

void Model3D::_processNode(std::vector<std::unique_ptr<ModelMeshPart>> &parts, void* currentNode)
{
	if (currentNode == nullptr) return;
	if(parts.empty()) return;

	auto node = static_cast<aiNode*>(currentNode);
	
	if(node->mNumMeshes == 0) return;

	std::vector<std::unique_ptr<ModelMeshPart>> lparts;
	for (unsigned i = 0; i < node->mNumMeshes; i++)
	{
		if(parts[node->mMeshes[i]] == nullptr) continue;

		lparts.push_back(std::move(parts[node->mMeshes[i]]));
		lparts[i]->Transform = Matrix4x4(reinterpret_cast<float*>(&node->mTransformation));
	}
	_meshes.push_back(std::make_unique<ModelMesh>(lparts));

	for (unsigned i = 0; i < node->mNumChildren; i++)
	{
		_processNode(parts, node->mChildren[i]);
	}
}

void Model3D::SetTransform(const Matrix4x4&m)
{
	for(const auto &mesh : _meshes)
	{
		for(auto &meshPart : *mesh.get())
		{
			meshPart->Transform = m;
		}
	}
}

void Model3D::Draw()
{
	for (auto& mesh :_meshes)
	{
		mesh->Draw();
	}
}

void Model3D::Draw(const Matrix4x4&m)
{
	for(auto &mesh : _meshes)
	{
		for(auto &meshPart : *mesh.get())
		{
			meshPart->Transform = m;
			meshPart->Draw();
		}
	}
}

Model3D::iterator Model3D::begin()
{
	return _meshes.begin();
}

Model3D::iterator Model3D::end()
{
	return _meshes.end();
}

size_t Model3D::NumMeshes()
{
	return _meshes.size();
}

BoundingBox Model3D::GetBoundingBox() const noexcept
{
	return _box;
}

BoundingSphere Model3D::GetBoundingSphere() const noexcept
{
	return _sphere;
}

void Model3D::SetShader(Effect* effect)
{
	for (auto& mesh : _meshes)
	{
		for (auto& meshPart : *mesh.get())
		{
			meshPart->SetShaders(effect);
		}
	}
}

void Model3D::SetShaders(std::span<Effect*> effects)
{
	size_t i = 0;
	size_t len = effects.size();

	for (auto const& mesh : _meshes)
	{
		for (auto const& meshPart : *mesh.get())
		{
			if (i < len)
				meshPart->SetShaders(effects[i++]);
			else return;
		}
	}
}

void Model3D::DrawEffect(Effect *effect)
{
	for (auto& mesh : _meshes)
	{
		for (auto& meshPart : *mesh.get())
		{
			meshPart->Draw(effect);
		}
	}
}

void Model3D::DrawEffect(Effect* effect, const Math::Matrix4x4& mvp)
{
	for(auto &mesh : _meshes)
	{
		for(auto &meshPart : *mesh.get())
		{
			meshPart->Transform = mvp;
			meshPart->Draw(effect);
		}
	}
}

ModelMesh* Model3D::operator[](unsigned i)
{
	return _meshes.at(i).get();
}