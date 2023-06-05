#include "SpriteBatch.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

void Engine3DRadSpace::Graphics::SpriteBatch::drawEntry(const spriteBatchEntry &entry)
{
	/*
		VertexPointUV{Vector2(0.0, 0.0), Vector2(0, 1)},
		VertexPointUV{Vector2(0.0, 0.5), Vector2(0, 0)},
		VertexPointUV{Vector2(0.5, 0.5), Vector2(1, 0)},

		VertexPointUV{Vector2(0.0, 0.0), Vector2(0,1)},
		VertexPointUV{Vector2(0.5, 0.5), Vector2(1,0)},
		VertexPointUV{Vector2(0.5, 0.0), Vector2(1,1)}
	*/

	/*
		B -- C
		|  / |
		| /  |
		A -- D

		(winding order is clockwise.)
		A -> B -> C 
		A -> C -> D
	*/
	Vector2 a = entry.rectangle.BottomLeft();
	a = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(a);

	Vector2 b = entry.rectangle.TopLeft();
	b = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(b);

	Vector2 c = entry.rectangle.TopRight();
	c = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(c);

	Vector2 d = entry.rectangle.BottomRight();
	d = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(d);

	std::array<VertexPointUV, 6> quad = 
	{
		VertexPointUV{a, Vector2(0, 1)},
		VertexPointUV{b, Vector2(0, 0)},
		VertexPointUV{c, Vector2(1, 0)},

		VertexPointUV{a, Vector2(0,1)},
		VertexPointUV{c, Vector2(1,0)},
		VertexPointUV{d, Vector2(1,1)}
	};

	VertexBufferV<VertexPointUV> vertexBuffer(gdevice, quad);

	spriteShader->SetBasic();

	SpriteShader::Data data{};
	data.flipU = entry.flipU;
	data.flipV = entry.flipV;
	data.tintColor = entry.tintColor;

#ifdef _DX11
	gdevice->context->RSGetState(&oldRasterizerState);
#endif

	spriteShader->SetData(data);
	spriteShader->SetSamplerState(samplerState.get());

	spriteShader->SetTexture(textures[entry.textureID]);
	gdevice->SetRasterizerState(rasterizerState.get());
	gdevice->SetTopology(VertexTopology::TriangleList);
	vertexBuffer.Draw();

#ifdef _DX11
	gdevice->context->RSSetState(oldRasterizerState);
#endif
}

Engine3DRadSpace::Graphics::SpriteBatch::SpriteBatch(GraphicsDevice *device) :
	gdevice(device),
	oldRasterizerState(nullptr),
	state(EndCalled)
{
	rasterizerState = std::make_unique<RasterizerState>(device, RasterizerFillMode::Solid);
	samplerState = std::make_unique<SamplerState>(SamplerState::LinearClamp(device));
	spriteShader = std::make_unique<Shaders::SpriteShader>(device);
}

void Engine3DRadSpace::Graphics::SpriteBatch::Begin(SpriteBatchSortMode sortingMode)
{
	if(sortingMode == SpriteBatchSortMode::Immediate)
	{
		if(state == BeginCalled) throw std::exception("Begin() was already called with the sorting mode set by texture!");

		state = Immediate;
		return;
	}
	else if(sortingMode == SpriteBatchSortMode::SortedByTexture)
	{
		if(state == Immediate) return;
		if(state == Ready)
		{
			state = BeginCalled;
			return;
		}
		else throw std::exception("Begin() was called when the sprite batch was waiting for entries.");
	}
}

void Engine3DRadSpace::Graphics::SpriteBatch::Draw(Texture2D *texture, const Math::Vector2 &pos, const Math::Vector2 &scale, const Color &tintColor, bool flipU, bool flipV)
{
	if(state == Immediate)
	{
		textures[1] = texture;
		spriteBatchEntry tempEntry
		{
			.textureID = 1u,
			.rectangle = RectangleF(pos.X, pos.Y, scale.X, scale.Y),
			.tintColor = tintColor,
			.flipU = flipU,
			.flipV = flipV,
		};

		drawEntry(tempEntry);
		textures.clear();
	}
	else if(state == BeginCalled)
	{

	}
	if(state == EndCalled) throw std::exception("Cannot draw textures when End() was called.");
}

void Engine3DRadSpace::Graphics::SpriteBatch::End()
{
	if(state == BeginCalled)
	{
		state = EndCalled;
		textures.clear();
	}
}
