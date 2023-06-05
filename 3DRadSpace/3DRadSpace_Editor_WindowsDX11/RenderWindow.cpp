#include "RenderWindow.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Objects;

RenderWindow::RenderWindow(HWND parent, HINSTANCE hInstance) :
	Game(Engine3DRadSpace::Window(hInstance, parent)),
	simpleShader(std::make_unique<BlankShader>(Device.get())),
	editorWindow(parent)
{
}

void RenderWindow::Initialize()
{
	this->simpleShader = std::make_unique<BlankShader>(Device.get());

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
		dLines.push_back(VertexPositionColor{ Vector3(float(i),0,10),Colors::Gray });
		dLines.push_back(VertexPositionColor{ Vector3(float(i),0,-10),Colors::Gray });

		dLines.push_back(VertexPositionColor{ Vector3(10, 0, float(i)), Colors::Gray });
		dLines.push_back(VertexPositionColor{ Vector3(-10, 0, float(i)), Colors::Gray });
	}

	this->lines = std::make_unique<VertexBufferV<VertexPositionColor>>(Device.get(), dLines);
	Camera.LookMode = Camera::CameraMode::UseLookAtCoordinates;

	lineRasterizer = std::make_unique<RasterizerState>(Device.get(),RasterizerFillMode::Solid, RasterizerCullMode::None);

	defaultRasterizer = std::make_unique<RasterizerState>(Device.get());

	texturedShader = std::make_unique<BasicTextured_NBT>(Device.get());
	cameraModel = std::make_unique<Model3D>(Device.get(), "Data\\Models\\Camera.x");

	testTexture = std::make_unique<Texture2D>(Device.get(), L"holding.png");
	spriteBatch = std::make_unique<SpriteBatch>(Device.get());
}

void RenderWindow::Update(Keyboard& keyboard, Mouse& mouse, double dt)
{
	zoom = mouse.ScrollWheel();
	if (zoom < -4.0f) zoom = -4.0f;

	if (mouse.RightButton() && IsFocused())
	{
		Point screenCenter = Window->Size() / 2;
		Point mousePos = mouse.Position();
		Window->SetMousePosition(screenCenter);

		Vector2 mouseDelta = (Vector2)(screenCenter - mousePos) * float(dt);
		cameraPos -= mouseDelta * 10.0f;

		cameraPos.Y = std::clamp<float>(
			cameraPos.Y,
			-std::numbers::pi_v<float> / 2.f + std::numeric_limits<float>::epsilon(),
			std::numbers::pi_v<float> / 2.f - std::numeric_limits<float>::epsilon()
		);

		if (keyboard.IsKeyDown(Key::F9))
		{
			OutputDebugStringA("pressed F9 \r\n");
		}
	}

	Quaternion q = Quaternion::FromYawPitchRoll(-cameraPos.Y, 0, 0) * Quaternion::FromYawPitchRoll(0, -cameraPos.X, 0);
	Camera.Position = Vector3::UnitZ().Transform(q) * (zoom + 5);
	Camera.LookAt = cursor3D;
}

void RenderWindow::Draw(Matrix &view, Matrix &projection, double dt)
{
	Camera.Draw(view, projection, dt);
	Matrix viewProj = view * projection;

	//Draw the lines.
	simpleShader->SetBasic();
	Device->SetRasterizerState(lineRasterizer.get());
	simpleShader->SetTransformation(viewProj);
	Device->SetTopology(VertexTopology::LineList);
	lines->Draw();

	spriteBatch->Begin(SpriteBatchSortMode::Immediate);
	spriteBatch->Draw(testTexture.get(), Vector2(0.25, 0.25), Vector2::One() / 2, Colors::White, false, false);
	spriteBatch->End();

	//Draw any other objects
	for (auto& obj : Objects)
	{
		obj->EditorDraw(view, projection, dt);
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
