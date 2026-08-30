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

void* E3DRSP_Game_GetSpriteBatch(E3DRSP_Game game)
{
	if (game == nullptr) return nullptr;
	return static_cast<Game*>(game)->SpriteBatch.get();
}

void* E3DRSP_Game_GetIGraphicsDevice(E3DRSP_Game game)
{
	if (game == nullptr) return nullptr;
	return static_cast<Game*>(game)->Device.get();
}

void* E3DRSP_Game_GetPostProcessCollection(E3DRSP_Game game)
{
	if (game == nullptr) return nullptr;
	return static_cast<Game*>(game)->PostProcesses.get();
}

void* E3DRSP_Game_GetIPhysicsEngine(E3DRSP_Game game)
{
	if (game == nullptr) return nullptr;
	return static_cast<Game*>(game)->Physics.get();
}

void* E3DRSP_Game_GetRenderingManager(E3DRSP_Game game)
{
	if (game == nullptr) return nullptr;
	return static_cast<Game*>(game)->RenderingManager.get();
}

void* E3DRSP_Game_GetObjectList(E3DRSP_Game game)
{
	if (game == nullptr) return nullptr;
	return static_cast<Game*>(game)->Objects.get();
}

void* E3DRSP_Game_GetContentManager(E3DRSP_Game game)
{
	if (game == nullptr) return nullptr;
	return static_cast<Game*>(game)->Content.get();
}

void* E3DRSP_Game_GetCameraProvider(E3DRSP_Game game)
{
	if (game == nullptr) return nullptr;
	return static_cast<Game*>(game)->Cameras.get();
}

E3DRSP_Mouse E3DRSP_Game_GetMouse(E3DRSP_Game game)
{
	if (game == nullptr) return E3DRSP_Mouse{};
	return E3DRSP_Mouse{
		static_cast<Game*>(game)->Mouse.LeftButton() == Input::ButtonState::Pressed ? E3DRSP_Pressed : E3DRSP_Released,
		static_cast<Game*>(game)->Mouse.MiddleButton() == Input::ButtonState::Pressed ? E3DRSP_Pressed : E3DRSP_Released,
		static_cast<Game*>(game)->Mouse.RightButton() == Input::ButtonState::Pressed ? E3DRSP_Pressed : E3DRSP_Released,
		E3DRSP_Point{
			static_cast<int>(static_cast<Game*>(game)->Mouse.Position().X),
			static_cast<int>(static_cast<Game*>(game)->Mouse.Position().Y)
		},
		static_cast<float>(static_cast<Game*>(game)->Mouse.ScrollWheel())
	};
}

E3DRSP_Keyboard E3DRSP_Game_GetKeyboard(E3DRSP_Game game)
{
	if (game == nullptr) return E3DRSP_Keyboard{};

	uint8_t keys[10];

	return E3DRSP_Keyboard{
		*static_cast<Game*>(game)->Keyboard.Buffer(),
		*(static_cast<Game*>(game)->Keyboard.Buffer() + 1),
		*(static_cast<Game*>(game)->Keyboard.Buffer() + 2),
		*(static_cast<Game*>(game)->Keyboard.Buffer() + 3),
		*(static_cast<Game*>(game)->Keyboard.Buffer() + 4),
		*(static_cast<Game*>(game)->Keyboard.Buffer() + 5),
		*(static_cast<Game*>(game)->Keyboard.Buffer() + 6),
		*(static_cast<Game*>(game)->Keyboard.Buffer() + 7),
		*(static_cast<Game*>(game)->Keyboard.Buffer() + 8),
		*(static_cast<Game*>(game)->Keyboard.Buffer() + 9),
	};
}

E3DRSP_Window E3DRSP_Game_GetWindow(E3DRSP_Game game)
{
	if (game == nullptr) return nullptr;
	return static_cast<Game*>(game)->Window.get();
}

float E3DRSP_Game_GetDrawDeltaTime(E3DRSP_Game game)
{
	return static_cast<Game*>(game)->Draw_dt;
}

float E3DRSP_Game_GetUpdateDeltaTime(E3DRSP_Game game)
{
	return static_cast<Game*>(game)->Update_dt;
}