#pragma once

#include "../IObject.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// A GForce object is a object that enables physics simulation and specifies the gravity.
	/// </summary>
	class DLLEXPORT GForce : public IObject
	{
	public:
		/// <summary>
		/// Main constructor.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="enabled">Enables physics at startup?</param>
		/// <param name="tag">String tag</param>
		/// <param name="gravity">Gravitatioal acceleration</param>
		GForce(const std::string& name = "GForce", bool enabled = true, const std::string& tag = "", const Math::Vector3& gravity = Math::Vector3(0, -9.81f, 0));

		/// <summary>
		/// World wide gravitation acceleration in m/s^2.
		/// </summary>
		Math::Vector3 Gravity;

		/// <summary>
		/// Requests the Game class to initialize physics.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing. From IObject
		/// </summary>
		/// <param name="keyboard">Not used.</param>
		/// <param name="mouse">Not used.</param>
		/// <param name="dt">Not used.</param>
		void Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt) override;
		/// <summary>
		/// Not used. From IObject
		/// </summary>
		/// <param name="content">Not used.</param>
		void Load(Content::ContentManager* content) override;
		/// <summary>
		/// Not used. From IObject.
		/// </summary>
		/// <param name="content">Not used.</param>
		/// <param name="path">Not used.</param>
		void Load(Content::ContentManager* content, const std::filesystem::path& path);
		/// <summary>
		/// Not used. The editor doesn't use physics at runtime. From IObject.
		/// </summary>
		void EditorInitialize() override;
		/// <summary>
		/// Not used. From IObject.
		/// </summary>
		/// <param name="content">Not used.</param>
		void EditorLoad(Content::ContentManager* content) override;
		/// <summary>
		/// Returns unique identifier used for serialization.
		/// </summary>
		/// <returns></returns>
		Reflection::UUID GetUUID() override;
	};
}

REFL_FWD(GForce)