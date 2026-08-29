#pragma once
#include "../IScript.hpp"
#include "../../Objects/IObject.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Scripting::CSharp
{
	/// <summary>
	/// A script object handing a AngelScript source.
	/// </summary>
	class __declspec(dllexport) CSharpScript final : public Engine3DRadSpace::Objects::IObject
	{
		int _id = -1;
		bool _initialized = false;
	public:
		explicit CSharpScript(
			const std::string& name = "C# Script",
			bool enabled = true,
			const std::string& src = ""
		);

		std::string ScriptPath;
		std::string Class = "MyClass";

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;

		int GetID() const noexcept;
		bool WasInitialized() const noexcept;

		bool Compile() const;

		~CSharpScript() override;
	};
}

REFL_FWD(CSharpScript)