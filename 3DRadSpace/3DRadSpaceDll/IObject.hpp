#pragma once
#include "Globals.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix.hpp"
#include "Game.hpp"

#pragma warning( push )
#pragma warning( disable : 4251 )

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents the base interface for any object used in 3DRadSpace.
	/// </summary>
	class DLLEXPORT IObject
	{
	public:
		//Main constructor.
		IObject(Game* game,const std::string &name = "Empty object", bool enabled = false, Vector3 pos = { 0,0,0 }, Quaternion rot = { 0,0,0,1 }, Vector3 cen = { 0,0,0 }, Vector3 scal = { 1,1,1 },const std::string &resource = "") :
			Name(name), Enabled(enabled), Position(pos), Rotation(rot), Center(cen), Scale(scal), Resource(resource), game(game) {};

		/// <summary>
		/// Defines the name of the object. Can be used as a tag or as an identifier.
		/// </summary>
		std::string Name;

		/// <summary>
		/// Checks if the object is enabled.
		/// </summary>
		bool Enabled;

		/// <summary>
		/// Represents the object's position in the world.
		/// </summary>
		Vector3 Position;

		/// <summary>
		/// Represents the object's rotation center.
		/// </summary>
		Vector3 Center;

		/// <summary>
		/// Represents the rotation using a quaternion.
		/// </summary>
		Quaternion Rotation;

		/// <summary>
		/// Represents the object's scaling.
		/// </summary>
		Vector3 Scale;

		/// <summary>
		/// Represents the file resource of the object if used.
		/// </summary>
		std::string Resource;

		/// <summary>
		/// Represents a pointer to the Game class that handles rendering and updating.
		/// </summary>
		Game* game;

		/// <summary>
		/// Represents the linear transfomation constructed from the position, rotation center, rotation and scaling.
		/// </summary>
		/// <returns></returns>
		virtual Matrix GetTranslation() = 0;

		/// <summary>
		/// Does updating logic like keyboard input and physics.
		/// </summary>
		/// <param name="dt">Time passed since the last update call.</param>
		virtual void Update(float dt) = 0;
		/// <summary>
		/// Rendering logic like LODs, animation, etc.
		/// </summary>
		/// <param name="dt">Delta time. Time passed since the last drawn frame.</param>
		/// <param name="g">A handle to the graphics handles.</param>
		virtual void Draw(float dt, Game* g) = 0;

		/// <summary>
		/// Enables the object forcefully.
		/// </summary>
		virtual void Enable() = 0;

		~IObject();
	};
}
#pragma warning( pop )
