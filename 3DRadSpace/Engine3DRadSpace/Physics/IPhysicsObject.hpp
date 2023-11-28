#pragma once
#include "../IObject3D.hpp"

namespace Engine3DRadSpace::Physics
{
	class DLLEXPORT IPhysicsObject : public IObject3D
	{
	protected:
		explicit IPhysicsObject(const std::string& name = "", const std::string& tag = "", bool enabled = false, bool visible = false, const Math::Vector3& pos = Math::Vector3::Zero(),
								const Math::Vector3& pivot = Math::Vector3::Zero(), const Math::Quaternion& rotation = Math::Quaternion(), const Math::Vector3& scale = Math::Vector3::One());
	public:

		virtual ~IPhysicsObject() = default;
	};
}