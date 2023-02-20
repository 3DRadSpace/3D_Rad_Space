#include "pch.h"
#include <Engine3DRadSpace/Game.hpp>
#include <Engine3DRadSpace/VertexBuffer.hpp>
#include <Engine3DRadSpace/Blank_NoMatrix.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;

class TriangleTest : public Game
{
	Engine3DRadSpace::Graphics::Shaders::Blank_NoMatrix _triangleShader;
	std::unique_ptr<Engine3DRadSpace::Graphics::VertexBuffer<Engine3DRadSpace::Graphics::VertexPositionColor>> _triangleBuffer;
public:
	TriangleTest();

	void Initialize() override;
	void Update(Keyboard& keyboard, Mouse& mouse, double dt) override;
	void Draw(Matrix& view, Matrix &projection, double dt) override;
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

	_triangleBuffer = std::make_unique<VertexBuffer<VertexPositionColor>>(Device.get(), triangle, _triangleShader.GetVertexShader());
}

void TriangleTest::Update(Keyboard& keyboard, Mouse& mouse, double dt)
{
}

void TriangleTest::Draw(Matrix& view, Matrix &projection, double dt)
{
	_triangleShader.SetBasic();
	Device->SetTopology(VertexTopology::TriangleList);
	_triangleBuffer->SetAndDraw();

	//TODO: save into a file.

	Exit();
}

TEST(EngineCore, HelloTriangleTest)
{
	TriangleTest t;
	t.Run();

	//TODO: Save into a file and compare the image.
}