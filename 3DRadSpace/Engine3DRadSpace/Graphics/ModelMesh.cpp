#include "ModelMesh.hpp"

using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

ModelMesh::ModelMesh(std::span<std::unique_ptr<ModelMeshPart>> parts)
{
	for (auto&& mesh : parts)
	{
		_meshParts.push_back(std::move(mesh));
	}
	_createBoundingObjects();
}

void ModelMesh::_createBoundingObjects()
{
	_box = _meshParts[0]->GetBoundingBox();
	_sphere = _meshParts[0]->GetBoundingSphere();
	for (size_t i = 1; i < _meshParts.size(); i++)
	{
		_box = BoundingBox(_box, _meshParts[i]->GetBoundingBox());
		_sphere = BoundingSphere(_sphere, _meshParts[i]->GetBoundingSphere());
	}
}

ModelMesh::ModelMesh(ModelMeshPart* parts, size_t numParts)
{
	for (size_t i = 0; i < numParts; i++)
	{
		_meshParts.push_back(std::make_unique<ModelMeshPart>(std::move(parts[i])));
	}

	_createBoundingObjects();
}

std::vector<std::unique_ptr<ModelMeshPart>>::iterator ModelMesh::begin()
{
	return _meshParts.begin();
}

std::vector<std::unique_ptr<ModelMeshPart>>::iterator ModelMesh::end()
{
	return _meshParts.end();
}

void ModelMesh::AddMeshPart(std::unique_ptr<ModelMeshPart>&& part)
{
	_meshParts.push_back(std::move(part));
}

ModelMeshPart* ModelMesh::operator[](unsigned i)
{
	return _meshParts[i].get();
}

void ModelMesh::Draw()
{
	for (auto& mesh : *this)
	{
		mesh->Draw();
	}
}

BoundingBox ModelMesh::GetBoundingBox()
{
	return _box;
}

BoundingSphere ModelMesh::GetBoundingSphere()
{
	return _sphere;
}
