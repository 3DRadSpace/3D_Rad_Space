#include "Directory.hpp"
#include  <Windows.h>
#include <PathCch.h>
#pragma comment(lib,"Pathcch.lib")

void Engine3DRadSpace::Native::SetDefaultWorkingDirectory()
{
	//Sets working directory to the executable's folder.
	wchar_t currentDir[_MAX_PATH]{};
	GetModuleFileNameW(nullptr, currentDir, _MAX_PATH);
	PathCchRemoveFileSpec(currentDir, _MAX_PATH);

	SetCurrentDirectoryW(currentDir);
}