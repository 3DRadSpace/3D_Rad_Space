#pragma once
#include <Windows.h>
#include "RenderWindow.hpp"

constexpr const char* EditorWindowClassName = "CLASS_3DRADSPACE_MAINWINDOW";
constexpr const char* RecentProjectFile = "Data\\RecentProjects.txt";
constexpr const char* FileFilter = "3DRadSpace Project(*.3drsp)\0*.3drsp\0All Files(*.*)\0*.*\0\0";

constexpr int CMD_NewFile = 500;
constexpr int CMD_OpenFile = 501;

constexpr int CMD_OpenRecentFile1 = 502; // 1 -> 10
// .
// .
// .
//constexpr int CMD_OpenRecentFile10 = 511; 

constexpr int CMD_SaveProject = 512;
constexpr int CMD_SaveProjectAs = 513;
constexpr int CMD_PlayProject = 514;
constexpr int CMD_BuildProject = 515;
constexpr int CMD_Exit = 516;

constexpr int CMD_AddObject = 517;
constexpr int CMD_AddAsset = 518;
constexpr int CMD_AddPrefab = 519;
constexpr int CMD_AddAddon = 520;
constexpr int CMD_ResetCursor = 521;

constexpr int CMD_Preferences = 522;
constexpr int CMD_Update = 523;

constexpr int CMD_About = 524;
constexpr int CMD_Documentation = 525;
constexpr int CMD_Homepage = 526;
constexpr int CMD_Github = 527;

constexpr int CMD_SwitchObjectList = 528;
constexpr int CMD_SwitchPropertyGrid = 529;

constexpr int CMD_OpenIDE = 258;
constexpr int CMD_Switch2D3D = 259;

class EditorWindow
{
	HINSTANCE _hInstance;
	HWND _mainWindow;
	HWND _listBox;
	HWND _toolbar;
	HWND _handleRenderWindow;
	HACCEL acceleratorTable;

	std::unique_ptr<RenderWindow> editor;

	bool _running;
	bool _changesSaved = true;

	char _currentFile[_MAX_PATH]{};
	void _saveProject(const char* fileName = nullptr);
	void _writeProject(const char *fileName);
public:
	EditorWindow(HINSTANCE hInstance, char* cmdArgs);

	void Run();

	~EditorWindow();

	Engine3DRadSpace::GraphicsDevice *GetGraphicsDevice();
	Engine3DRadSpace::Content::ContentManager *GetContentManager();

	void AddObject(Engine3DRadSpace::IObject *obj);
	bool WarnNotSaved();

	friend LRESULT __stdcall EditorWindow_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

LRESULT __stdcall EditorWindow_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern EditorWindow *gEditorWindow;