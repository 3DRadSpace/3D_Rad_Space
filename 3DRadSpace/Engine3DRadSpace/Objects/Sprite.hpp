#pragma once
#include "../IObject.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class Sprite : public IObject
	{
		Graphics::Texture2D *_texture;
	public:
		Sprite();
		Sprite(const std::string &name, bool visible, const std::string &path, const Vector2 &pos, const Vector2& scale, float depth = 0.0,
			float rotation = 0.0f, bool flipU = false, bool flipV = false);

		Sprite(const std::string &name, bool visible, Reflection::RefTexture2D resource, const Vector2 &pos, const Vector2& scale, float depth = 0.0, 
			float rotation = 0.0f, bool flipU = false, bool flipV = false);

		bool FlipU;
		bool FlipV;

		Reflection::RefTexture2D Image;

		virtual void Initialize() override;
		virtual void Update(Input::Keyboard &keyboard, Input::Mouse &mouse, double dt) override;
		virtual void Draw(Engine3DRadSpace::Math::Matrix &view, Engine3DRadSpace::Math::Matrix &projection, double dt) override;
		virtual void EditorInitialize() override;
		virtual void EditorDraw(const Engine3DRadSpace::Math::Matrix &view, const Engine3DRadSpace::Math::Matrix &projection, double dt) override;
		virtual Reflection::UUID GetUUID() override;
	};
}

REFL_DEF(Sprite)