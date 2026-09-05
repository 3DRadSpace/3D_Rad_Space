#include "AngelScriptObject.hpp"
#include "AngelscriptWrapper.hpp"
#include <Engine3DRadSpace/Logging/Warning.hpp>
#include "Legacy.hpp"
#include <Engine3DRadSpace/Games/Game.hpp>
#include <filesystem>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Reflection;

using namespace Engine3DRadSpace::Angelscript;

extern std::unique_ptr<AngelScriptWrapper> p_angelscriptWrapper;

AngelScriptObject::AngelScriptObject() :
	IObject("AngelScript Script", true),
	ScriptPath()
{
	Legacy::SetObjectList(GetGame()->RequireService<Engine3DRadSpace::Objects::ObjectList>({}));
	Legacy::SetProjectPath(static_cast<Game*>(GetGame())->GetCurrentScene());
}

AngelScriptObject::AngelScriptObject(const std::string& name, bool enabled, const std::filesystem::path& source) :
	IObject(name, enabled),
	ScriptPath(source)
{
}

AngelScriptObject::AngelScriptObject(const std::string& name, bool enabled, const std::string_view& source) :
	IObject(name, enabled),
	ScriptPath()
{
	std::filesystem::path tempPath = std::filesystem::temp_directory_path() / (name + ".as");
	std::ofstream file(tempPath);
	file << source;
	file.close();
	ScriptPath = tempPath;
}

AngelScriptObject::AngelScriptObject(AngelScriptObject&& other) noexcept :
	IObject(std::move(other)),
	ScriptPath(std::move(other.ScriptPath)),
	_scriptHandle(other._scriptHandle)
{
	other._scriptHandle = -1;
}

AngelScriptObject& AngelScriptObject::operator=(AngelScriptObject&& other) noexcept
{
	if (this != &other)
	{
		IObject::operator=(std::move(other));
		ScriptPath = std::move(other.ScriptPath);
		_scriptHandle = other._scriptHandle;
		other._scriptHandle = -1;
	}
	return *this;
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
	std::string err;
	bool b = TryCompile(err);
	if (!b)
	{
		Logging::PrintWarning(std::format("Failed to compile AngelScript script '{}': {}", ScriptPath.string(), err));
		return;
	}

	p_angelscriptWrapper->Call(_scriptHandle, AngelScriptWrapper::FunctionID::Initialize);
	p_angelscriptWrapper->Call(_scriptHandle, AngelScriptWrapper::FunctionID::Main);
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
	p_angelscriptWrapper->Call(_scriptHandle, AngelScriptWrapper::FunctionID::Main);
}

bool AngelScriptObject::TryCompile(std::string& err)
{
	if (!std::filesystem::exists(ScriptPath))
	{
		err = "Script file does not exist.";
		return false;
	}
	int handle = p_angelscriptWrapper->Compile(ScriptPath);
	if (handle < 0)
	{
		err = "Failed to compile script.";
		return false;
	}
	_scriptHandle = handle;
	return true;
}

AngelScriptObject::~AngelScriptObject()
{
	if (_scriptHandle >= 0)
	{
		p_angelscriptWrapper->Call(_scriptHandle, AngelScriptWrapper::FunctionID::Deinitialize);
		p_angelscriptWrapper->Call(_scriptHandle, AngelScriptWrapper::FunctionID::Main);
	}
}

REFL_BEGIN(AngelScriptObject, "AngelScript Script", "Scripting", "AngelScript script")
REFL_FIELD(AngelScriptObject, std::string, Name, "Name", "AngelScript script", "Name of the script object")
REFL_FIELD(AngelScriptObject, bool, Enabled, "Enabled", "", "Is the object enabled")
REFL_FIELD(AngelScriptObject, std::string, ScriptPath, "Script path", "", "Path to script file")
REFL_METHOD(AngelScriptObject, void, (&AngelScriptObject::Enable), "Enable")
REFL_METHOD(AngelScriptObject, void, (&AngelScriptObject::Disable), "Disable")
REFL_ATTR("Icon","Data\\Editor\\OBJ_AngelScript.png")
REFL_END