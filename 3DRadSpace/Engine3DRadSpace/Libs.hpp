#pragma once

#include <cstdint>
#include <memory>
#include <exception>
#include <stdexcept>

#ifdef _WIN32
#ifdef _DX11
#include <d3d11.h>
#include <d3dcompiler.h>
#endif
#include <wrl/client.h>
#endif