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

		void _processNode(std::vector<std::unique_ptr<ModelMeshPart>> &parts, void* currentNode);

		Math::BoundingSphere _sphere;
		Math::BoundingBox _box;
	public:
		Model3D(IGraphicsDevice* Device, const std::filesystem::path& path);

		Model3D(Model3D &) = delete;
		Model3D(Model3D &&) noexcept = default;

		Model3D &operator=(Model3D &) = delete;
		Model3D &operator=(Model3D &&) noexcept = default;

		/// <summary>
		///	Sets the world, view, and projection transform matrices for the model.
		/// </summary>
		/// <param name="w">The world matrix.</param>
		/// <param name="v">The view matrix.</param>
		/// <param name="p">The projection matrix.</param>
		void SetTransform(
			const Math::Matrix4x4& w,
			const Math::Matrix4x4& v,
			const Math::Matrix4x4& p
		);

		void SetTransform(const Math::Matrix4x4& v, const Math::Matrix4x4& p);

		ModelMesh* operator[](unsigned i);

		std::vector<std::unique_ptr<ModelMesh>>::iterator begin();
		std::vector<std::unique_ptr<ModelMesh>>::iterator end();

		size_t NumMeshes();

		Math::BoundingBox GetBoundingBox() const noexcept;
		Math::BoundingSphere GetBoundingSphere() const noexcept;

		~Model3D() = default;
	};
}