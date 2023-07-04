#pragma once
#include "../IObject2D.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class DLLEXPORT Sprite : public IObject2D
	{
		Graphics::Texture2D *_texture;
		std::unique_ptr<std::string> _tempResourceString;
	public:
		Sprite();
		Sprite(const std::string &name, bool visible, const std::string &path, const Math::Vector2 &pos, const Math::Vector2& scale, 
			const Math::Vector2& pivot = Math::Vector2::Zero(), float depth = 0.0,
			float rotation = 0.0f, bool flipU = false, bool flipV = false, const Color &tintColor = Colors::White);

		Sprite(const std::string &name, bool visible, Reflection::RefTexture2D resource, const Math::Vector2 &pos, const Math::Vector2& scale, float depth = 0.0, 
			const Math::Vector2 &pivot = Math::Vector2::Zero(), float rotation = 0.0f, bool flipU = false, bool flipV = false,
			const Color &tintColor = Colors::White);

		bool FlipU;
		bool FlipV;

		Reflection::RefTexture2D Image;
		Engine3DRadSpace::Graphics::Texture2D *GetSpriteImage();

		Color TintColor;

		virtual void Initialize() override;
		virtual void Load(Content::ContentManager *content) override;
		virtual void Update(Input::Keyboard &keyboard, Input::Mouse &mouse, double dt) override;
		virtual void Draw(Graphics::SpriteBatch *spriteBatch, double dt) override;

		virtual void EditorInitialize() override;
		virtual void EditorLoad(Content::ContentManager *content) override;
		virtual void EditorDraw(Graphics::SpriteBatch *spriteBatch, double dt, bool selected) override;
		virtual Reflection::UUID GetUUID() override;

		virtual ~Sprite() = default;
	};
}

REFL_DEF(Sprite)