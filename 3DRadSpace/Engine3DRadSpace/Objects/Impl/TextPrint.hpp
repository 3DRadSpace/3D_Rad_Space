#pragma once
#include "../IObject2D.hpp"
#include "../../Graphics/Font.hpp"
#include "../../Content/AssetID.hpp"
#include "../../Reflection/Reflection.hpp"
#include "../../Content/Assets/FontAsset.hpp"

namespace Engine3DRadSpace::Objects
{ 
	using RefFont = Content::AssetID<Content::Assets::FontAsset>;

	class E3DRSP_OBJECTS_IMPL_EXPORT TextPrint : public IObject2D
	{
	private:
		Graphics::Font* _font = nullptr;
		std::unique_ptr<std::string> _path;
	public:
		TextPrint();
		TextPrint(
			const std::string& name, 
			bool visible,
			RefFont font,
			const std::string& text,
			const Math::Vector2& pos,
			float rotation,
			float scale, 
			Math::Color color, 
			float depth
		);
		TextPrint(
			const std::string& name,
			bool visible,
			const std::filesystem::path &font, 
			const std::string& text,
			const Math::Vector2& pos,
			float rotation,
			float scale,
			Math::Color color,
			float depth
		);

		RefFont Font = 0;
		Math::Color Colour;
		std::string Text;

		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		Reflection::UUID GetUUID() const noexcept override;
		void Draw2D() override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;
		
		Graphics::Font* GetFont() const noexcept;
	};
}

REFL_FWD(TextPrint)