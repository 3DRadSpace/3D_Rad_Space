#pragma once
#include "../IObject3D.hpp"
#include "../../Content/Assets/SkyboxAsset.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects 
{
	using RefSkybox = Content::AssetID<Content::Assets::SkyboxAsset>;
	/// <summary>
	/// Represents a skybox object in the 3D scene.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT Skybox : public IObject3D
	{
		Content::Assets::SkyboxAsset *_skybox;
		std::unique_ptr<std::string> _path;
	public:
		/// <summary>
		/// Skybox constructor using an numerical asset idenfitier.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="visible">Is this object visible?</param>
		/// <param name="skybox">Numerical asset identifier for the skybox</param>
		explicit Skybox(
			const std::string& name = "Skybox",
			bool visible = false,
			RefSkybox skybox = 0
		);
		/// <summary>
		/// Skybox constructor using a file path to load the skybox asset.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="visible">Is this object visible?</param>
		/// <param name="path">File path to the skybox asset</param>
		Skybox(
			const std::string& name,
			bool visible,
			const std::filesystem::path& path
		);

		Skybox(Skybox&&) noexcept = default;
		Skybox& operator=(Skybox&&) noexcept = default;
		/// <summary>
		///	Numerical reference to the skybox asset used by this object.
		/// </summary>
		RefSkybox SkyboxID;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Loads the skybox asset.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Loads an alternate skybox asset from the specified path.
		/// </summary>
		/// <param name="path"></param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Gets the UUID for the Skybox class.
		/// </summary>
		/// <returns>{E29253F1-2053-4752-ADBF-236AA6A0039E}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		///	Draws the associated skybox.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Returns NaN.
		/// </summary>
		/// <param name="r">unused</param>
		/// <returns>NaN</returns>
		float Intersects(const Math::Ray& r) const override;
		/// <summary>
		/// Returns the associated gizmo.
		/// </summary>
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		~Skybox() override = default;
	};
}

REFL_FWD(Skybox)