#pragma once
#include "../IObject3D.hpp"
#include "Sprite.hpp"
#include "../../Graphics/Primitives/CylindricalBillboard.hpp"
#include "../../Graphics/Primitives/SphericalBillboard.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT SpriteBillboard : public IObject3D
	{
		Graphics::ITexture2D* _texture;
		std::unique_ptr<std::filesystem::path> _tempPath;
		std::unique_ptr<Graphics::Primitives::CylindricalBillboard> _cylindricalBillboard;

		void _createBillboard();
	public:
		SpriteBillboard(
			const std::string& name,
			bool visible,
			const std::filesystem::path& texturePath,
			const Math::Vector3& pos,
			const Math::Vector3& axis,
			bool spherical
		);

		SpriteBillboard(
			const std::string& name = "SpriteBillboard",
			bool visible = true,
			RefTexture2D resource = 0,
			const Math::Vector3& pos = Math::Vector3::Zero(),
			const Math::Vector3& axis = Math::Vector3(0, 1, 0),
			bool spherical = false
		);

		RefTexture2D Texture;
		bool IsSpherical = false;

		Graphics::ITexture2D* GetSpriteImage();
		void SetSpriteImage(Graphics::ITexture2D* texture);

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;
		
		void Draw3D() override;
		float Intersects(const Math::Ray& r) override;

		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		~SpriteBillboard() override = default;
	};
}

REFL_FWD(SpriteBillboard);