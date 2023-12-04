#pragma once
#include <string>
#include <Engine3DRadSpace/Tag.hpp>
#include <typeindex>
#include <concepts>
#include <Engine3DRadSpace/Concepts.hpp>

template<typename T>
struct Setting
{
	std::string Category;
	std::string Name;
	T Value;
};

template<>
struct Setting<float>
{
	std::string Category;
	std::string Name;
	
	float Min;
	float Value;
	float Max;
};

class Settings
{
public:
	static Setting<float> CameraSensitivity;
	static Setting<bool> StartupUpdate;
	static Setting<bool> ShowGrid;

	static void Load();
	static void Save();
};

std::string GetAppDataFolder();