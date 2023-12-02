#pragma once
#include "../IObject2D.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class SkyColor : public IObject2D
	{
	public:
		SkyColor(const std::string& name ="SkyColor", bool enabled = true, const std::string& tag = "", Color color = Colors::Black);

		Color Colour;

		// Inherited via IObject2D
		void Initialize() override;
		void Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt) override;
		void Load(Content::ContentManager* content) override;
		void Load(Content::ContentManager* content, const std::filesystem::path& path) override;
		void EditorInitialize() override;
		void EditorLoad(Content::ContentManager* content) override;
		Reflection::UUID GetUUID() override;

		// Inherited via IObject2D
		void Draw(Graphics::SpriteBatch* spriteBatch, double dt) override;
		void EditorDraw(Graphics::SpriteBatch* spriteBatch, double dt, bool selected) override;
	};
}

REFL_FWD(SkyColor)