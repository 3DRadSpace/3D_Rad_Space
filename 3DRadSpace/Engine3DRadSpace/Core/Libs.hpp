#pragma once

#pragma region STL imports
#include <cstdint>
#include <memory>
#include <exception>
#include <stdexcept>
#include <span>
#include <array>
#include <format>
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
#include <cassert>
#include <ranges>
#include <random>
#include <fstream>
#include <expected>
#include <concepts>
#include <typeinfo>
#include <stacktrace>
#pragma endregion

#pragma region WIN32 imports
#ifdef _WIN32
#define NOMINMAX
#include <wrl/client.h>
#include <sal.h>
#endif
#pragma endregion

#pragma region Other defines
#if _DEBUG
#define _DISABLE_VECTOR_ANNOTATION
#endif 
#pragma endregion

#include "Libs.h"

#pragma region Typedefs and usings
using STD_UPtrTypeless = std::unique_ptr<void, std::function<void(void*)>>;
#pragma endregion