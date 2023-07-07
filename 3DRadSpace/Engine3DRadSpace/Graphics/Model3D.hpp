#pragma once
#include "ModelMesh.hpp"
#include "Shaders/BasicTextured_NBT.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT Model3D
	{
		Engine3DRadSpace::GraphicsDevice* _device;
		std::vector<std::unique_ptr<ModelMesh>> _meshes;

		void _processNode(std::vector<std::unique_ptr<ModelMeshPart>> &parts,void* currentNode);

		std::shared_ptr<Shaders::ShaderPipeline> basicTexturedNBT;
	public:
		Model3D(GraphicsDevice* Device,const std::string& path);

		Model3D(Model3D &) = delete;
		Model3D(Model3D &&) noexcept = default;

		Model3D &operator=(Model3D &) = delete;
		Model3D &operator=(Model3D &&) noexcept = default;

		void SetTransform(const Engine3DRadSpace::Math::Matrix &m);

		void Draw();
		void Draw(const Engine3DRadSpace::Math::Matrix &m);
		void Draw(const Engine3DRadSpace::Math::Matrix &model, const Engine3DRadSpace::Math::Matrix &view, const Engine3DRadSpace::Math::Matrix &proj);

		using iterator = std::vector<std::unique_ptr<ModelMesh>>::iterator;

		iterator begin();
		iterator end();

		~Model3D() = default;

		ModelMesh *operator[](unsigned i);
	};
}

