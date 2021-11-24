#pragma once
#include "IObject.h"
#include "Model3D.h"

namespace Engine3DRadSpace
{
	class Skinmesh :public IObject
	{
		Model3D* model;
	public:
		Skinmesh(Game* game, const std::string& name, bool enabled, const Vector3& pos, const Quaternion& q, const Vector3& c, const Vector3& s, const std::string& path) :
			IObject(game, name, enabled, pos, q, c, s, path), model(new Model3D(game, path.c_str())) {};

		Skinmesh(Game* game, const std::string& path) :
			IObject(game, "Skinmesh", true, { 0,0,0 }, { 0,0,0,1 }, { 0,0,0 }, { 1,1,1 }, path), model(new Model3D(game, path.c_str())) {}

		Matrix GetTranslation() override;

		void Update(float dt) override;
		void Draw(float dt, Game* g) override;

		void Enable() = 0;

		~Skinmesh();
	};
}
