#include "ModelMesh.hpp"

using namespace Engine3DRadSpace::Graphics;

Engine3DRadSpace::Graphics::ModelMesh::ModelMesh(std::span<std::unique_ptr<ModelMeshPart>> parts)
{
	for (auto&& mesh : parts)
	{
		_meshParts.push_back(std::move(mesh));
	}
}

Engine3DRadSpace::Graphics::ModelMesh::ModelMesh(ModelMeshPart* parts, size_t numParts)
{
	for (size_t i = 0; i < numParts; i++)
	{
		_meshParts.push_back(std::make_unique<ModelMeshPart>(std::move(parts[i])));
	}
}

std::vector<std::unique_ptr<ModelMeshPart>>::iterator Engine3DRadSpace::Graphics::ModelMesh::begin()
{
	return _meshParts.begin();
}

std::vector<std::unique_ptr<ModelMeshPart>>::iterator Engine3DRadSpace::Graphics::ModelMesh::end()
{
	return _meshParts.end();
}

void Engine3DRadSpace::Graphics::ModelMesh::AddMeshPart(std::unique_ptr<ModelMeshPart>&& part)
{
	_meshParts.push_back(std::move(part));
}

ModelMeshPart* Engine3DRadSpace::Graphics::ModelMesh::operator[](unsigned i)
{
	return _meshParts[i].get();
}

void Engine3DRadSpace::Graphics::ModelMesh::Draw()
{
	for (auto& mesh : *this)
	{
		mesh->Draw();
	}
}
