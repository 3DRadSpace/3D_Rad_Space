#include "Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Math;

Game::Game(const std::string &title, unsigned width, unsigned height, bool fullscreen) :
	Window(std::make_unique<Engine3DRadSpace::Window>(title, width, height))
{
	Device = std::make_unique<GraphicsDevice>(Window->NativeHandle(),width,height);
	Content = std::make_unique<Content::ContentManager>(Device.get());
	SpriteBatch = std::make_unique<Graphics::SpriteBatch>(Device.get());
	_valid = true;
}

Game::Game(Engine3DRadSpace::Window &&window) :
	Window(std::make_unique<Engine3DRadSpace::Window>(std::move(window)))
{
	Math::Point size = Window->Size();

	Device = std::make_unique<GraphicsDevice>(Window->NativeHandle(), size.X, size.Y);
	Content = std::make_unique<Content::ContentManager>(Device.get());
	SpriteBatch = std::make_unique<Graphics::SpriteBatch>(Device.get());
	_valid = true;
}

void Game::Run()
{
	Game::Initialize();
	Initialize();
	Game::Load(Content.get());
	Load(Content.get());
	while (_running && Window->NativeHandle() != nullptr)
	{	
		Window->ProcessMessages();
		RunOneFrame();
	}
}

void Game::RunOneFrame()
{
	auto ts_u1 = std::chrono::high_resolution_clock::now();

	auto& keyboard = Window->GetKeyboardState();
	auto& mouse = Window->GetMouseState();

	Game::Update(keyboard, mouse, u_dt);
	this->Update(Window->GetKeyboardState(), Window->GetMouseState(), u_dt);
	auto ts_u2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> uDiff = ts_u2 - ts_u1;
	u_dt = uDiff.count();

	auto ts_d1 = std::chrono::high_resolution_clock::now();

	this->Device->SetViewport();
	this->Device->Clear(ClearColor);

	Game::Draw(View, Projection, d_dt);
	this->Draw(View,Projection,d_dt);

	this->Device->Present();

	auto ts_d2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> dDiff = ts_d2 - ts_d1;
	d_dt = dDiff.count();
}

void Game::Exit()
{
	_running = false;
}

void Game::RequestPhysicsInitialization(const Vector3 &gravity, double timeStep)
{
	Physics = std::make_unique<PhysicsEngine>(
		Physics::PhysicsSettings
		{
			.PhysicsEnabled = true,
			.Gravity = gravity,
			.TimeStep = timeStep
		}
	);
}

Engine3DRadSpace::Game::~Game()
{
	Exit();
}


void Game::Load(ContentManager* content)
{
	for (auto& [object, type] : Objects)
	{
		object->Load(content);
	}
}

void Game::Load(Content::ContentManager* content, const std::filesystem::path& path)
{

}

void Game::Update(Keyboard& keyboard, Mouse& mouse, double dt)
{
	for (auto& [object, type] : Objects)
	{
		object->Update(keyboard, mouse, dt);
	}
}

void Game::Draw(Math::Matrix4x4& view, Math::Matrix4x4& projection, double dt)
{
	for (auto& [object, type] : Objects)
	{
		if (type == ObjectList::ObjectInstance::ObjectType::IObject3D)
		{
			(static_cast<IObject3D*>(object.get()))->Draw(view, projection, dt);
		}
	}
}

void Game::Draw(Graphics::SpriteBatch* spriteBatch, double dt)
{
	for (auto& [object, type] : Objects)
	{
		if (type == ObjectList::ObjectInstance::ObjectType::IObject2D)
		{
			(static_cast<IObject2D*>(object.get()))->Draw(spriteBatch, dt);
		}
	}
}

void Game::Initialize()
{
	for (auto& [object, type] : Objects)
	{
		object->internalInitialize(this);
		object->Initialize();
	}
}

Ray Game::GetMouseRay(const Vector2 &mousePosition, const Matrix4x4 &view, const Matrix4x4 &projection)
{
	Vector3 nearPoint = Vector3(mousePosition.X, mousePosition.Y, 0);
	Vector3 farPoint = Vector3(mousePosition.X, mousePosition.Y, 1);

	auto viewport = Device->GetViewport();

	nearPoint = viewport.Unproject(nearPoint, projection, view, Matrix4x4{});
	farPoint = viewport.Unproject(farPoint, projection, view, Matrix4x4{});
	Vector3 direction = farPoint - nearPoint;
	direction.Normalize();

	return Ray
	{
		.Origin = nearPoint,
		.Direction = direction
	};
}