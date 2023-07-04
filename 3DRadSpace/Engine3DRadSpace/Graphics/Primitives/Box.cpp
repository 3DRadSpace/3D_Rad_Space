#include "Box.hpp"
#include "../Shaders/BlankShader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

inline std::unique_ptr<BlankShader> simpleShader;

std::array<VertexPositionColor, 8> Box::_createVerts(const Math::BoundingBox &b, const Engine3DRadSpace::Color &color)
{
    return std::array<VertexPositionColor, 8>
    {
        VertexPositionColor{ b.Position, color},
        VertexPositionColor{ b.Position + Vector3(b.Scale.X,0,0), color},
        VertexPositionColor{ b.Position + Vector3(0, b.Scale.Y,0), color},
        VertexPositionColor{ b.Position + Vector3(0, 0,b.Scale.Z), color},
        VertexPositionColor{ b.Position + Vector3(b.Scale.X, b.Scale.Y, 0), color},
        VertexPositionColor{ b.Position + Vector3(0, b.Scale.Y, b.Scale.Z), color},
        VertexPositionColor{ b.Position + Vector3(b.Scale.X, b.Scale.Z), color},
        VertexPositionColor{ b.Position + b.Scale , color},
    };
}

Engine3DRadSpace::Graphics::Primitives::Box::Box(GraphicsDevice *device, const Math::BoundingBox &b, Engine3DRadSpace::Color color)
{
    auto box_vertices = _createVerts(b, color);
    _vertices = std::make_unique<VertexBufferV<VertexPositionColor>>(device, box_vertices);

    std::array<unsigned, 32> indices =
    {
        0
    };
    _indices = std::make_unique<IndexBuffer>(device, indices);
}

BoundingBox Box::GetBoundingBox()
{
    return _box;
}

void Engine3DRadSpace::Graphics::Primitives::Box::SetBoundingBox(const Math::BoundingBox &b)
{
    _box = b;

    auto box_vertices = _createVerts(b, _color);
    _vertices->SetData(box_vertices);
}

Color Box::GetColor()
{
    return _color;
}

void Engine3DRadSpace::Graphics::Primitives::Box::SetColor(const Engine3DRadSpace::Color &color)
{
    _color = color;

    auto verts = _createVerts(_box, color);
    _vertices->SetData(verts);
}

void Engine3DRadSpace::Graphics::Primitives::Box::SetTransform(const Math::Matrix &m)
{
}

void Box::Draw(Matrix &view, Matrix &projection, double dt)
{

}
