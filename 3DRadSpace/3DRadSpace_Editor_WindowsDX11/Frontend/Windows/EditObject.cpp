#include "EditObject.hpp"
#include "..\..\resource.h"
#include <CommCtrl.h>
#include <Engine3DRadSpace/Objects/Impl/Objects.hpp>
#include <psapi.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Reflection;
using namespace Engine3DRadSpace::Objects;

std::unordered_map<std::string, Plugins::ObjectCustomWindow> customWindowFunctions;

void* EditObject(HWND hwnd, HINSTANCE hInstance, void* pRefl, void* pContent, void* pObj)
{
	auto refl = static_cast<ReflectedObject*>(pRefl);
	auto content = static_cast<ContentManager*>(pContent);
	auto obj = static_cast<IObject*>(pObj);

	bool useDefaultWindow = true;
	std::string customWindowFnName;

	for (auto field : *refl)
	{
		if (Attribute* attribute = dynamic_cast<Attribute*>(field); attribute != nullptr)
		{
			if (attribute->FieldName() == "CustomWindow")
			{
				customWindowFnName = attribute->FieldDesc();

				useDefaultWindow = false;
				break;
			}
		}
	}

	if (useDefaultWindow)
	{
		EditObjectDialog dialog(hwnd, hInstance, refl, content);
		return dialog.ShowDialog();
	}
	else
	{
		if (customWindowFunctions.find(customWindowFnName) != customWindowFunctions.end())
		{
			auto customWindowFn = customWindowFunctions[customWindowFnName];
			return customWindowFn(hwnd, hInstance, refl, content, obj);
		}

		std::vector<HMODULE> modules;
		modules.emplace_back(nullptr);

		DWORD neededSize = 0;
		EnumProcessModules(GetCurrentProcess(), modules.data(), sizeof(HMODULE), &neededSize);

		modules.resize(neededSize / sizeof(HMODULE));

		auto r = EnumProcessModules(GetCurrentProcess(), modules.data(), neededSize, &neededSize);

		if (!r) throw std::exception("Failed to enumerate process modules!");

		for (auto module : modules)
		{
			auto customWindowFn = reinterpret_cast<Plugins::ObjectCustomWindow>(GetProcAddress(module, customWindowFnName.c_str()));

			if (customWindowFn != nullptr)
			{
				customWindowFunctions[customWindowFnName] = customWindowFn;
				return customWindowFn(hwnd, hInstance, refl, content, obj);
			}
		}
	}

	throw std::runtime_error("Custom window procedure not found: " + customWindowFnName);
}	