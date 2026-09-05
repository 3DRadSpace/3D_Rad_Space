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
		int64_t _scriptHandle = -1;
	public:
		AngelScriptObject();

		AngelScriptObject(
			const std::string& name,
			bool enabled,
			const std::filesystem::path& scriptFilename
		);

		AngelScriptObject(
			const std::string& name,
			bool enabled,
			const std::string_view& scriptSource
		);

		AngelScriptObject(AngelScriptObject&&) noexcept;
		AngelScriptObject& operator=(AngelScriptObject&&) noexcept;

		std::filesystem::path ScriptPath;

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;

		int GetHandle() const noexcept;
		bool TryCompile(std::string& err);

		~AngelScriptObject() override;
	};
}

REFL_FWD(AngelScriptObject)