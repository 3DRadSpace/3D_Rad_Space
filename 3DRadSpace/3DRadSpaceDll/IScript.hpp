#pragma once
#include "Game.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents the interface for any script.
	/// </summary>
	class DLLEXPORT IScript
	{
	public:
		/// <summary>
		/// Loading function. Can be used for loading resources like 3D models, initializing resources like memory buffers, et cetera.
		/// </summary>
		/// <param name="game">Handle to the graphics handles</param>
		virtual void Load(Game* game) = 0;
		/// <summary>
		/// Update function. Called when doing physics and input handling.
		/// </summary>
		/// <param name="dt"></param>
		virtual void Update(float dt) = 0;
		/// <summary>
		/// Drawing function. Called when doing rendering.
		/// </summary>
		/// <param name="dt"></param>
		virtual void Draw(float dt) = 0;
		/// <summary>
		/// Deinitialization function. Free memory resources here.
		/// </summary>
		virtual void End() = 0;
		~IScript();
	};
}

#define __3DRSPSCRIPT(T)  \
class (T); \
extern "C" Engine3DRadSpace::IScript* CreateScriptInstance() \
{ \
	static_assert(std::is_default_constructible<(T)>::value,"T must have a default constructor"); \
	static_assert(std::is_class<(T)>::value,"T must be a structure or a class"); \
	(T) *scriptInst = new (T); \
	Engine3DRadSpace::IScript* ret =  dynamic_cast<Engine3DRadSpace::IScript*>(scriptInst); \
	return ret; \
} \