#include "Settings.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <shlobj_core.h>
#include <Windows.h>
#include <Engine3DRadSpace/Logging/Exception.hpp>

Setting<float> Settings::CameraSensitivity =
{
	.Name = "Camera sensitivity",
	.Min = 0.1f,
	.Value = 5.0f,
	.Max = 20.0f
};

Setting<bool> Settings::StartupUpdate =
{
	.Name = "Check for updates at startup",
	.Value = true
};

Setting<bool> Settings::ShowGrid
{
	.Name = "Show grid",
	.Value = true
};

Setting<float> Settings::GizmoSensitivity =
{
	.Name = "Gizmo sensitivity",
	.Min = 0.1f,
	.Value = 1.0f,
	.Max = 20.0f
};

Setting<bool> Settings::PreferArcShot =
{
	.Name = "Prefer Arc shot camera",
	.Value = true
};

template<typename Fn, typename ...Args>
void try_emptycatch(Fn&& fn, Args&& ...args)
{
	try
	{
		fn(std::forward<Args>(args)...);
	}
	catch(...)
	{
	}
}

void Settings::Load()
{
	nlohmann::json settings;

	std::ifstream jsonFile(GetAppDataFolder() + "Settings.json");
	if (jsonFile.fail() || jsonFile.bad())
	{
		Save();
		return;
	}

	try
	{
		jsonFile >> settings;
		jsonFile.close();
	}
	catch(...)
	{
		Save();
		return;
	}

	try_emptycatch([&]() {CameraSensitivity.Value = settings["Editor"]["CameraSensitivity"].get<float>(); });
	try_emptycatch([&]() {StartupUpdate.Value = settings["Updates"]["StartupUpdate"].get<bool>(); });
	try_emptycatch([&]() {ShowGrid.Value = settings["Editor"]["ShowGrid"].get<bool>(); });
	try_emptycatch([&]() {GizmoSensitivity.Value = settings["Editor"]["GizmoSensitivity"].get<float>(); });
	try_emptycatch([&]() {PreferArcShot.Value = settings["Editor"]["PreferArcShot"].get<bool>(); });
}

void Settings::Save()
{
	//Saves the settings into a json file.
	nlohmann::json jsonSettings;

	jsonSettings["Editor"]["CameraSensitivity"] = CameraSensitivity.Value;
	jsonSettings["Updates"]["StartupUpdate"] = StartupUpdate.Value;
	jsonSettings["Editor"]["ShowGrid"] = ShowGrid.Value;
	jsonSettings["Editor"]["GizmoSensitivity"] = GizmoSensitivity.Value;
	jsonSettings["Editor"]["PreferArcShot"] = PreferArcShot.Value;

	std::ofstream jsonFile(GetAppDataFolder() + "Settings.json");
	jsonFile << std::setw(4) << jsonSettings;
}

std::string GetAppDataFolder()
{
	char appdataPath[_MAX_PATH] = {};
	HRESULT r;
	if (SUCCEEDED(r = SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, appdataPath)))
	{
		std::string result = std::string(appdataPath) + "\\3DRadSpace\\";
		return result;
	}
	throw std::system_error(std::error_code(static_cast<int>(r), std::system_category()), "Failed to get the appdata folder");
}