#include "IGizmo.hpp"

using namespace Engine3DRadSpace::Objects;

IGizmo::IGizmo(
	bool allow3DRendering,
	bool allow2DRendering,
	bool allowUpdating,
	bool allowTranslating,
	bool allowRotating,
	bool allowScaling
) :
	Allow3DRendering(allow3DRendering),
	Allow2DRendering(allow2DRendering),
	AllowUpdating(allowUpdating),
	AllowTranslating(allowTranslating),
	AllowRotating(allowRotating),
	AllowScaling(allowScaling)
{
}