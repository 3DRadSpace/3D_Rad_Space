#pragma once
#include "ModelMeshPart.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ModelMesh
	{
		std::vector<std::unique_ptr<ModelMeshPart>> meshParts;
	public:
		ModelMesh(std::span<std::unique_ptr<ModelMeshPart>> parts);
		ModelMesh(ModelMeshPart* parts, size_t numParts);

		std::vector<std::unique_ptr<ModelMeshPart>>::iterator begin();
		std::vector<std::unique_ptr<ModelMeshPart>>::iterator end();

		void AddMeshPart(std::unique_ptr<ModelMeshPart> &&part);

		ModelMeshPart* operator[](unsigned i);

		void Draw();
	};
}

