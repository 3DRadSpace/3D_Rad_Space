#pragma once
#include "ModelMesh.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Model3D
	{
		Engine3DRadSpace::GraphicsDevice* _device;
		std::vector<std::unique_ptr<ModelMesh>> _meshes;

		void _processNode(std::vector<std::unique_ptr<ModelMeshPart>> &parts,void* currentNode);
	public:
		Model3D(GraphicsDevice* Device,const std::string& path);

		void SetTransform(const Engine3DRadSpace::Math::Matrix &m);

		void Draw();
		void Draw(const Engine3DRadSpace::Math::Matrix &m);
		void Draw(const Engine3DRadSpace::Math::Matrix &model, const Engine3DRadSpace::Math::Matrix &view, const Engine3DRadSpace::Math::Matrix &proj);

		using iterator = std::vector<std::unique_ptr<ModelMesh>>::iterator;

		iterator begin();
		iterator end();

		ModelMesh *operator[](unsigned i);
	};
}

