#pragma once
#include "ModelMesh.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Model3D
	{
		Engine3DRadSpace::GraphicsDevice* device;
		std::vector<std::unique_ptr<ModelMesh>> meshes;
		std::vector<std::unique_ptr<Texture2D>> textures;

		void processNode(std::vector<std::unique_ptr<ModelMeshPart>> &parts,void* currentNode);
	public:
		Model3D(GraphicsDevice* Device,const std::string& path);

		void Draw();
	};
}

