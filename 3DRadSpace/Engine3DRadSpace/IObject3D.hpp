#pragma once
#include "IObject.hpp"
#include "Graphics/SpriteBatch.hpp"
#include "IDrawable3D.hpp"

namespace Engine3DRadSpace
{
	class IObject3D : public IObject, public IDrawable3D
	{
	public:
		explicit IObject3D(const std::string &name = "", const std::string &tag = "", bool enabled = false, bool visible = false, const Math::Vector3 &pos = Math::Vector3::Zero(),
			const Math::Vector3 &pivot = Math::Vector3::Zero(), const Math::Quaternion &rotation = Math::Quaternion(), const Math::Vector3 &scale = Math::Vector3::One());

		explicit IObject3D(GraphicsDevice *device, const std::string &name = "", const std::string &tag = "", bool enabled = false, bool visible = false,
			const Math::Vector3 &pos = Math::Vector3::Zero(), const Math::Vector3 &pivot = Math::Vector3::Zero(), const Math::Quaternion &rotation = Math::Quaternion(), 
			const Math::Vector3 &scale = Math::Vector3::One());

		Engine3DRadSpace::Math::Vector3 Position;

		Engine3DRadSpace::Math::Vector3 RotationCenter;
		Engine3DRadSpace::Math::Quaternion Rotation;

		Engine3DRadSpace::Math::Vector3 Scale;

		virtual Engine3DRadSpace::Math::Matrix GetModelMartix();
		virtual void EditorDraw(const Engine3DRadSpace::Math::Matrix &view, const Engine3DRadSpace::Math::Matrix &projection, double dt, bool selected) = 0;

		~IObject3D() = default;
	};
}
