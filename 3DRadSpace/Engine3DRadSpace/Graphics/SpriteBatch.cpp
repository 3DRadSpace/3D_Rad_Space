#include "SpriteBatch.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

std::array<VertexPointUV,6> SpriteBatch::_createQuad(const RectangleF &r, bool flipU, bool flipV)
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

	Vector2 uv_a = Vector2(0, 1);
	Vector2 uv_b = Vector2(0, 0);
	Vector2 uv_c = Vector2(1, 0);
	Vector2 uv_d = Vector2(1, 1);

	if(flipU)
	{
		uv_a.X = 1 - uv_a.X;
		uv_b.X = 1 - uv_b.X;
		uv_c.X = 1 - uv_c.X;
		uv_d.X = 1 - uv_d.X;
	}
	if(flipV)
	{
		uv_a.Y = 1 - uv_a.Y;
		uv_b.Y = 1 - uv_b.Y;
		uv_c.Y = 1 - uv_c.Y;
		uv_d.Y = 1 - uv_d.Y;
	}

	std::array<VertexPointUV, 6> quad =
	{
		VertexPointUV{a, uv_a},
		VertexPointUV{b, uv_b},
		VertexPointUV{c, uv_c},

		VertexPointUV{a, uv_a},
		VertexPointUV{c, uv_c},
		VertexPointUV{d, uv_d}
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

#ifdef _DX11
	_device->_context->RSGetState(&_oldRasterizerState);
	_device->_context->OMGetBlendState(&_oldBlendState, _oldBlendFactor, &_oldSampleMask);
	_device->_context->OMGetDepthStencilState(&_oldStencilState, &_oldStencilRef);
#endif
	_device->SetRasterizerState(_rasterizerState.get());
	_device->SetTopology(VertexTopology::TriangleList);
	_device->SetBlendState(_blendState.get());
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
	unsigned lastID = 1;

	std::vector<VertexPointUV> currentVertices;
	_prepareGraphicsDevice();
	for(auto &entry : _entries)
	{
		if(entry.textureID == lastID)
		{
			auto quad = _createQuad(entry.rectangle, entry.flipU, entry.flipV);
			currentVertices.insert(currentVertices.end(), quad.begin(), quad.end());
		}
		else
		{
			vertexBuffers.push_back(std::make_unique<VertexBufferV<VertexPointUV>>(_device, currentVertices));
			currentVertices.clear();
		}
	}

	vertexBuffers.push_back(std::make_unique<VertexBufferV<VertexPointUV>>(_device, currentVertices));
	currentVertices.clear();

	for(unsigned i =0; i < unsigned(vertexBuffers.size()); i++)
	{
		_spriteShader->SetTexture(this->_textures[i]);
		vertexBuffers[i]->Draw();
	}

	_restoreGraphicsDevice();
}

void Engine3DRadSpace::Graphics::SpriteBatch::_drawAllEntries()
{
	_prepareGraphicsDevice();

	for(auto& entry : _entries)
	{
		_drawEntry(entry);
	}
	_restoreGraphicsDevice();
}

void Engine3DRadSpace::Graphics::SpriteBatch::_restoreGraphicsDevice()
{
#ifdef _DX11
	_device->_context->RSSetState(_oldRasterizerState.Get());
	_device->_context->OMSetBlendState(_oldBlendState.Get(), _oldBlendFactor, _oldSampleMask);
	_device->_context->OMSetDepthStencilState(_oldStencilState.Get(), _oldStencilRef);
#endif
}

Engine3DRadSpace::Graphics::SpriteBatch::SpriteBatch(GraphicsDevice *device) :
	_device(device),
	_state(Immediate),
	_lastID(1)
{
	_spriteShader = std::make_unique<Shaders::SpriteShader>(device);

	_rasterizerState = std::make_unique<RasterizerState>(device, RasterizerFillMode::Solid);
	_samplerState = std::make_unique<SamplerState>(SamplerState::PointWrap(device));
	_depthBufferState = std::make_unique<DepthStencilState>(DepthStencilState::DepthNone(device));
	_blendState = std::make_unique<BlendState>(BlendState::AlphaBlend(device));
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
		if(_state == EndCalled)
		{
			_state = BeginCalled;
			return;
		}
		else throw std::exception("Begin() was called when the sprite batch was waiting for entries.");
	}
}

void Engine3DRadSpace::Graphics::SpriteBatch::Begin(SpriteBatchSortMode sortingMode, SamplerState samplerState)
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

void SpriteBatch::Draw(Texture2D *texture, const Math::Vector2 &pos, float rotation, const Math::Vector2 &scale, const Color &tintColor, bool flipU, bool flipV, float depth)
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
	if(_sortingMode == SpriteBatchSortMode::Immediate) return;

	if(_state == BeginCalled)
	{
		//draw all entries
		if(_sortingMode == SpriteBatchSortMode::SortedByTexture)
		{
			_drawAllEntries_SortByTexture();
		}
		else _drawAllEntries();

		_state = EndCalled;
		_lastID = 1;
		_textures.clear();
	}
}

void Engine3DRadSpace::Graphics::SpriteBatch::DrawQuad(Texture2D *texture)
{
	_textures[1] = texture;
	spriteBatchEntry tempEntry
	{
		.textureID = 1u,
		.rectangle = RectangleF(0,0,1,1),
		.tintColor = Colors::White,
		.flipU = false,
		.flipV = false,
		.depth = false,
		.sortingMode = SpriteBatchSortMode::Immediate
	};

	_drawEntry(tempEntry);
	_textures.clear();
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