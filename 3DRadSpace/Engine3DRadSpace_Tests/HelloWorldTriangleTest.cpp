#include "pch.h"
#include <Engine3DRadSpace/Game.hpp>
#include <Engine3DRadSpace/Graphics/VertexBuffer.hpp>
#include <Engine3DRadSpace/Graphics/Shaders/Blank_NoMatrix.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Content;

class TriangleTest : public Game
{
	Shaders::Blank_NoMatrix _triangleShader;
	std::unique_ptr<VertexBufferV<VertexPositionColor>> _triangleBuffer;
public:
	TriangleTest();

	void Initialize() override;
	void Load(ContentManager *content) override;
	void Update(Keyboard& keyboard, Mouse& mouse, double dt) override;
	void Draw(Matrix4x4& view, Matrix4x4 &projection, double dt) override;

	int frameCount = 0;
};

TriangleTest::TriangleTest():
	Game("Triangle Test", 800, 600, false),
	_triangleShader(Device.get())
{

}

void TriangleTest::Initialize()
{
	std::array<VertexPositionColor, 3> triangle =
	{
		VertexPositionColor{Vector3(0.0,0.5,0.0), Colors::Red},
		VertexPositionColor{Vector3(0.5,-0.5,0.0), Colors::Green},
		VertexPositionColor{Vector3(-0.5,-0.5,0.0), Colors::Blue}
	};

	_triangleBuffer = std::make_unique<VertexBufferV<VertexPositionColor>>(Device.get(), triangle);
}

void TriangleTest::Load(ContentManager *content)
{
}

void TriangleTest::Update(Keyboard& keyboard, Mouse& mouse, double dt)
{
}

void TriangleTest::Draw(Matrix4x4& view, Matrix4x4 &projection, double dt)
{
	if (frameCount == 1) Exit();
	frameCount++;

	_triangleShader.SetBasic();
	Device->SetTopology(VertexTopology::TriangleList);
	_triangleBuffer->Draw();
	Device->SaveBackBufferToFile("Triangle.png");
	//TODO: Check if the saved image is matching with a expected image
}

TEST(EngineCoreTests, HelloTriangle)
{
	TriangleTest t;
	t.Run();
	EXPECT_TRUE(true);
}