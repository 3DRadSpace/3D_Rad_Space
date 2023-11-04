#include "IObject2D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;

IObject2D::IObject2D(const std::string &name, const std::string &tag, bool enabled, bool visible, const Vector2&pos, const
                     Vector2&scale, 
                     float rotation, const Vector2&pivot, float depth) :
	IObject(name, tag, false, false),
	Position(pos),
	Rotation(rotation),
	RotationCenter(pivot),
	Scale(scale),
	Depth(depth)
{
}

IObject2D::IObject2D(Game *game, const std::string &name, const std::string &tag, bool enabled, bool visible, const Vector2 &pos,
                     const Vector2& scale, float rotation, const Vector2&pivot, float depth): 
	IObject(game, name, tag, false, false),
	Position(pos),
	Rotation(rotation),
	RotationCenter(pivot),
	Scale(scale),
	Depth(depth)
{
}
