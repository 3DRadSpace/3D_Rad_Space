#pragma once
#include "Math/Matrix.hpp"
#include "IInitializable.hpp"
#include "IUpdateable.hpp"
#include "IDrawable.hpp"
#include "Reflection/UUID.hpp"

namespace Engine3DRadSpace
{
	class IObject : public IInitiializable, public IUpdateable, public IDrawable
	{
	protected:
		GraphicsDevice* _device = nullptr;
	public:
		IObject(GraphicsDevice* gdev, const std::string &name = "Empty", const std::string &tag = "...", bool enabled = false, bool visible = false,
			Engine3DRadSpace::Math::Vector3 pos = {0,0,0}, Engine3DRadSpace::Math::Vector3 rotCenter = {0,0,0}, Engine3DRadSpace::Math::Quaternion rot = {0,0,0,1},
			Engine3DRadSpace::Math::Vector3 scale = {1,1,1});

		IObject(const std::string &name = "Empty",const std::string &tag = "...", bool enabled = false, bool visible = false,
				Engine3DRadSpace::Math::Vector3 pos = {0,0,0}, Engine3DRadSpace::Math::Vector3 rotCenter = {0,0,0}, Engine3DRadSpace::Math::Quaternion rot = {0,0,0,1},
				Engine3DRadSpace::Math::Vector3 scale = {1,1,1});

		std::string Name;
		std::string Tag;
		bool Enabled;
		bool Visible;
		Engine3DRadSpace::Math::Vector3 Position;

		Engine3DRadSpace::Math::Vector3 RotationCenter;
		Engine3DRadSpace::Math::Quaternion Rotation;

		Engine3DRadSpace::Math::Vector3 Scale;

		virtual Engine3DRadSpace::Math::Matrix GetModelMartix();

		virtual void EditorInitialize() = 0;
		virtual void EditorDraw(const Engine3DRadSpace::Math::Matrix& view, const Engine3DRadSpace::Math::Matrix& projection,double dt) = 0;
		virtual Reflection::UUID GetUUID() = 0;

		GraphicsDevice *GetGraphicsDeviceHandle();
	};
}


