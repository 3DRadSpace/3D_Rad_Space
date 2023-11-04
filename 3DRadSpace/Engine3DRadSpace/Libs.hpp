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
#include <map>
#include <typeindex>

#ifdef _WIN32
#define NOMINMAX
#include <wrl/client.h>

#ifdef _WINDLL 
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT __declspec(dllimport)
#endif

//Check if compiling for DirectX 11/12 or Vulkan.
#ifndef USING_DX11
#ifndef USING_DX12
#ifndef USING_VULKAN
//#warning "Using DirectX11 as default backend."
#define USING_DX11
#endif
#endif // !USING_DX11
#endif

#ifdef USING_DX11
#ifndef _WIN32
#error DirectX11 is only supported on Windows!
#endif // !_WIN32
#endif

#ifdef _DX12
#ifndef _WIN32
#error DirectX12 is only supported on Windows!
#endif // !_WIN32
#endif

#ifdef USING_DX11
#include <d3d11.h>
#include <d3dcompiler.h>
#endif
#else
#define DLLEXPORT
#endif

//Check compiler support
#ifndef __cplusplus
#error A C++ supporting compiler is required!
#endif
