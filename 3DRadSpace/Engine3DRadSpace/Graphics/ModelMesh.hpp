#pragma once
#include "ModelMeshPart.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents a collection of multiple ModelMeshPart instances.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT ModelMesh
	{
		std::vector<std::unique_ptr<ModelMeshPart>> _meshParts;

		Math::BoundingBox _box;
		Math::BoundingSphere _sphere;

		void _createBoundingObjects();
	public:
		/// <summary>
		/// Creates a ModelMesh from a array of ModelMeshParts.
		/// </summary>
		/// <param name="parts">Array of unique pointer of parts.</param>
		ModelMesh(std::span<std::unique_ptr<ModelMeshPart>> parts);
		/// <summary>
		/// Creates a ModelMesh from a C-style array of ModelMeshParts.
		/// </summary>
		/// <param name="parts">C-style pointer array of ModelMeshPart instances</param>
		/// <param name="numParts">Number of instances.</param>
		ModelMesh(ModelMeshPart* parts, size_t numParts);

		ModelMesh(ModelMesh &) = delete;
		ModelMesh(ModelMesh &&) noexcept = default;

		ModelMesh &operator=(ModelMesh &) = delete;
		ModelMesh &operator=(ModelMesh &&) noexcept = default;

		std::vector<std::unique_ptr<ModelMeshPart>>::iterator begin();
		std::vector<std::unique_ptr<ModelMeshPart>>::iterator end();

		/// <summary>
		/// Adds a ModelMeshPart into this ModelMesh.
		/// </summary>
		/// <param name="part">part will become "moved" because it is now owned by this.</param>
		void AddMeshPart(std::unique_ptr<ModelMeshPart> &&part);

		/// <summary>
		/// Returns the i-th ModelMeshPart. No null checking.
		/// </summary>
		/// <param name="i">index</param>
		/// <returns>i-th ModelMeshPart.</returns>
		ModelMeshPart* operator[](unsigned i);

		size_t NumMeshParts() const noexcept;

		/// <summary>
		/// Draw each ModelMeshPart.
		/// </summary>
		void Draw();

		/// <summary>
		/// Gets the bounding box of all ModelMeshParts.
		/// </summary>
		/// <returns></returns>
		Math::BoundingBox GetBoundingBox() const noexcept;
		/// <summary>
		/// Gets the bounding sphere of all ModelMeshParts.
		/// </summary>
		/// <returns></returns>
		Math::BoundingSphere GetBoundingSphere() const noexcept;

		~ModelMesh() = default;
	};
}

