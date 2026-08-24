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

		/// <summary>
		/// Sets the view and projection matrices.
		/// </summary>
		/// <param name="v">View matrix</param>
		/// <param name="p">Projection matrix</param>
		void SetTransform(const Math::Matrix4x4& v, const Math::Matrix4x4& p);

		/// <summary>
		/// Gets the i-th ModelMesh in the model. No null checking.
		/// </summary>
		/// <param name="i">The index of the ModelMesh to retrieve.</param>
		/// <returns>The i-th ModelMesh.</returns>
		ModelMesh* operator[](unsigned i);

		/// <summary>
		/// Begin iterator for the collection of ModelMesh instances in the model.
		/// </summary>
		/// <returns>An iterator to the beginning of the collection of ModelMesh instances.</returns>
		std::vector<std::unique_ptr<ModelMesh>>::iterator begin();
		/// <summary>
		/// End iterator for the collection of ModelMesh instances in the model.
		/// </summary>
		/// <returns>An iterator to the end of the collection of ModelMesh instances.</returns>
		std::vector<std::unique_ptr<ModelMesh>>::iterator end();
		/// <summary>
		///	Returns the number of ModelMesh instances in this model.
		/// </summary>
		/// <returns></returns>
		size_t NumMeshes();

		/// <summary>
		/// Gets the bounding box of this entire model instance.
		/// </summary>
		/// <returns>The bounding box of this entire model instance.</returns>
		Math::BoundingBox GetBoundingBox() const noexcept;
		/// <summary>
		/// Gets the bounding sphere of this entire model instance.
		/// </summary>
		/// <returns>The bounding sphere of this entire model instance.</returns>
		Math::BoundingSphere GetBoundingSphere() const noexcept;

		~Model3D() = default;
	};
}