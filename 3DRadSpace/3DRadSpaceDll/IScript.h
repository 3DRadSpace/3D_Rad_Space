#pragma once
#include "Game.h"

class DLLEXPORT IScript
{
public:
	virtual void Load(Game *game) = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;
	virtual void End() = 0;
	~IScript();
};


#define __3DRSPSCRIPT(T)  \
class (T); \
extern "C" IScript* CreateScriptInstance() \
{ \
	static_assert(std::is_default_constructible<(T)>::value,"T must have a default constructor"); \
	static_assert(std::is_class<(T)>::value,"T must be a structure or a class"); \
	(T) *scriptInst = new (T); \
	IScript* ret =  dynamic_cast<IScript*>(scriptInst); \
	return ret; \
} \