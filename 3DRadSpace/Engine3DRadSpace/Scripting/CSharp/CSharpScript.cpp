#include "CSharpScript.hpp"
#include "NETCoreHost.hpp"
#include "../../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Scripting;
using namespace Engine3DRadSpace::Scripting::CSharp;

extern ScriptManager_LoadScript csmgr_loadScript;
extern ScriptManager_UpdateScript csmgr_updateScript;
extern ScriptManager_UnloadScript csmgr_unloadScript;

CSharpScript::CSharpScript(
	const std::string& name,
	bool enabled,
	const std::string& src
)
{
}

Reflection::UUID CSharpScript::GetUUID() const noexcept
{
	// {8B607307-5FF3-4019-9416-493EA100E0B2}
	return { 0x8b607307, 0x5ff3, 0x4019, { 0x94, 0x16, 0x49, 0x3e, 0xa1, 0x0, 0xe0, 0xb2 } };
}

Objects::Gizmos::IGizmo* CSharpScript::GetGizmo() const noexcept
{
	return nullptr;
}

void CSharpScript::Initialize()
{
	if(_initialized) return;

	//If csmgr_loadScript is null, that also means the rest of the other fptrs aren't initialized, so one single check is enough.
	if(csmgr_loadScript == nullptr) throw Logging::Exception("Script manager is improperly initialized!");

	_id = csmgr_loadScript(ScriptPath.c_str(), Class.c_str(), this);
	_initialized = (_id != -1);
}

void CSharpScript::Load()
{
	Load(ScriptPath);
}

void CSharpScript::Load(const std::filesystem::path& path)
{
	ScriptPath = path.string();
	Initialize();
}

void CSharpScript::Update()
{
	csmgr_updateScript(_id);
}

int CSharpScript::GetID() const noexcept
{
	return _id;
}

bool CSharpScript::WasInitialized() const noexcept
{
	return _initialized;
}

CSharpScript::~CSharpScript()
{
	//This check is necessary, as an object is created when this object type is being reflected.
	if(csmgr_unloadScript && _id != -1)
	{
		csmgr_unloadScript(_id);
	}
}

REFL_BEGIN(CSharpScript, "C# Script", "Scripting", "C# script")
REFL_FIELD(CSharpScript, std::string, ScriptPath, "Script path", "", "Path to script file")
REFL_FIELD(CSharpScript, std::string, Class, "Entry classname", "", "Path to script file")
REFL_END