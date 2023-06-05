#include "SpriteBatch.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

std::array<VertexPointUV,6> SpriteBatch::_createQuad(const RectangleF &r)
{
/*
	B -- C
	|  / |
	| /  |
	A -- D

	(winding order is clockwise.)
	A -> B -> C
	A -> C -> D
*/
	Vector2 a = r.BottomLeft();
	a = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(a);

	Vector2 b = r.TopLeft();
	b = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(b);

	Vector2 c = r.TopRight();
	c = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(c);

	Vector2 d = r.BottomRight();
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

	return quad;
}

void Engine3DRadSpace::Graphics::SpriteBatch::_setEntry(const spriteBatchEntry &entry)
{
	SpriteShader::Data data{};
	data.flipU = entry.flipU;
	data.flipV = entry.flipV;
	data.tintColor = entry.tintColor;

	_spriteShader->SetData(data);
	_spriteShader->SetTexture(_textures[entry.textureID]);
}

void Engine3DRadSpace::Graphics::SpriteBatch::_prepareGraphicsDevice()
{
	_spriteShader->SetBasic();
	_spriteShader->SetSamplerState(_samplerState.get());

	_device->SetRasterizerState(_rasterizerState.get());
	_device->SetTopology(VertexTopology::TriangleList);
}

void Engine3DRadSpace::Graphics::SpriteBatch::_drawEntry(const spriteBatchEntry &entry)
{
	auto quad = _createQuad(entry.rectangle);
	VertexBufferV<VertexPointUV> vertexBuffer(_device, quad);

	_prepareGraphicsDevice();
	_setEntry(entry);
	vertexBuffer.Draw();
	_restoreGraphicsDevice();
}

void Engine3DRadSpace::Graphics::SpriteBatch::_drawAllEntries_SortByTexture()
{
	std::vector<std::unique_ptr<VertexBufferV<VertexPointUV>>> vertexBuffers;
	unsigned _lastID = 1;

	std::vector<VertexPointUV> currentVertices;
	_prepareGraphicsDevice();
	for(auto &entry : _entries)
	{
		if(entry.textureID == _lastID)
		{
			//currentVertices.insert(currentVertices.end(), _createQuad())
		}
		else
		{

		}
	}


}

void Engine3DRadSpace::Graphics::SpriteBatch::_restoreGraphicsDevice()
{
#ifdef _DX11
	_device->_context->RSSetState(_oldRasterizerState);
#endif
}

Engine3DRadSpace::Graphics::SpriteBatch::SpriteBatch(GraphicsDevice *device) :
	_device(device),
	_oldRasterizerState(nullptr),
	_state(Immediate),
	_lastID(1)
{
	_rasterizerState = std::make_unique<RasterizerState>(device, RasterizerFillMode::Solid);
	_samplerState = std::make_unique<SamplerState>(SamplerState::PointWrap(device));
	_spriteShader = std::make_unique<Shaders::SpriteShader>(device);
}

void Engine3DRadSpace::Graphics::SpriteBatch::Begin(SpriteBatchSortMode sortingMode)
{
	if(sortingMode == SpriteBatchSortMode::Immediate)
	{
		if(_state == BeginCalled) throw std::exception("Begin() was already called with the sorting mode set by texture!");

		_state = Immediate;
		return;
	}
	else if(sortingMode == SpriteBatchSortMode::SortedByTexture)
	{
		if(_state == Immediate) return;
		if(_state == Ready)
		{
			_state = BeginCalled;
			return;
		}
		else throw std::exception("Begin() was called when the sprite batch was waiting for entries.");
	}
}

void Engine3DRadSpace::Graphics::SpriteBatch::Begin(SpriteBatchSortMode sortingMode, SamplerState &&samplerState)
{
	_samplerState.reset();
	_samplerState = std::make_unique<SamplerState>(std::move(samplerState));
	Begin(sortingMode);
}

void SpriteBatch::Draw(Texture2D *texture, const Math::Vector2 &pos, const Math::Vector2 &scale, const Color &tintColor, bool flipU, bool flipV, float depth)
{
	if(_state == Immediate)
	{
		_textures[1] = texture;
		spriteBatchEntry tempEntry
		{
			.textureID = 1u,
			.rectangle = RectangleF(pos.X, pos.Y, scale.X, scale.Y),
			.tintColor = tintColor,
			.flipU = flipU,
			.flipV = flipV,
			.depth = depth,
			.sortingMode = SpriteBatchSortMode::Immediate
		};

		_drawEntry(tempEntry);
		_textures.clear();
	}
	else if(_state == BeginCalled)
	{
		_entries.insert(
			spriteBatchEntry
			{
				.textureID = _lastID,
				.rectangle = RectangleF(pos.X, pos.Y, scale.X, scale.Y),
				.tintColor = tintColor,
				.flipU = flipU,
				.flipV = flipV,
				.depth = depth,
				.sortingMode = _sortingMode
			}
		);
	}
	if(_state == EndCalled) throw std::exception("Cannot draw textures when End() was called.");
}

void Engine3DRadSpace::Graphics::SpriteBatch::End()
{
	if(_state == BeginCalled)
	{
		//draw all entries
		if(_sortingMode == SpriteBatchSortMode::SortedByTexture)
		{
			_drawAllEntries_SortByTexture();
		}

		_state = EndCalled;
		_lastID = 1;
		_textures.clear();
	}
}

bool Engine3DRadSpace::Graphics::SpriteBatch::spriteBatchEntry::operator>(const spriteBatchEntry &b) const
{
	switch(sortingMode)
	{
		case SpriteBatchSortMode::Immediate:
		case SpriteBatchSortMode::SortedByTexture:
			return textureID > b.textureID;
		case SpriteBatchSortMode::SortedByDepth_FrontToBack:
			return depth > b.depth;
		case SpriteBatchSortMode::SortedByDepth_BackToFront:
		default:
			return depth < b.depth;
	}
}

bool Engine3DRadSpace::Graphics::SpriteBatch::spriteBatchEntry::operator<(const spriteBatchEntry &b) const
{
	switch(sortingMode)
	{
		case SpriteBatchSortMode::Immediate:
		case SpriteBatchSortMode::SortedByTexture:
			return textureID < b.textureID;
		case SpriteBatchSortMode::SortedByDepth_FrontToBack:
			return depth < b.depth;
		case SpriteBatchSortMode::SortedByDepth_BackToFront:
		default:
			return depth > b.depth;
	}
}

bool Engine3DRadSpace::Graphics::SpriteBatch::spriteBatchEntry::operator==(const spriteBatchEntry &b) const
{
	return textureID == b.textureID && flipU == b.flipU && flipV == b.flipV;
}