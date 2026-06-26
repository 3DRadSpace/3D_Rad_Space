#include "Box.hpp"
#include "../IShaderCompiler.hpp"
#include "../../Math/Vector4.hpp"
#include "../../Math/MVP.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;

std::array<VertexPositionNormalColor, 24> Box::CreateVertices(const BoundingBox& b, const Color& color)
{
    const Vector3 nNegY(0, -1,  0);
    const Vector3 nPosY(0,  1,  0);
    const Vector3 nNegX(-1, 0,  0);
    const Vector3 nPosX( 1, 0,  0);
    const Vector3 nNegZ(0,  0, -1);
    const Vector3 nPosZ(0,  0,  1);

    const Vector3 p   = b.Position;
    const Vector3 pX  = b.Position + Vector3(b.Scale.X, 0,          0         );
    const Vector3 pY  = b.Position + Vector3(0,          b.Scale.Y, 0         );
    const Vector3 pZ  = b.Position + Vector3(0,          0,          b.Scale.Z);
    const Vector3 pXY = b.Position + Vector3(b.Scale.X,  b.Scale.Y, 0         );
    const Vector3 pYZ = b.Position + Vector3(0,          b.Scale.Y,  b.Scale.Z);
    const Vector3 pXZ = b.Position + Vector3(b.Scale.X,  0,          b.Scale.Z);
    const Vector3 pXYZ = b.Position + b.Scale;

    return
    {
        // -Y face (bottom), normal = (0,-1,0)
        VertexPositionNormalColor{ p,   nNegY, color }, // V0
        VertexPositionNormalColor{ pX,  nNegY, color }, // V1
        VertexPositionNormalColor{ pZ,  nNegY, color }, // V2
        VertexPositionNormalColor{ pXZ, nNegY, color }, // V3

        // +Y face (top), normal = (0,1,0)
        VertexPositionNormalColor{ pY,   nPosY, color }, // V4
        VertexPositionNormalColor{ pXY,  nPosY, color }, // V5
        VertexPositionNormalColor{ pYZ,  nPosY, color }, // V6
        VertexPositionNormalColor{ pXYZ, nPosY, color }, // V7

        // -X face (left), normal = (-1,0,0)
        VertexPositionNormalColor{ p,   nNegX, color }, // V8
        VertexPositionNormalColor{ pY,  nNegX, color }, // V9
        VertexPositionNormalColor{ pZ,  nNegX, color }, // V10
        VertexPositionNormalColor{ pYZ, nNegX, color }, // V11

        // +X face (right), normal = (1,0,0)
        VertexPositionNormalColor{ pX,   nPosX, color }, // V12
        VertexPositionNormalColor{ pXY,  nPosX, color }, // V13
        VertexPositionNormalColor{ pXZ,  nPosX, color }, // V14
        VertexPositionNormalColor{ pXYZ, nPosX, color }, // V15

        // -Z face (front), normal = (0,0,-1)
        VertexPositionNormalColor{ p,   nNegZ, color }, // V16
        VertexPositionNormalColor{ pX,  nNegZ, color }, // V17
        VertexPositionNormalColor{ pY,  nNegZ, color }, // V18
        VertexPositionNormalColor{ pXY, nNegZ, color }, // V19

        // +Z face (back), normal = (0,0,1)
        VertexPositionNormalColor{ pZ,   nPosZ, color }, // V20
        VertexPositionNormalColor{ pXZ,  nPosZ, color }, // V21
        VertexPositionNormalColor{ pYZ,  nPosZ, color }, // V22
        VertexPositionNormalColor{ pXYZ, nPosZ, color }, // V23
    };
}

std::array<unsigned, 36> Box::CreateIndices()
{
    return
    {
        // -Y face
        0, 2, 3,
        0, 3, 1,
        // +Y face
        7, 6, 4,
        5, 7, 4,
        // -X face
        8, 9, 11,
        8, 11, 10,
        // +X face
        15, 13, 12,
        14, 15, 12,
        // -Z face
        17, 19, 18,
        17, 18, 16,
        // +Z face
        20, 22, 23,
        20, 23, 21,
    };
}

Box::Box(IGraphicsDevice *device, const BoundingBox&b, Color color) :
	IPrimitive(device, nullptr),
	_box(b),
	_color(color),
	Light{ Colors::White, Color(color.R * 0.15f, color.G * 0.15f, color.B * 0.15f, 1.0f), Vector3(0,-1,0), 1.0f }
{
    auto box_vertices = CreateVertices(b, color);
    _vertices = device->CreateVertexBuffer<VertexPositionNormalColor>(box_vertices, BufferUsage::ReadOnlyGPU);

    std::array<unsigned, 36> indices = CreateIndices();
    _indices = device->CreateIndexBuffer(indices);

    // Set Lambertian shader with color
    constexpr const char* lambertShader = "Data\\Shaders\\Lambert_PositionNormal.hlsl";
    auto vsLambertShader = ShaderDescFile(
        lambertShader,
        "VS_Main",
        ShaderType::Vertex
    );
    auto psLambertShader = ShaderDescFile(
        lambertShader,
        "PS_Main",
        ShaderType::Fragment
    );
    std::array<ShaderDesc*, 2> lambertShaderDesc =
    {
        &vsLambertShader,
        &psLambertShader
    };
    auto [lambertEffect, result] = device->ShaderCompiler()->CompileEffect(lambertShaderDesc);
    if (result.Succeded)
    {
        _shader = lambertEffect;
    }
}

BoundingBox Box::GetBoundingBox() const noexcept
{
    return _box;
}

void Box::SetBoundingBox(const BoundingBox&b)
{
    _box = b;

    auto box_vertices = CreateVertices(b, _color);
    _vertices->SetData<VertexPositionNormalColor>(box_vertices);
}

Color Box::GetColor() const noexcept
{
    return _color;
}

void Box::SetColor(const Color&color)
{
    _color = color;

    auto verts = CreateVertices(_box, color);
    _vertices->SetData<VertexPositionNormalColor>(verts);
}

void Box::Draw3D()
{
    struct alignas(16) LambertData
    {
        Matrix4x4 MatWorldInverseTranspose;
        Vector4   LightColor;
        Vector4   AmbientColor;
        Vector3   LightDirection;
        float     Intensity;
    };

	Math::MVP mvp
	{
		.World = Transform,
		.View = View,
		.Projection = Projection
	};
    Matrix4x4 worldInverseTranspose = Matrix4x4::Transpose(Matrix4x4::Invert(Transform));

    LambertData data =
    {
        worldInverseTranspose,
        Vector4(Light.LightColor.R,   Light.LightColor.G,   Light.LightColor.B,   Light.LightColor.A),
        Vector4(Light.AmbientColor.R, Light.AmbientColor.G, Light.AmbientColor.B, Light.AmbientColor.A),
        Light.LightDirection,
        Light.Intensity
    };

    // Upload to cbuffer slot 0 on every shader stage before binding
    _shader->SetData(&mvp, 0);
    _shader->SetData(&data, 1);

    _shader->SetAll();

    auto cmd = _device->ImmediateContext();
    cmd->SetTopology(VertexTopology::TriangleList);
    cmd->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}