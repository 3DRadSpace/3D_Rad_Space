#pragma once
#include "../IObject3D.hpp"
#include "Sprite.hpp"
#include "../../Graphics/Primitives/CylindricalBillboard.hpp"
#include "../../Graphics/Primitives/SphericalBillboard.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a 2D sprite rendered in 3D space that always faces the camera, either fully (spherical) or around a fixed axis (cylindrical).
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT SpriteBillboard : public IObject3D
	{
		Graphics::ITexture2D* _texture;
		std::unique_ptr<std::filesystem::path> _tempPath;
		std::unique_ptr<Graphics::Primitives::CylindricalBillboard> _cylindricalBillboard;

		void _createBillboard();
	public:
		/// <summary>
		/// Constructs a sprite billboard from a file path.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="visible">Is this object visible?</param>
		/// <param name="texturePath">File path to the texture</param>
		/// <param name="pos">Position of the billboard</param>
		/// <param name="axis">Axis around which the billboard rotates when cylindrical</param>
		/// <param name="spherical">True for a spherical billboard, false for a cylindrical billboard</param>
		SpriteBillboard(
			const std::string& name,
			bool visible,
			const std::filesystem::path& texturePath,
			const Math::Vector3& pos,
			const Math::Vector3& axis,
			bool spherical
		);

		/// <summary>
		/// Constructs a sprite billboard from a numerical asset identifier.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="visible">Is this object visible?</param>
		/// <param name="resource">Numerical asset identifier for the texture</param>
		/// <param name="pos">Position of the billboard</param>
		/// <param name="axis">Axis around which the billboard rotates when cylindrical</param>
		/// <param name="spherical">True for a spherical billboard, false for a cylindrical billboard</param>
		explicit SpriteBillboard(
			const std::string& name = "SpriteBillboard",
			bool visible = true,
			RefTexture2D resource = 0,
			const Math::Vector3& pos = Math::Vector3::Zero(),
			const Math::Vector3& axis = Math::Vector3(0, 1, 0),
			bool spherical = false
		);

		/// <summary>
		/// Numerical reference to the texture asset used by this object.
		/// </summary>
		RefTexture2D Texture;
		/// <summary>
		/// Whether the billboard is spherical (faces the camera fully) or cylindrical (rotates only around the specified axis).
		/// </summary>
		bool IsSpherical = false;

		/// <summary>
		/// Gets the underlying texture used by this billboard.
		/// </summary>
		/// <returns>Pointer to the underlying texture</returns>
		Graphics::ITexture2D* GetSpriteImage();
		/// <summary>
		/// Sets the underlying texture used by this billboard.
		/// </summary>
		/// <param name="texture">Pointer to the texture</param>
		void SetSpriteImage(Graphics::ITexture2D* texture);

		/// <summary>
		/// Loads the texture asset and creates the billboard primitive.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Loads the texture asset.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Loads a texture from a specified path.
		/// </summary>
		/// <param name="path">Image file</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Update() override;

		/// <summary>
		/// Draws the billboard.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Tests for intersections with the billboard.
		/// </summary>
		/// <param name="r">Ray to test against</param>
		/// <returns>Distance to the intersection point, or a negative value if there is no intersection</returns>
		float Intersects(const Math::Ray& r) const override;

		/// <summary>
		/// Gets the UUID of the SpriteBillboard type.
		/// </summary>
		/// <returns>{C083D382-86D9-40A0-AFCC-16109C9B0C35}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Gets the associated gizmo that allows rendering.
		/// </summary>
		/// <returns>GizmoOf&lt;SpriteBillboard&gt;</returns>
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		~SpriteBillboard() override = default;
	};
}

REFL_FWD(SpriteBillboard);