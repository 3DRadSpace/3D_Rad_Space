#include "CppScript.h"

CppScript::CppScript(const char* modulepath, Game* game)
{
	this->_loaded = false;
	this->_createInstance = nullptr;
	this->scriptInstance = nullptr;

	this->_module = LoadLibraryA(modulepath);
	if (this->_module != nullptr)
	{
		this->_createInstance = (fptrGetScriptInstance)GetProcAddress(this->_module, "CreateScriptInstance");
		if (this->_createInstance) this->_loaded = true;
	}
}

bool CppScript::IsLoaded()
{
	return this->_loaded;
}

void CppScript::CallDraw(float dt)
{
	if (this->_loaded)
	{
		this->scriptInstance->Draw(dt);
	}
}

void CppScript::CallUpdate(float dt)
{
	if (this->_loaded)
	{
		this->scriptInstance->Update(dt);
	}
}

void CppScript::CallEnd()
{
	if (this->_loaded)
	{
		this->scriptInstance->End();
	}
}

CppScript::~CppScript()
{
	FreeLibrary(this->_module);
}
