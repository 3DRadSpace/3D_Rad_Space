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
		float Mass;

		float LinearDamping;
		float AngularDamping;

		float StaticFriction;
		float DynamicFriction;
		float Restitution;

		Math::Vector3 LinearVelocity;
		Math::Vector3 AngularVelocity;

		Math::Vector3 MaxAngularVelocity;

		/// <summary>
		/// If true, the fields Position, Rotation, Scale, Mass, Damping, Velocity, etc will be set after a Game::Update() call ends.
		/// </summary>
		bool UpdatePropertiesAfterFrame = false;

		enum class PhysicsProperty
		{
			Mass,
			Position,
			Rotation,
			Scale,
			LinearVelocity,
			AngularVelocity,
			MaxAngularVelocity,
			StaticFriction,
			DynamicFriction,
			Restitution,
		};

		/// <summary>
		/// Will apply the chooosen property from the argument. Argument will be read from the class itself. <br/>
		/// For example <c>Apply(PhysicsProperty::Mass)</c> will set the mass to this->Mass.
		/// </summary>
		/// <param name="newSettigs">Selected property</param>
		/// <returns>true if successful.</returns>
		virtual bool Apply(PhysicsProperty newSettigs) = 0;
		virtual bool Read(PhysicsProperty property) = 0;

		virtual bool ApplyForce(const Math::Vector3& force) = 0;
		virtual bool ApplyTorque(const Math::Vector3& force) = 0;

		virtual ~IPhysicsObject() = default;
	};
}