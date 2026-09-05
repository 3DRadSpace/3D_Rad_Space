#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <angelscript.h>
#include "AngelScript_AddOns\scriptstdstring.h"

namespace Engine3DRadSpace::Angelscript
{
	class AngelScriptWrapper final
	{
		asIScriptEngine* _engine;
		asIScriptContext* _context;

		struct ScriptModule
		{
			size_t Handle;
			std::string Name;
			asIScriptModule* Module;
			asIScriptFunction* MainFunction;
			asIScriptFunction* InitializeFunction;
			asIScriptFunction* DeinitializeFunction;
		};

		std::vector<ScriptModule> _scriptModules;
	public:
		AngelScriptWrapper();

		int Compile(const std::filesystem::path& scriptPath);
		void Call(size_t scriptHandle, const std::string& fnName);

		enum class FunctionID
		{
			Main,
			Initialize,
			Deinitialize
		};

		void Call(size_t scriptHandle, FunctionID functionID = FunctionID::Main);

		asIScriptEngine* GetEngine() const noexcept;

		~AngelScriptWrapper();
	};
}