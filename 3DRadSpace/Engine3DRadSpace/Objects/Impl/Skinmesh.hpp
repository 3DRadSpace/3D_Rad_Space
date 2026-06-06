#pragma once

#include "../IObject3D.hpp"
#include "../../Graphics/Model3D.hpp"
#include "../../Content/Assets/ModelAsset.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	using RefModel3D = Content::AssetID<Content::Assets::ModelAsset>;

	class E3DRSP_OBJECTS_IMPL_EXPORT Skinmesh : public IObject3D
	{
		Graphics::Model3D *_model;
		std::unique_ptr<std::string> _path;
	public:
		Skinmesh();

		Skinmesh(
			const std::string &name,
			bool visible, 
			RefModel3D model,
			const Math::Vector3 &pos = Math::Vector3::Zero(),
			const Math::Quaternion &rot = Math::Quaternion(),
			const Math::Vector3 &pivot = Math::Vector3::Zero(),
			const Math::Vector3 &scale = Math::Vector3::One()
		);

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

		RefModel3D Model;

		Graphics::Model3D *GetModel();

		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		Reflection::UUID GetUUID() const noexcept override;
		void Draw3D() override;
		float Intersects(const Math::Ray &r) override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		bool HasShadows = true;
		/// <summary>
		/// If true, the skinmesh will be rendered after all opaque objects.
		/// </summary>
		bool Transparent = false;

		~Skinmesh() override = default;
	};
}

REFL_FWD(Skinmesh)