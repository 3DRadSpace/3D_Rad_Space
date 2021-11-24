#include "CppScript.h"

Engine3DRadSpace::CppScript::CppScript(const char* modulepath, Game* game)
{
	this->_loaded = false;
	this->_createInstance = nullptr;
	this->scriptInstance = nullptr;

	this->_module = LoadLibraryA(modulepath);
	if (this->_module != nullptr)
	{
		this->_createInstance = (fptrGetScriptInstance)GetProcAddress(this->_module, "CreateScriptInstance");
		if (this->_createInstance)
		{
			this->scriptInstance = this->_createInstance();

			if (this->_createInstance != nullptr)
				this->_loaded = true;
			else
				throw std::runtime_error("CreateScriptInstance function call failed!");
		}
	}
}

bool Engine3DRadSpace::CppScript::IsLoaded()
{
	return this->_loaded;
}

void Engine3DRadSpace::CppScript::CallDraw(float dt)
{
	if (this->_loaded)
	{
		this->scriptInstance->Draw(dt);
	}
}

void Engine3DRadSpace::CppScript::CallUpdate(float dt)
{
	if (this->_loaded)
	{
		this->scriptInstance->Update(dt);
	}
}

void Engine3DRadSpace::CppScript::CallEnd()
{
	if (this->_loaded)
	{
		this->scriptInstance->End();
	}
}

Engine3DRadSpace::CppScript::~CppScript()
{
	FreeLibrary(this->_module);
}
