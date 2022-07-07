#pragma once

#define NOMINMAX //WINAPI32 is fucking retarded

#include <Windows.h>
#include <d3d11.h>
#include "Game.hpp"
#include <cassert>

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

#include <cfloat>
#include <cstdint>
#include "Matrix.hpp"
#include "StencilState.hpp"
#include "VertexBuffer.hpp"

#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

#include <thread>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "comctl32.lib")

#include <pathcch.h>
#pragma comment(lib,"pathcch.lib")

#include "Shader.hpp"
#include "SamplerState.hpp"
#include "RasterizerState.hpp"
#include "Viewport.hpp"
#include "Camera.hpp"
#include "Maths.hpp"

#include <Mouse.h>
#include <dxgidebug.h>
#include <discord_rpc.h>

#pragma warning(push)
#pragma warning(disable : 26812)
#include <Keyboard.h>
#include <Model.h>
#pragma warning(pop)

#include <DirectXMath.h>
#include <Effects.h>
#include <CommonStates.h>
#include <chrono>
#include <dxgi1_3.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <DirectXHelpers.h>

#pragma comment(lib,"DXGI.lib")

#ifdef UNICODE
#define __stdstring std::wstring
#define __rawstring wchar_t*
#define __to_stdstring std::to_wstring
#define __char wchar_t
#define __rawstrlen wcslen
#else
#define __stdstring std::string
#define __rawstring char*
#define __to_stdstring std::to_string
#define __char char
#define __rawstrlen strlen
#endif

#include <CommCtrl.h>
#include <variant>
#include <array>
#include <span>
//#define __cpp_lib_format
#include <format> //std::format (C++ 20)
#include <functional>
#include <numbers>