#pragma once

#define NOMINMAX //WINAPI32 is fucking retarded

#include <windows.h>
#include <d3d11.h>
#include "3DRadSpaceDll/Game.h"
#include "UpdateDownloadManager.h"
#include <cassert>

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

#include <cfloat>
#include <cstdint>
#include "3DRadSpaceDll/Matrix.h"
#include "3DRadSpaceDll/StencilState.h"
#include "3DRadSpaceDll/VertexBuffer.h"

#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

#include <thread>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "comctl32.lib")

#include <pathcch.h>
#pragma comment(lib,"pathcch.lib")

#include "3DRadSpaceDll/Shader.h"