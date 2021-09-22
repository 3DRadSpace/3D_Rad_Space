#pragma once
#include "Game.h"
#include "IScript.h"

#ifdef WIN32
#ifdef __DIRECTXVER

#include <Windows.h>

typedef IScript* (*fptrGetScriptInstance)();

class CppScript
{
	HMODULE _module;
	bool _loaded;
	fptrGetScriptInstance _createInstance;
	IScript* scriptInstance;

public:
	CppScript(const char* modulepath,Game *game);

	bool IsLoaded();

	void CallDraw(float dt);
	void CallUpdate(float dt);
	void CallEnd();

	~CppScript();
};

#endif
#endif
