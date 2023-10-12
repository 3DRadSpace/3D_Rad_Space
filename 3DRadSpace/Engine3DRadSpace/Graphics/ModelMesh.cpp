#include "ModelMesh.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

Engine3DRadSpace::Graphics::ModelMesh::ModelMesh(std::span<std::unique_ptr<ModelMeshPart>> parts)
{
	for (auto&& mesh : parts)
	{
		_meshParts.push_back(std::move(mesh));
	}
	_createBoundingObjects();
}

void Engine3DRadSpace::Graphics::ModelMesh::_createBoundingObjects()
{
	_box = _meshParts[0]->GetBoundingBox();
	_sphere = _meshParts[0]->GetBoundingSphere();
	for (size_t i = 1; i < _meshParts.size(); i++)
	{
		_box = BoundingBox(_box, _meshParts[i]->GetBoundingBox());
		_sphere = BoundingSphere(_sphere, _meshParts[i]->GetBoundingSphere());
	}
}

Engine3DRadSpace::Graphics::ModelMesh::ModelMesh(ModelMeshPart* parts, size_t numParts)
{
	for (size_t i = 0; i < numParts; i++)
	{
		_meshParts.push_back(std::make_unique<ModelMeshPart>(std::move(parts[i])));
	}

	_createBoundingObjects();
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

BoundingBox Engine3DRadSpace::Graphics::ModelMesh::GetBoundingBox()
{
	return _box;
}

BoundingSphere Engine3DRadSpace::Graphics::ModelMesh::GetBoundingSphere()
{
	return _sphere;
}
