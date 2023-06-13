#pragma once
#include "IObject.hpp"
#include "IDrawable2D.hpp"

namespace Engine3DRadSpace
{
	class IObject2D : public IObject, public IDrawable2D
	{
	public:
		IObject2D(const std::string& name = "", const std::string &tag = "...", bool enabled = false, bool visible = false, const Math::Vector2 &pos = Math::Vector2::Zero(),
			const Math::Vector2 &scale = Math::Vector2(0.1f,0.1f), float rotation = 0.0f, const Math::Vector2 &pivot = Math::Vector2::Zero(), float depth = 0.0f);

		explicit IObject2D(GraphicsDevice *device, const std::string &name = "", const std::string &tag = "...", bool enabled = false, bool visible = false,
			const Math::Vector2 &pos = Math::Vector2::Zero(), const Math::Vector2 &scale = Math::Vector2(0.1f, 0.1f), float rotation = 0.0f,
			const Math::Vector2 &pivot = Math::Vector2::Zero(), float depth = 0.0f);

		Math::Vector2 Position;
		Math::Vector2 RotationCenter;
		Math::Vector2 Scale;
		float Depth;
		float Rotation;

		virtual void EditorDraw(Graphics::SpriteBatch *spriteBatch, double dt, bool selected) = 0;
	};
}