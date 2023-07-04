#pragma once
#include "ModelMeshPart.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT ModelMesh
	{
		std::vector<std::unique_ptr<ModelMeshPart>> _meshParts;
	public:
		ModelMesh(std::span<std::unique_ptr<ModelMeshPart>> parts);
		ModelMesh(ModelMeshPart* parts, size_t numParts);

		ModelMesh(ModelMesh &) = delete;
		ModelMesh(ModelMesh &&) noexcept = default;

		ModelMesh &operator=(ModelMesh &) = delete;
		ModelMesh &operator=(ModelMesh &&) noexcept = default;

		std::vector<std::unique_ptr<ModelMeshPart>>::iterator begin();
		std::vector<std::unique_ptr<ModelMeshPart>>::iterator end();

		void AddMeshPart(std::unique_ptr<ModelMeshPart> &&part);

		ModelMeshPart* operator[](unsigned i);

		void Draw();

		~ModelMesh() = default;
	};
}

