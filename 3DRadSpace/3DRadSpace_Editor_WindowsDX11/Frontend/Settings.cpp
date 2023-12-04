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

void Settings::Load()
{
	nlohmann::json settings;

	std::ifstream jsonFile(GetAppDataFolder() + "Settings.json");
	if (jsonFile.fail() || jsonFile.bad())
	{
		Save();
		return;
	}

	jsonFile >> settings;
	jsonFile.close();

	CameraSensitivity.Value = settings["Editor"]["CameraSensitivity"].get<float>();
	StartupUpdate.Value = settings["Updates"]["StartupUpdate"].get<bool>();
	ShowGrid.Value = settings["Editor"]["ShowGrid"].get<bool>();
}

void Settings::Save()
{
	//Saves the settings into a json file.
	nlohmann::json jsonSettings;
	jsonSettings["Editor"]["CameraSensitivity"] = CameraSensitivity.Value;
	jsonSettings["Updates"]["StartupUpdate"] = StartupUpdate.Value;
	jsonSettings["Editor"]["ShowGrid"] = ShowGrid.Value;

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