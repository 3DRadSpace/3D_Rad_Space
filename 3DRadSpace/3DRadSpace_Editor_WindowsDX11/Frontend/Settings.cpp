#include "Settings.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <shlobj_core.h>
#include <Windows.h>
#include <Engine3DRadSpace/Logging/Exception.hpp>

Setting<float> Settings::CameraSensitivity =
{
	.Name = "Camera sensitivity",
	.Value = 1.0f
};

Setting<bool> Settings::StartupUpdate =
{
	.Name = "Check for updates at startup",
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

	CameraSensitivity.Value = settings["CameraSensitivity"].get<float>();
	StartupUpdate.Value = settings["StartupUpdate"].get<bool>();
}

void Settings::Save()
{
	//Saves the settings into a json file.
	nlohmann::json jsonSettings;
	jsonSettings["CameraSensitivity"] = CameraSensitivity.Value;
	jsonSettings["StartupUpdate"] = StartupUpdate.Value;

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
	}
	throw std::system_error(std::error_code(static_cast<int>(r), std::system_category()), "Failed to get the appdata folder");
}