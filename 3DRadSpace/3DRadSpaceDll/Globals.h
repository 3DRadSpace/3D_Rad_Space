#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <typeinfo>
#include <exception>
#include <limits>
#include <string>
#include <fstream>
#include <type_traits>

//By default, in linux all functions are already exported. No other defined needed.
#ifdef WIN32
	#define NOMINMAX
	#ifdef _MT //MSDN says it is defined when compiling as a DLL
		#define DLLEXPORT  __declspec(dllexport)
		#define DLL_T_EXTERN 
	#else
		#define DLLEXPORT __declspec(dllimport)
		#define DLL_T_EXTERN extern
	#endif //DLL
#endif //WIN32

#include "ResourceCreationException.h"
#include <vector>
#include <unordered_map>
#include <cstdlib>