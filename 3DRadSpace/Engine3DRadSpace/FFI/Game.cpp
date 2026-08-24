#include "Game.h"
#include "../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;

E3DRSP_Game E3DRSP_Game_Create(const char* title, size_t width, size_t height)
{
	if(title == nullptr) title = "";
	return new Game(title, width, height);
}

void E3DRSP_Game_Run(E3DRSP_Game game)
{
	if(game == nullptr) return;
	static_cast<Game*>(game)->Run();
}

void E3DRSP_Game_RunOneFrame(E3DRSP_Game game)
{
	if(game == nullptr) return;
	static_cast<Game*>(game)->RunOneFrame();
}

E3DRSP_Ray E3DRSP_Game_GetMouseRay(
	E3DRSP_Game game,
	E3DRSP_Vector2 mousePos,
	const E3DRSP_Matrix4x4* view,
	const E3DRSP_Matrix4x4* projection
)
{
	if(game == nullptr || view == nullptr || projection == nullptr) return E3DRSP_Ray
	{
		E3DRSP_Vector3{0.0f, 0.0f, 0.0f},
		E3DRSP_Vector3{0.0f, 0.0f, 0.0f}
	};

	//Assume same memory layout
	Matrix4x4 m_view;
	memcpy_s(&m_view, sizeof(Matrix4x4), view, sizeof(E3DRSP_Matrix4x4));

	Matrix4x4 m_proj;
	memcpy_s(&m_proj, sizeof(Matrix4x4), projection, sizeof(E3DRSP_Matrix4x4));

	auto ray = static_cast<Game*>(game)->GetMouseRay(
		Vector2{mousePos.X, mousePos.Y},
		m_view,
		m_proj
	);

	return E3DRSP_Ray
	{
		E3DRSP_Vector3{ray.Origin.X, ray.Origin.Y, ray.Origin.Z},
		E3DRSP_Vector3{ray.Direction.X, ray.Direction.Y, ray.Direction.Z},
	};
}