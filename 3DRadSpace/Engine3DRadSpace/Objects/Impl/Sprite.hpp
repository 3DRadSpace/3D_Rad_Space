#pragma once
#include "../IObject2D.hpp"
#include "../../Reflection/Reflection.hpp"
#include "../../Content/Assets/TextureAsset.hpp"
#include "../../Reflection/Event.hpp"

namespace Engine3DRadSpace::Objects
{
	using RefTexture2D = Content::AssetID<Content::Assets::TextureAsset>;

	class E3DRSP_OBJECTS_IMPL_EXPORT Sprite : public IObject2D
	{
		std::unique_ptr<std::string> _tempResourceString;
		void _initEvents();
	protected:
		Graphics::ITexture2D* _texture;
		bool _hover;
		bool _click;
	public:
		Sprite();
		Sprite(
			const std::string &name,
			bool visible,
			const std::string &path, 
			const Math::Vector2& pos,
			const Math::Vector2& scale, 
			float depth = 0.0,
			const Math::Vector2& pivot = Math::Vector2::Zero(),
			float rotation = 0.0f,
			bool flipU = false,
			bool flipV = false,
			const Math::Color& tintColor = Math::Colors::White
		);

		Sprite(
			const std::string &name,
			bool visible,
			RefTexture2D resource, 
			const Math::Vector2 &pos,
			const Math::Vector2& scale,
			float depth = 0.0,
			const Math::Vector2 &pivot = Math::Vector2::Zero(),
			float rotation = 0.0f,
			bool flipU = false,
			bool flipV = false,
			const Math::Color &tintColor = Math::Colors::White
		);

		Sprite(Sprite&&) noexcept = default;
		Sprite& operator=(Sprite&&) noexcept = default;

		bool FlipU;
		bool FlipV;

		RefTexture2D Image;
		Graphics::ITexture2D *GetSpriteImage();
		void SetSpriteImage(Graphics::ITexture2D* texture);

		Math::Color TintColor;
		Math::RectangleF UVCoordinates = Math::RectangleF(0, 0, 1, 1);

		Reflection::Event OnClick;
		Reflection::Event OnMouseEnter;
		Reflection::Event OnMouseLeave;

		bool IsHovered() const noexcept;
		bool IsClicked() const noexcept;
		void ResetInputState() noexcept;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;
		void Draw2D() override;

		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		virtual ~Sprite() = default;
	};
}

REFL_FWD(Sprite)