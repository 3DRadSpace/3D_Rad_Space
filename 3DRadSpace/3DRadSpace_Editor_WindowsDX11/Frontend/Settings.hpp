#pragma once
#include <string>

template<typename T>
struct Setting
{
	std::string Name;
	T Value;
};

class Settings
{
public:
	static Setting<float> CameraSensitivity;
	static Setting<bool> StartupUpdate;

	static void Load();
	static void Save();
};

std::string GetAppDataFolder();