#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <typeinfo>
#include <exception>
#include <limits>
#include <string>
#include <fstream>
#include <type_traits>

//By default, in linux all functions are already exported. No other defined needed.
#ifdef _WIN32 //If we are compiling on Windows
	#define NOMINMAX
	#ifdef _DLL //If we are compiling as a DLL
		#define DLLEXPORT  __declspec(dllexport)
	#else //If we are using the headers inside a project
		#define DLLEXPORT __declspec(dllimport)
	#endif //DLL
#endif //WIN32 (both x64 and x86)

#ifdef __linux__
	#define DLLEXPORT
#endif

#include "ResourceCreationException.h"
#include <vector>
#include <unordered_map>
#include <cstdlib>