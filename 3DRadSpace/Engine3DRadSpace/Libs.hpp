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

#ifdef _WIN32
#define NOMINMAX
#ifdef _DX11
#include <d3d11.h>
#include <d3dcompiler.h>
#endif
#include <wrl/client.h>
#endif