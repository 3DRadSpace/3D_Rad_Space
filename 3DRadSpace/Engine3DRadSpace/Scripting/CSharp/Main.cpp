#include "CSharpScript.hpp"
#include "NETCoreHost.hpp"
#include "../../FFI/Core/RawSpan.h"
#include "../../Logging/Message.hpp"
#include "../../Logging/Warning.hpp"
#include "../../Logging/Exception.hpp"
#include "../../Plugins/EditorPlugin.hpp"
#include "../../Native/LibraryLoader.hpp"
#include <scintilla/ILexer.h>

//https://github.com/dotnet/samples/blob/main/core/hosting/src/NativeHost/nativehost.cpp

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Native;
using namespace Engine3DRadSpace::Plugins;

extern "C"
{
	__declspec(dllexport) bool PluginMain();
	__declspec(dllexport) bool PluginUnload();
	__declspec(dllexport) PluginInfo LoadPluginInfo();
	__declspec(dllexport) E3DRSP_RawSpan LoadCustomObjects();
}

string_t fxrPath;
extern load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer;

constexpr auto runtimeConfigPath = STR("3DRadSpace_CSharp.runtimeconfig.json");

ScriptManager_LoadScript csmgr_loadScript;
ScriptManager_UpdateScript csmgr_updateScript;
ScriptManager_UnloadScript csmgr_unloadScript;

template<typename Fn>
auto CallCSFunction(
	const char_t* static_class_and_assembly_name,
	const char_t* fnName
) -> std::invoke_result_t<Fn>
{
	Fn fn;

	int r = load_assembly_and_get_function_pointer(
		csharpAssemblyPath,
		static_class_and_assembly_name,
		fnName,
		UNMANAGEDCALLERSONLY_METHOD,
		nullptr,
		reinterpret_cast<void**>(&fn)
	);

	if(r != 0 || fn == nullptr)
	{
		throw Logging::Exception(std::format("{} fn is NULL!", typeid(Fn).name()));
	}

	return fn();
}

template<typename Fn, typename ...Args>
auto CallCSFunction(
	const char_t *static_class_and_assembly_name,
	const char_t *fnName,
	Args&& ...args
) -> std::invoke_result_t<Fn>
{
	Fn fn;

	int r = load_assembly_and_get_function_pointer(
		csharpAssemblyPath,
		static_class_and_assembly_name,
		fnName,
		UNMANAGEDCALLERSONLY_METHOD,
		nullptr,
		reinterpret_cast<void**>(&fn)
	);

	if(r != 0 || fn == nullptr)
	{
		Logging::PrintWarning(std::format("load_assembly_and_get_function_pointer(RTTI {}) failed: rc {:x}", typeid(Fn).name(), r));
		return false;
	}

	fn(std::forward<Args&&>(args)...);
}

template<typename Fn>
Fn LoadCSFunction(const char_t* static_class_and_assembly_name, const char_t* fnName)
{
	Fn fn;

	int r = load_assembly_and_get_function_pointer(
		csharpAssemblyPath,
		static_class_and_assembly_name,
		fnName,
		UNMANAGEDCALLERSONLY_METHOD,
		nullptr,
		reinterpret_cast<void**>(&fn)
	);

	return fn;
}

bool PluginMain()
{
	if (!load_hostfxr())
	{
		Logging::PrintWarning("load_hostfxr() failed!");
		return false;
	}

	if(!std::filesystem::exists(runtimeConfigPath))
	{
		Logging::PrintWarning("C# Runtime config is not found. It should be located at \"<root>\\3DRadSpace_CSharp.runtimeconfig.json\"");
		return false;
	}

	load_assembly_and_get_function_pointer = get_dotnet_load_assembly(runtimeConfigPath);

	if (load_assembly_and_get_function_pointer == nullptr)
	{
		Logging::PrintWarning("get_dotnet_load_assembly() is null!");
		return false;
	}

	CallCSFunction<CsCompiler_InitializeFn>(STR("Engine3DRadSpace.Internal.CsCompiler, 3DRadSpace_CSharp"), STR("Initialize"));
	csmgr_loadScript = LoadCSFunction<ScriptManager_LoadScript>(STR("Engine3DRadSpace.Internal.ScriptManager, 3DRadSpace_CSharp"), STR("LoadScript"));
	csmgr_updateScript = LoadCSFunction<ScriptManager_UpdateScript>(STR("Engine3DRadSpace.Internal.ScriptManager, 3DRadSpace_CSharp"), STR("UpdateScript"));
	csmgr_unloadScript = LoadCSFunction<ScriptManager_UnloadScript>(STR("Engine3DRadSpace.Internal.ScriptManager, 3DRadSpace_CSharp"), STR("UnloadScript"));

	return true;
}

extern Scintilla::ILexer5* cpplexer;

bool PluginUnload()
{
	if (cpplexer != nullptr)
	{
		cpplexer->Release();
		cpplexer = nullptr;
	}
	return true;
}

PluginInfo LoadPluginInfo()
{
	return PluginInfo
	{
		.Name = "3DRadSpace C# Scripting",
		.Version = "0.1.0 Alpha",
		.Author = "3DRadSpace",

		.Description = "Support for C# scripting in 3DRadSpace through C# Script objects",
		.Homepage = "3dradspace.github.io",
		.IconFilename = "CSharp.png"
	};
}

E3DRSP_RawSpan LoadCustomObjects(void)
{
	E3DRSP_RawSpan newObjects =
	{
		.Ptr = &CSharpScriptReflInstance,
		.Size = 1u
	};

	return newObjects;
}