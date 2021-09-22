#pragma once
#include "Globals.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Game.h"

#pragma warning( push )
#pragma warning( disable : 4251 )

class DLLEXPORT IObject
{
public:

	IObject(Game* game,std::string name = "Empty object",bool enabled = false, Vector3 pos = { 0,0,0 }, Quaternion rot = { 0,0,0,1 }, Vector3 cen = { 0,0,0 }, Vector3 scal = { 1,1,1 }, std::string resource = "") :
		Name(name),Enabled(enabled), Position(pos), Rotation(rot) , Center(cen), Scale(scal), Resource(resource), game(game) {};

	std::string Name;

	bool Enabled;

	Vector3 Position;
	
	Vector3 Center;
	Quaternion Rotation;

	Vector3 Scale;

	std::string Resource;

	Game* game;

	virtual Matrix GetTranslation() = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw(float dt, Game* g) = 0;

	virtual void Enable() = 0;

	~IObject();
};

#pragma warning( pop )
