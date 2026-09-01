#include "AngelScriptObject.hpp"
#include "AngelscriptWrapper.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Reflection;

using namespace Engine3DRadSpace::Angelscript;

extern std::unique_ptr<AngelScriptWrapper> p_angelscriptWrapper;

AngelScriptObject::AngelScriptObject(const std::string& name, bool enabled, const std::string& source) :
	IObject(name, enabled),
	ScriptPath(source)
{
}

Reflection::UUID AngelScriptObject::GetUUID() const noexcept
{
	// {0F8115D8-8695-4041-BA02-423EAA556D0B}
	return  { 0xf8115d8, 0x8695, 0x4041, { 0xba, 0x2, 0x42, 0x3e, 0xaa, 0x55, 0x6d, 0xb } };
}

Objects::Gizmos::IGizmo* AngelScriptObject::GetGizmo() const noexcept
{
	return nullptr;
}

void AngelScriptObject::Initialize()
{
	p_angelscriptWrapper->Compile(ScriptPath);
}

void AngelScriptObject::Load()
{
}

void AngelScriptObject::Load(const std::filesystem::path& path)
{
	ScriptPath = path.string();
}

void AngelScriptObject::Update()
{

}

REFL_BEGIN(AngelScriptObject, "AngelScript Script", "Scripting", "AngelScript script")
REFL_FIELD(AngelScriptObject, std::string, Name, "Name", "AngelScript script", "Name of the script object")
REFL_FIELD(AngelScriptObject, bool, Enabled, "Enabled", "", "Is the object enabled")
REFL_FIELD(AngelScriptObject, std::string, ScriptPath, "Script path", "", "Path to script file")
REFL_METHOD(AngelScriptObject, void, (&AngelScriptObject::Enable), "Enable")
REFL_METHOD(AngelScriptObject, void, (&AngelScriptObject::Disable), "Disable")
REFL_ATTR("Icon","Data\\Editor\\OBJ_AngelScript.png")
REFL_END