#pragma once
#include <string>
#include <angelscript.h>
#include "AngelScript_AddOns\scriptstdstring.h"

namespace Engine3DRadSpace::Angelscript
{
	class AngelScriptWrapper final
	{
		asIScriptEngine* _engine;
	public:
		AngelScriptWrapper();

		int Compile(const std::string& scriptPath);
		void Call(int scriptHandle, const std::string& fnName);

		~AngelScriptWrapper();
	};
}