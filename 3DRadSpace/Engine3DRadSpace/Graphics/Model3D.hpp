#pragma once
#include "ModelMesh.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Model3D
	{
		Engine3DRadSpace::GraphicsDevice* _device;
		std::vector<std::unique_ptr<ModelMesh>> _meshes;
		std::vector<std::unique_ptr<Texture2D>> _textures;

		void _processNode(std::vector<std::unique_ptr<ModelMeshPart>> &parts,void* currentNode);
	public:
		Model3D(GraphicsDevice* Device,const std::string& path);

		void Draw();

		using iterator = std::vector<std::unique_ptr<ModelMesh>>::iterator;

		iterator begin();
		iterator end();

		ModelMesh *operator[](unsigned i);
	};
}

