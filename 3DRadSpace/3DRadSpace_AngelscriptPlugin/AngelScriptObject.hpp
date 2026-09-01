#pragma once
#include <Engine3DRadSpace\Objects\IObject.hpp>
#include <Engine3DRadSpace\Reflection\Reflection.hpp>

namespace Engine3DRadSpace::Angelscript
{
	/// <summary>
	/// A script object handing a AngelScript source.
	/// </summary>
	class __declspec(dllexport) AngelScriptObject final : public Engine3DRadSpace::Objects::IObject
	{
	public:
		AngelScriptObject(
			const std::string& name = "AngelScript Script", 
			bool enabled = true,
			const std::string& src = ""
		);

		std::string ScriptPath;

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;

		~AngelScriptObject() override = default;
	};
}

REFL_FWD(AngelScriptObject)