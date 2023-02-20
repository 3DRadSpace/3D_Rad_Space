#pragma once
#include "Matrix.hpp"
#include "IInitializable.hpp"
#include "IUpdateable.hpp"
#include "IDrawable.hpp"

namespace Engine3DRadSpace
{
	class IObject : public IInitiializable, public IUpdateable, public IDrawable
	{
	protected:
		GraphicsDevice* device = nullptr;
	public:
		IObject(std::string name = "Empty", std::string tag = "...", std::string resource = "", bool enabled = false, bool visible = false,
				Engine3DRadSpace::Math::Vector3 pos = {0,0,0}, Engine3DRadSpace::Math::Vector3 rotCenter = {0,0,0}, Engine3DRadSpace::Math::Quaternion rot = {0,0,0,1},
				Engine3DRadSpace::Math::Vector3 scale = {1,1,1});

		std::string Name;
		std::string Tag;
		std::string Resource;
		bool Enabled;
		bool Visible;
		Engine3DRadSpace::Math::Vector3 Position;

		Engine3DRadSpace::Math::Vector3 RotationCenter;
		Engine3DRadSpace::Math::Quaternion Rotation;

		Engine3DRadSpace::Math::Vector3 Scale;

		virtual void EditorDraw(double dt) = 0;
	};
}

