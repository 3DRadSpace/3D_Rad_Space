#pragma once

#include "../IObject.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// A GForce object is a object that enables physics simulation and specifies the gravity.
	/// </summary>
	class GForce : public IObject
	{
	public:
		GForce(const std::string& name = "GForce", bool enabled = true, const std::string& tag = "", const Math::Vector3& gravity = Math::Vector3(0, -9.81f, 0));

		Math::Vector3 Gravity;

		// Inherited via IObject
		void Initialize() override;
		void Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt) override;
		void Load(Content::ContentManager* content) override;
		void EditorInitialize() override;
		void EditorLoad(Content::ContentManager* content) override;
		Reflection::UUID GetUUID() override;
	};
}

REFL_FWD(GForce)