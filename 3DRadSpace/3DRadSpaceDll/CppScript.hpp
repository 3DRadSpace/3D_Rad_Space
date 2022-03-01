#pragma once
#include "Game.hpp"
#include "IScript.hpp"

#ifdef WIN32
#ifdef __DIRECTXVER

#include <Windows.h>

///
/// FIXME: This can't handle more classes per 1 single library
///

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a function pointer
	/// </summary>
	typedef IScript* (*fptrGetScriptInstance)();

	/// <summary>
	/// Represents a compiled source code written in C++.
	/// </summary>
	class CppScript
	{
		HMODULE _module;
		bool _loaded;
		fptrGetScriptInstance _createInstance;
		IScript* scriptInstance;

	public:
		/// <summary>
		/// Constructor. Loads the given DLL and then creates a instance that's returned by the function CreateScriptInstance() located inside the loaded dll.
		/// Use CppScript::IsLoaded to check if the loading of the module was successful.
		/// </summary>
		/// <param name="modulepath">Path to the module containing a CreateScriptInstance() function</param>
		/// <param name="game">Used by the script to access data like the loaded objects, graphics handles, etc</param>
		explicit CppScript(const char* modulepath);

		/// <summary>
		/// Checks if an error occured while loading the module.
		/// </summary>
		/// <returns>True if the module was succesfully loaded, false otherwise.</returns>
		bool IsLoaded();

		void CallLoad(Game* game);
		/// <summary>
		/// Calls the draw function from the given IScript interface.
		/// </summary>
		/// <param name="dt">Time passed since the last draw call</param>
		void CallDraw(float dt);
		/// <summary>
		/// Calls the update function from the given IScript interface.
		/// </summary>
		/// <param name="dt">Time passed since the last update call</param>
		void CallUpdate(float dt);
		/// <summary>
		/// Calls the end function from the IScript interface when perfominig deinitalization.
		/// </summary>
		void CallEnd();

		~CppScript();
	};

}
#endif
#endif
