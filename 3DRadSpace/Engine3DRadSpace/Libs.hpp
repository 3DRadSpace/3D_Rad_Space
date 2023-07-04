#pragma once

#include <cstdint>
#include <memory>
#include <exception>
#include <stdexcept>
#include <span>
#include <sal.h>
#include <array>
#include <format>
#include <span>
#include <chrono>
#include <numbers>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <filesystem>
#include <set>
#include <variant>
#include <any>

#ifdef _WIN32
#define NOMINMAX
#include <wrl/client.h>

#ifdef _WINDLL 
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT __declspec(dllimport)
#endif

#ifdef _DX11
	#include <d3d11.h>
	#include <d3dcompiler.h>
#endif
#else
#define DLLEXPORT
#endif