#include "Box.hpp"
#include "../Shaders/BlankShader.hpp"
#include "../../Content/ShaderManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

std::array<VertexPositionColor, 8> Box::_createVerts(const BoundingBox&b, const Color& color)
{
    return std::array<VertexPositionColor, 8>
    {
        VertexPositionColor{ b.Position, color }, // 0
        VertexPositionColor{ b.Position + Vector3(b.Scale.X, 0, 0), color }, // 1
        VertexPositionColor{ b.Position + Vector3(0, b.Scale.Y, 0), color }, // 2
        VertexPositionColor{ b.Position + Vector3(0, 0, b.Scale.Z), color }, // 3
        VertexPositionColor{ b.Position + Vector3(b.Scale.X, b.Scale.Y, 0), color }, // 4
        VertexPositionColor{ b.Position + Vector3(0, b.Scale.Y, b.Scale.Z), color }, // 5
        VertexPositionColor{ b.Position + Vector3(b.Scale.X, 0, b.Scale.Z), color }, // 6
        VertexPositionColor{ b.Position + b.Scale, color }, // 7
    };
}

Box::Box(GraphicsDevice *device, const BoundingBox&b, Color color) :
    _device(device)
{
    auto box_vertices = _createVerts(b, color);
    _vertices = std::make_unique<VertexBufferV<VertexPositionColor>>(device, box_vertices);

    std::array<unsigned, 36> indices =
    {
        //-Y face
        0, 3, 6,
        0, 6, 1,
        //+Y face
        7, 5, 2,
        4, 7, 2, 
        // -X face
        0, 2, 5,
        0, 5, 3,
        //+X face
        7, 4, 1,
        6, 7, 1,
        //-Z face
        1, 4, 2,
        1, 2, 0,
        //+Z face
        3, 5, 7,
        3, 7, 6
        
    };
    _indices = std::make_unique<IndexBuffer>(device, indices);

    _shader = ShaderManager::LoadShader<BlankShader>(device);
}

BoundingBox Box::GetBoundingBox()
{
    return _box;
}

void Box::SetBoundingBox(const BoundingBox&b)
{
    _box = b;

    auto box_vertices = _createVerts(b, _color);
    _vertices->SetData(box_vertices);
}

Color Box::GetColor()
{
    return _color;
}

void Box::SetColor(const Color&color)
{
    _color = color;

    auto verts = _createVerts(_box, color);
    _vertices->SetData(verts);
}

void Box::SetTransform(const Matrix4x4&m)
{
    _worldMat = m;
}

void Box::Draw(Matrix4x4 &view, Matrix4x4 &projection, double dt)
{
    _shader->SetBasic();
    Matrix4x4 mvp = _worldMat * view * projection;
    _shader->SetTransformation(mvp);
    
    _device->SetTopology(VertexTopology::TriangleList);
    _device->DrawVertexBufferWithindices(_vertices.get(), _indices.get());
}
