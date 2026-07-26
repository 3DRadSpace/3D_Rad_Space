#pragma once
#include "CSharpScript.hpp"
#include "../../Reflection/ReflectedObject.hpp"
#include "../../Content/ContentManager.hpp"
#include "../../Objects/IObject.hpp"
#include "resource.h"
#include <Windows.h>

extern "C"
{
	__declspec(dllexport) void* CreateCSharpEditorWindow(HWND dlgOwner, HINSTANCE hInstance, void* reflectionData, void* contentManager, void* object);
}

INT_PTR CALLBACK CSharpEditorDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

namespace Engine3DRadSpace::Scripting::CSharp
{
	class CSharpScriptEditor
	{
		HWND _window;
		HINSTANCE _hInstance;
		HWND _owner;
		CSharpScript* _script;
		bool _wasAllocated;
		bool _wasScintillaModuleLoaded;
		bool _wasLexillaModuleLoaded;
		int _maxLineNumberCharLength;
		HWND _codeControl;

		void initForms();
		void handleCharAdded(HWND scintilla, int ch);
		void handleTextChanged(HWND scintilla);

		void load(const std::filesystem::path& path);
		void save(const std::filesystem::path& path);

		std::filesystem::path saveFileDialog();
		std::filesystem::path openFileDialog();
		void openFile();
	public:
		CSharpScriptEditor(
			HWND dlgOwner, 
			HINSTANCE hInstance,
			CSharpScript* object
		);

		CSharpScriptEditor(const CSharpScriptEditor&) = delete;
		CSharpScriptEditor& operator=(const CSharpScriptEditor&) = delete;

		CSharpScriptEditor(CSharpScriptEditor&&) = delete;
		CSharpScriptEditor& operator=(CSharpScriptEditor&&) = delete;

		CSharpScript* ShowDialog();

		friend INT_PTR CALLBACK ::CSharpEditorDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);
	};
}