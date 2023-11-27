#include "RenderWindow.hpp"
#include <Engine3DRadSpace/Graphics/Fonts/Font.hpp>
#include "../Frontend/Settings.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Algorithms::Picking;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Objects;

RenderWindow::RenderWindow(HWND parent, HINSTANCE hInstance) :
	Game(Engine3DRadSpace::Window(hInstance, parent)),
	editorWindow(parent), 
	testTexture(nullptr)
{

}

void RenderWindow::Initialize()
{
	std::vector<VertexPositionColor> dLines =
	{
		//+X
		VertexPositionColor{Vector3(0,0,0),Colors::Red},
		VertexPositionColor{Vector3(500,0,0),Colors::Red},
		//-X
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(-500,0,0),Colors::White},
		//+Y
		VertexPositionColor{Vector3(0,0,0),Colors::Green},
		VertexPositionColor{Vector3(0,500,0),Colors::Green},
		//-Y
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(0,-500,0),Colors::White},
		//+Z
		VertexPositionColor{Vector3(0,0,0),Colors::Blue},
		VertexPositionColor{Vector3(0,0,500),Colors::Blue},
		//-Z
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(0,0,-500),Colors::White},
	};

	for (int i = -10; i <= 10; i++)
	{
		if (i == 0) continue;
		dLines.push_back(VertexPositionColor{ Vector3(float(i),0,10), Colors::Gray });
		dLines.push_back(VertexPositionColor{ Vector3(float(i),0,-10), Colors::Gray });

		dLines.push_back(VertexPositionColor{ Vector3(10, 0, float(i)), Colors::Gray });
		dLines.push_back(VertexPositionColor{ Vector3(-10, 0, float(i)), Colors::Gray });
	}

	this->lines = std::make_unique<Primitives::Lines>(Device.get(), dLines);
	Camera.LookMode = Camera::CameraMode::UseLookAtCoordinates;

	_pickingShader = std::make_unique<PickingShader>(Device.get());
}

Model3D *fish = nullptr;

void RenderWindow::Load(Content::ContentManager *content)
{
	testTexture = content->Load<Texture2D>("gradient.png");
	//testTexture->Resize(256, 256);

	fish = content->Load<Model3D>("Data\\Models\\YellowFish.x");

	testFont = std::make_unique<Fonts::Font>(Device.get(), "Data\\Fonts\\arial.ttf");
	//this->ClearColor.R = 0.128;
}

void RenderWindow::Update(Keyboard& keyboard, Mouse& mouse, double dt)
{
	zoom = mouse.ScrollWheel();
	if (zoom < -4.0f) zoom = -4.0f;

	if (mouse.LeftButton() == ButtonState::Pressed && IsFocused())
	{
		Point screenCenter = Window->Size() / 2;
		Point mousePos = mouse.Position();
		Window->SetMousePosition(screenCenter);

		Vector2 mouseDelta = (Vector2)(screenCenter - mousePos) * float(dt);
		cameraPos -= mouseDelta * Settings::CameraSensitivity.Value;

		cameraPos.Y = std::clamp<float>(
			cameraPos.Y,
			-std::numbers::pi_v<float> / 2.f + std::numeric_limits<float>::epsilon(),
			std::numbers::pi_v<float> / 2.f - std::numeric_limits<float>::epsilon()
		);
	}

	if(keyboard.IsKeyDown(Key::Space))
	{
		_keyboardTest = true;
	}
	else _keyboardTest = false;

	Quaternion q = Quaternion::FromYawPitchRoll(-cameraPos.Y, 0, 0) * Quaternion::FromYawPitchRoll(0, -cameraPos.X, 0);
	Camera.Position = Vector3::UnitZ().Transform(q) * (zoom + 5);
	Camera.LookAt = cursor3D;
}

void RenderWindow::Draw(Matrix4x4 &view, Matrix4x4 &projection, double dt)
{
	Camera.Draw(view, projection, dt);

	lines->Draw(View, Projection, dt);

	if(_keyboardTest)
	{
		
	}

	for(auto &obj : Objects)
	{
		switch(obj.InternalType)
		{
		case ObjectList::ObjectInstance::ObjectType::IObject2D:
				static_cast<IObject2D *>(obj.Object.get())->EditorDraw(SpriteBatch.get(), dt, false);
				break;
			case ObjectList::ObjectInstance::ObjectType::IObject3D:
				static_cast<IObject3D *>(obj.Object.get())->EditorDraw(View, Projection, dt, false);
				break;
			default:
				break;
		}
	}
}

bool RenderWindow::IsFocused()
{
	return editorWindow == GetForegroundWindow();
}

void RenderWindow::Reset3DCursor()
{
	cursor3D = Vector3::Zero();
}