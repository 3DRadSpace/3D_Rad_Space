#pragma once
#include "ModelMesh.hpp"
#include "../Math/BoundingSphere.hpp"
#include "../Math/BoundingBox.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents a 3D model, composed of multiple ModelMesh instances.
	/// </summary>
	/// <remarks>
	/// Assimp is used to load the model.
	/// </remarks>
	class E3DRSP_GRAPHICS_EXPORT Model3D
	{
		IGraphicsDevice* _device;
		std::vector<std::unique_ptr<ModelMesh>> _meshes;

		Effect* _loadBasicShader(IGraphicsDevice* device);
		void _processNode(std::vector<std::unique_ptr<ModelMeshPart>> &parts, void* currentNode);

		Math::BoundingSphere _sphere;
		Math::BoundingBox _box;
	public:
		Model3D(IGraphicsDevice* Device, const std::filesystem::path& path);

		Model3D(Model3D &) = delete;
		Model3D(Model3D &&) noexcept = default;

		Model3D &operator=(Model3D &) = delete;
		Model3D &operator=(Model3D &&) noexcept = default;

		void SetTransform(const Math::Matrix4x4 &m);

		void Draw();
		void Draw(const Math::Matrix4x4 &mvp);
		
		void DrawEffect(Effect *effect);
		void DrawEffect(Effect *effect, const Math::Matrix4x4 &mvp);

		using iterator = std::vector<std::unique_ptr<ModelMesh>>::iterator;
		iterator begin();
		iterator end();
		size_t NumMeshes();

		Math::BoundingBox GetBoundingBox() const noexcept;
		Math::BoundingSphere GetBoundingSphere() const noexcept;

		void SetShader(Effect* effect);
		void SetShaders(std::span<Effect*> effects);

		~Model3D() = default;

		ModelMesh *operator[](unsigned i);
	};
}