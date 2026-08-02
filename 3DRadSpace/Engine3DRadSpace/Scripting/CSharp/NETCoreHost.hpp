#pragma once
#include "../../Core/Libs.hpp"
#include <nethost.h>
#include <hostfxr.h>
#include <coreclr_delegates.h>

using string_t = std::basic_string<char_t>;

#define STR(s) L ## s

typedef void (*CsCompiler_InitializeFn)();

typedef int (*ScriptManager_LoadScript)(const char* scriptPath, const char* fnName, const void* ownerObject);
typedef bool (*ScriptManager_UpdateScript)(int scriptID);
typedef void (*ScriptManager_UnloadScript)(int scriptID);
typedef bool (*ScriptManager_CompileScript)(const char* scriptPath, const char* className);

constexpr auto csharpAssemblyPath = STR("3DRadSpace_CSharp.dll");

bool load_hostfxr();
load_assembly_and_get_function_pointer_fn get_dotnet_load_assembly(const char_t* config_path);