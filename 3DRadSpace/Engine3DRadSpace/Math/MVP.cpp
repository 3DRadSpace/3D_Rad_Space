#include "MVP.hpp"

using namespace Engine3DRadSpace::Math;

Matrix4x4 MVP::Multiply() const noexcept
{
	return World * View * Projection;
}