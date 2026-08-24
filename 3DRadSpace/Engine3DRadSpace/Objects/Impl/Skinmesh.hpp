#pragma once

#include "../IObject3D.hpp"
#include "../../Graphics/Model3D.hpp"
#include "../../Content/Assets/ModelAsset.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class RenderingManager;
}

namespace Engine3DRadSpace::Objects
{
	using RefModel3D = Content::AssetID<Content::Assets::ModelAsset>;

	/// <summary>
	/// Represents a 3D mesh in the scene.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT Skinmesh : public IObject3D
	{
		Graphics::Model3D *_model;
		std::unique_ptr<std::string> _path;
		Graphics::Rendering::RenderingManager* _renderingManager = nullptr;
	public:
		/// <summary>
		/// Default constructor for the skinmesh object.
		/// </summary>
		Skinmesh();
		/// <summary>
		/// Constructor for the skinmesh object using an numerical asset reference.
		/// </summary>
		/// <param name="name">The name of the skinmesh object.</param>
		/// <param name="visible">Whether the skinmesh is visible.</param>
		/// <param name="model">The numerical asset reference for the model.</param>
		/// <param name="pos">The position of the skinmesh.</param>
		/// <param name="rot">The rotation of the skinmesh.</param>
		/// <param name="pivot">The pivot point of the skinmesh.</param>
		/// <param name="scale">The scale of the skinmesh.</param>
		Skinmesh(
			const std::string &name,
			bool visible, 
			RefModel3D model,
			const Math::Vector3 &pos = Math::Vector3::Zero(),
			const Math::Quaternion &rot = Math::Quaternion(),
			const Math::Vector3 &pivot = Math::Vector3::Zero(),
			const Math::Vector3 &scale = Math::Vector3::One()
		);
		/// <summary>
		/// Constructor for the skinmesh object using an external model file path.
		/// </summary>
		/// <param name="name">The name of the skinmesh object.</param>
		/// <param name="visible">Whether the skinmesh is visible.</param>
		/// <param name="path">The file path to the external model.</param>
		/// <param name="pos">The position of the skinmesh.</param>
		/// <param name="rot">The rotation of the skinmesh.</param>
		/// <param name="pivot">The pivot point of the skinmesh.</param>
		/// <param name="scale">The scale of the skinmesh.</param>
		Skinmesh(
			const std::string &name,
			bool visible, 
			const std::filesystem::path &path,
			const Math::Vector3 &pos = Math::Vector3::Zero(),
			const Math::Quaternion &rot = Math::Quaternion(),
			const Math::Vector3 &pivot = Math::Vector3::Zero(),
			const Math::Vector3 &scale = Math::Vector3::One()
		);

		Skinmesh(Skinmesh&&) noexcept = default;
		Skinmesh& operator=(Skinmesh&&) noexcept = default;
		/// <summary>
		/// Numerical asset reference for the model associated with this skinmesh.
		/// </summary>
		RefModel3D Model;
		/// <summary>
		/// Gets the underlying mesh.
		/// </summary>
		/// <returns>Unredlying mesh.</returns>
		Graphics::Model3D *GetModel();
		/// <summary>
		/// Initialized the skinmesh object, retrieving necessary services.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Loads the skinmesh model.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Loads the mesh model from the specified file path.
		/// </summary>
		/// <param name="path"></param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Gets the unique identifier for the Skinmesh type.
		/// </summary>
		/// <returns>{C3A243F6-23E2-437F-AE8A-B8E8C2A6E944}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Draws the associated mesh.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Returns the distance from the ray to the mesh. NaN if there is no intersection.
		/// </summary>
		/// <param name="r">The ray to test for intersection.</param>
		/// <returns>The distance from the ray to the mesh, or NaN if there is no intersection.</returns>
		float Intersects(const Math::Ray &r) const override;
		/// <summary>
		/// Returns the associated gizmo for the skinmesh.
		/// </summary>
		/// <returns>The associated gizmo for the skinmesh.</returns>
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		/// <summary>
		/// Does this object emit shadows?
		/// </summary>
		bool HasShadows = true;
		/// <summary>
		/// If true, the skinmesh will be rendered after all opaque objects.
		/// </summary>
		bool Transparent = false;
		/// <summary>
		/// Returns the bounding box of the skinmesh.
		/// </summary>
		/// <returns>The bounding box of the skinmesh.</returns>
		virtual Math::BoundingBox GetBoundingBox() const noexcept override;

		~Skinmesh() override = default;
	};
}

REFL_FWD(Skinmesh)