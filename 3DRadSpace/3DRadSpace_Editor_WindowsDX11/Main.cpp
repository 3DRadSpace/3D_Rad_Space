#define NOMINMAX

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#include <cstdlib>
#include <stacktrace>
#include "Frontend\Windows\EditorWindow.hpp"
#include "Frontend\HelperFunctions.hpp"

#include <PathCch.h>
#pragma comment(lib,"Comctl32.lib")

#include <commctrl.h>
#pragma comment(lib,"Pathcch.lib")

//Enable visual styles
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <dxgi1_3.h>
#include <DXGIDebug.h>
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "dxguid.lib")

#include <Engine3DRadSpace/Logging/Exception.hpp>
#include <Engine3DRadSpace/Logging/Message.hpp>
#include <Engine3DRadSpace/Logging/Warning.hpp>
#include <Engine3DRadSpace/Plugins/EditorPlugin.hpp>
#include <Engine3DRadSpace/Plugins/CustomObject.hpp>
#include <Engine3DRadSpace/Native/LibraryLoader.hpp>
#include <Engine3DRadSpace/Objects/Gizmos.hpp>
#include <Engine3DRadSpace/Objects/Impl/Objects.hpp>
#undef LoadLibrary
#include "Frontend/Settings.hpp"
#include "Editor/SkinmeshPreviewer.hpp"
#include "Frontend/Windows/CrashWindow.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Logging;

void SetWorkingDirectory()
{
	//Sets working directory to the executable's folder.
	wchar_t currentDir[_MAX_PATH]{};
	GetModuleFileNameW(nullptr, currentDir, _MAX_PATH);
	PathCchRemoveFileSpec(currentDir, _MAX_PATH);

	SetCurrentDirectoryW(currentDir);
}

void InitializeCommonControls()
{
	// Load controls such as the progress bar, tree views, list views, etc...
	INITCOMMONCONTROLSEX iccs{};
	iccs.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccs.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&iccs);
}

#ifdef _DEBUG
void ReportLiveObjects()
{
	Microsoft::WRL::ComPtr<IDXGIDebug1> dxgi_debug;
	if(SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgi_debug.GetAddressOf()))))
	{
		dxgi_debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_DETAIL | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
	}
}
#endif

std::vector<void*> plugins;
std::vector<Plugins::PluginInfo> pluginInfos;

void LoadAllPlugins()
{
	std::filesystem::create_directories("Plugins");
	auto dirIterator = std::filesystem::directory_iterator("Plugins");

	//Count .dll files in "./Plugins"
	unsigned numPlugins = 0;
	for (auto const& entry : dirIterator)
	{
		if (entry.path().extension() == ".dll")
		{
			++numPlugins;
		}
	}

	Logging::SetLastMessage(std::format("Found {} plugins:", numPlugins));

	dirIterator = std::filesystem::directory_iterator("Plugins");

	//Load all dll files in "./Plugins"
	for (auto const& entry : dirIterator)
	{
		auto file = entry.path();
		if (file.has_extension() && file.extension() == ".dll")
		{
			auto p = Plugins::LoadPlugin(file);
			std::ignore = p.and_then([](std::pair<Plugins::PluginInfo, void*> plugin) -> decltype(p)
				{
					pluginInfos.push_back(plugin.first);

					auto& [info, handle] = plugin;
					plugins.push_back(handle);

					Logging::SetLastMessage(std::format("Loaded plugin {} ver {} handle 0x{:x}", info.Name, info.Version, reinterpret_cast<intptr_t>(handle)));

					auto numLoadedObjects = Plugins::LoadCustomObjectsFromLibHandle(handle);
					Logging::SetLastMessage(std::format("Loaded {} custom object types from plugin {}", numLoadedObjects, info.Name));

					return plugin;
				}
			).or_else([&file](Plugins::PluginLoadingError err) -> decltype(p)
				{
					std::string msg = "Unknown error";
					switch (err)
					{
					case Plugins::PluginLoadingError::UnableToLoadPluginLibrary:
						msg = "Unable to load library.";
						break;
					case Plugins::PluginLoadingError::NotA3DRadSpacePlugin:
						msg = "Not a 3DRadSpace Plugin!\r\nFunction \"bool PluginMain()\" was not found!";
						break;
					case Plugins::PluginLoadingError::InitializationFunctionFailure:
						msg = "Plugin initialization failed!";
						break;
					default:
						break;
					}

					Logging::SetLastWarning(std::format("Failed to load plugin at {}!\r\n{}", file.string(), msg));
					return std::unexpected(err);
				}
			);
		}
	}
}

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR cmdArgs, _In_ int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance); //hPrevInstance was only used in 16-bit Windows applications.
	UNREFERENCED_PARAMETER(nShowCmd); //The editor windows is maximized anyways.

#ifdef _DEBUG
	std::atexit(ReportLiveObjects); // Lists leaked DX11 objects
#endif

#if _DEBUG
	AllocConsole();

	FILE* fDummy;
	auto r = freopen_s(&fDummy, "CONOUT$", "w", stderr);
	if(r != 0) return -1;
	
	r = freopen_s(&fDummy, "CONOUT$", "w", stdout);
	if(r != 0) return -1;
#endif

	InitializeGDI();
	InitializeCommonControls();
	SetWorkingDirectory();

	if (FAILED(CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED)))
		return -1;

	Internal::LoadDefaultObjects();
	Settings::Load();
	LoadAllPlugins();

	try
	{
		EditorWindow editor(hInstance, cmdArgs);
		editor.Run();
	}
	catch(const std::exception &e)
	{
		std::stacktrace st = std::stacktrace::current();

		CrashWindow crash(GetActiveWindow(), hInstance, e, st);
		crash.ShowDialog();
	}
	catch(...)
	{
		std::runtime_error unknownError("An unknown error occurred.");
		std::stacktrace st = std::stacktrace::current();
		CrashWindow crash(nullptr, hInstance, unknownError, st);
		crash.ShowDialog();
	}

	//unload plugins
	for (auto plugin : plugins)
	{
		auto f = Native::GetFunctionFromLibrary<Plugins::PluginUnload>(plugin, "PluginUnload");
		if (f != nullptr)
		{
			if (!f()) Logging::SetLastMessage(std::format("PluginUnload() returned false! Handle {:x}", reinterpret_cast<intptr_t>(plugin)));
		}
	}
	
	Internal::UnloadGizmos();

	CoUninitialize();
	DeinitializeGDI();
#if _DEBUG
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}