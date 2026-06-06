#pragma once
#include "IPhysicsObject.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	class Force : public IPhysicsObject
	{
		Math::Vector3 _direction = Math::Vector3::Forward();
		float _time = 0;
	public:
		Force(
			const std::string& name = "Force",
			const Math::Vector3& position = Math::Vector3(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			float magnitude = 1,
			float timer = 1.0f,
			bool torque = false
		);

		Force(Force&&) noexcept = default;
		Force& operator=(Force&&) noexcept = default;

		float Magnitude;
		float Timer;
		bool Torque;

		Math::Vector3 Direction() const noexcept;
		Math::Vector3 ForceVector() const noexcept;

		void Enable() override;
		void Disable() override;

		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;
		void Draw3D() override;
		
		float Intersects(const Math::Ray& r) override;
		Reflection::UUID GetUUID() const noexcept override;
		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}

REFL_FWD(Force)