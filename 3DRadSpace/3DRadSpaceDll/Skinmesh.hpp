#pragma once
#include "IObject.hpp"
#include "Model3D.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a 3D model
	/// </summary>
	class Skinmesh :public IObject
	{
		Model3D* model;
	public:
		/// <summary>
		/// Constructs a Skinmesh with all possible arguments.
		/// </summary>
		/// <param name="game">Handle to the graphics devices and rendering data</param>
		/// <param name="name">Name of the object</param>
		/// <param name="enabled">Checks if the skinmesh will be rendered</param>
		/// <param name="pos">Skinmesh position in the world</param>
		/// <param name="q">Skinmesh rotation</param>
		/// <param name="c">Skinmesh rotation pivot(center)</param>
		/// <param name="s">Skinmesh scale</param>
		/// <param name="path">Path to the skinmesh 3D model</param>
		Skinmesh(Game* game, const std::string& name, bool enabled, const Vector3& pos, const Quaternion& q, const Vector3& c, const Vector3& s, const std::string& path) :
			IObject(game, name, enabled, pos, q, c, s, path), model(new Model3D(game, path.c_str())) {};

		/// <summary>
		/// Constructs a skinmesh with default position, scaling, rotation and rotation pivot.
		/// </summary>
		/// <param name="game">Handle to the graphics handles</param>
		/// <param name="path">Path fo the 3D model</param>
		Skinmesh(Game* game, const std::string& path) :
			IObject(game, "Skinmesh", true, { 0,0,0 }, { 0,0,0,1 }, { 0,0,0 }, { 1,1,1 }, path), model(new Model3D(game, path.c_str())) {}

		/// <summary>
		/// Gets the linear transformation used by this skinmesh object
		/// </summary>
		/// <returns></returns>
		Matrix GetTranslation() override;

		/// <summary>
		/// This function has no effect.
		/// </summary>
		/// <param name="dt">Time since the last Update call</param>
		void Update(float dt) override;
		/// <summary>
		/// Draws the skinmesh.
		/// </summary>
		/// <param name="dt">Delta time</param>
		/// <param name="g">Handle to the graphics handle</param>
		void Draw(float dt, Game* g) override;

		void Enable();

		~Skinmesh();
	};
}
