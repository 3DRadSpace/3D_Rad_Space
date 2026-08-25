#pragma once
#include <string>
#include <Engine3DRadSpace/Core/Tag.hpp>
#include <typeindex>
#include <concepts>
#include <Engine3DRadSpace/Core/Concepts.hpp>

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
	static Setting<float> GizmoSensitivity;
	static Setting<bool> PreferArcShot;

	static void Load();
	static void Save();
};

std::string GetAppDataFolder();