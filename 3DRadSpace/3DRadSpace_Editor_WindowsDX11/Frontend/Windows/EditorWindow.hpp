#pragma once
#include <Windows.h>
#include "..\..\Editor\EditorGame.hpp"
#include <CommCtrl.h>

constexpr const char* EditorWindowClassName = "CLASS_3DRADSPACE_MAINWINDOW";
constexpr const char* RecentProjectFile = "Data\\RecentProjects.txt";
constexpr const char* FileFilter = "3DRadSpace Project(*.3drsp)\0*.3drsp\0All Files(*.*)\0*.*\0\0";
constexpr const char* EngineVersion = "0.1.0";

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
constexpr int CMD_Plugins = 524;

constexpr int CMD_About = 525;
constexpr int CMD_Documentation = 526;
constexpr int CMD_Homepage = 527;
constexpr int CMD_Github = 528;

constexpr int CMD_SwitchObjectList = 529;
constexpr int CMD_SwitchPropertyGrid = 530;

constexpr int CMD_EditObject = 531;
constexpr int CMD_DeleteObject = 532;
constexpr int CMD_DeselectObject = 533;
constexpr int CMD_AddChildObject = 534;
constexpr int CMD_OpenIDE = 258;
constexpr int CMD_Switch2D3D = 259;

class EditorWindow
{
	HINSTANCE _hInstance;
	HWND _mainWindow;
	HWND _treeView;
	HWND _toolbar;
	HWND _handleRenderWindow;
	HACCEL acceleratorTable;

	std::unique_ptr<EditorGame> editor;

	bool _running;
	bool _changesSaved = true;

	std::filesystem::path _currentFile;
	void _openProject(const std::filesystem::path& filename);
	void _saveProject(const std::filesystem::path& filename = "");
	void _writeProject(const std::filesystem::path& filename);

	void _findUpdate();
	void _addRecentProject(const std::filesystem::path& filename);

	HTREEITEM _getSelectedListViewItem();
	std::pair<HTREEITEM, std::optional<unsigned>> _getSelectedObjectID();

	void _parseCmdArgs(const std::string & cmdArgs);

	std::chrono::time_point<std::chrono::high_resolution_clock> _lastFrameTime{};
	std::vector<std::filesystem::path> _recentFiles;
public:
	EditorWindow(HINSTANCE hInstance, const std::string &cmdArgs);

	void Run();

	~EditorWindow();

	Engine3DRadSpace::Graphics::IGraphicsDevice *GetGraphicsDevice();
	Engine3DRadSpace::Content::ContentManager *GetContentManager();

	IObject* CreateNewObject();
	void AddObject(Engine3DRadSpace::Objects::IObject *obj);
	void AddChildObject(Engine3DRadSpace::Objects::IObject *obj);
	void SelectObject(std::optional<unsigned> id);

	bool WarnNotSaved();
	void OpenRecentProject(uint8_t id);

	static void PopulateObjectList(Engine3DRadSpace::Objects::ObjectList* list, HWND treeView);

	friend LRESULT __stdcall EditorWindow_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	friend class Engine3DRadSpace::Game;
};

LRESULT __stdcall EditorWindow_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern EditorWindow *gEditorWindow;