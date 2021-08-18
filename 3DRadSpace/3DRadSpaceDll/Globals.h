#pragma once
#include <typeinfo>
#include <exception>
#include <limits>
#include <string>
#include <fstream>
#include <type_traits>


//By default, in linux all functions are already exported. No other defined needed.
#ifdef WIN32
	#ifdef _MT //MSDN says it is defined when compiling as a DLL
		#define DLLEXPORT  __declspec(dllexport)
	#else
		#define DLLEXPORT __declspec(dllimport)
	#endif //DLL
#endif //WIN32
