#include "pch.h"
#include <Engine3DRadSpace/Games/Game.hpp>
#include <Engine3DRadSpace/Graphics/IVertexBuffer.hpp>
#include <Engine3DRadSpace/Graphics/IShaderCompiler.hpp>
#include "PerceptualHash.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Content;

class TriangleTest : public Game
{
	Effect* _triangleShader;
	std::unique_ptr<IVertexBuffer> _triangleBuffer;
public:
	TriangleTest();

	void Initialize() override;
	void Load() override;
	void Update() override;
	void Draw3D() override;

	int frameCount = 0;
};

TriangleTest::TriangleTest():
	Game("Triangle Test", 800, 600),
	_triangleShader(nullptr)
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

	_triangleBuffer = Device->CreateVertexBuffer<VertexPositionColor>(triangle, BufferUsage::ReadOnlyGPU);
}

void TriangleTest::Load()
{
	constexpr std::string_view shaderPath = "Data\\Shaders\\PositionColor_NoMat.hlsl";

	ShaderDescFile vs(shaderPath, "VS_Main", ShaderType::Vertex);
	ShaderDescFile ps(shaderPath, "PS_Main", ShaderType::Fragment);

	ShaderDesc* effect[2] = { &vs, &ps };

	_triangleShader = Device->ShaderCompiler()->CompileEffect(effect).first;
}

void TriangleTest::Update()
{
}

void TriangleTest::Draw3D()
{
	if (frameCount == 1) Exit();
	frameCount++;

	auto cmd = Device->ImmediateContext();

	_triangleShader->SetAll();
	cmd->SetTopology(VertexTopology::TriangleList);
	cmd->DrawVertexBuffer(_triangleBuffer.get());
	cmd->SaveBackBufferToFile("Triangle.png");
}

TEST(EngineCoreTests, HelloTriangle)
{
	TriangleTest t;
	t.Run();

	std::filesystem::path renderedImage = "Triangle.png";
	std::filesystem::path expectedImage = "Testing/Triangle.png";

	ASSERT_TRUE(std::filesystem::exists(renderedImage)) 
		<< "Rendered image was not saved";

	if (std::filesystem::exists(expectedImage))
	{
		// Compare using perceptual hash with threshold of 5 bits difference
		// Threshold can be adjusted: 0 = identical, 5-10 = very similar, >15 = different
		bool similar = Testing::PerceptualHash::AreImagesSimilar(
			renderedImage, 
			expectedImage, 
			5
		);

		EXPECT_TRUE(similar) << "Rendered image does not match expected image. ";
	}
	else
	{
		GTEST_SKIP() << "Reference image not found at: " << expectedImage;
	}

	std::filesystem::remove(renderedImage);
}