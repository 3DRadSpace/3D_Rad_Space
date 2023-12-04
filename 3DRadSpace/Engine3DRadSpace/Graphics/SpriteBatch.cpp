#include "SpriteBatch.hpp"
#include "../Math/Matrix3x3.hpp"
#include "../Math/Math.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

constexpr Math::RectangleF _fullDefaultUV(0.0f, 0.0f, 1.0f, 1.0f);

std::array<VertexPointUV,6> SpriteBatch::_createQuad(const RectangleF &r, bool flipU, bool flipV)
{
/*
	B -- C
	|  / |
	| /  |
	A -- D

	(winding order is clockwise.)
	A -> B -> C
	C -> D -> A
*/
	Vector2 a = r.BottomLeft();
	a = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(a);

	Vector2 b = r.TopLeft();
	b = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(b);

	Vector2 c = r.TopRight();
	c = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(c);

	Vector2 d = r.BottomRight();
	d = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(d);

	return _createQuad(a, b, c, d, flipU, flipV);
}

std::array<VertexPointUV, 6> SpriteBatch::_createQuad(const Math::Vector2& a, const Math::Vector2& b, const Math::Vector2& c, const Math::Vector2& d, bool flipU, bool flipV, const Math::RectangleF uvRect)
{
	Vector2 uv_a = uvRect.BottomLeft();
	Vector2 uv_b = uvRect.TopLeft();
	Vector2 uv_c = uvRect.TopRight();
	Vector2 uv_d = uvRect.BottomRight();

	std::array quad =
	{
		VertexPointUV{Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(a), uv_a},
		VertexPointUV{Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(b), uv_b},
		VertexPointUV{Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(c), uv_c},

		VertexPointUV{Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(c), uv_c},
		VertexPointUV{Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(d), uv_d},
		VertexPointUV{Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(a), uv_a}
	};

	return quad;
}

void SpriteBatch::_setEntry(const spriteBatchEntry &entry)
{
	SpriteShader::Data data;
	data.FlipU = entry.flipU;
	data.FlipV = entry.flipV;
	data.TintColor = entry.tintColor;

	_spriteShader->SetData(data);
	_spriteShader->SetTexture(_textures[entry.textureID]);
}

void SpriteBatch::_prepareGraphicsDevice()
{
	_spriteShader->SetBasic();
	_spriteShader->SetSamplerState(_samplerState.get());

#ifdef USING_DX11
	_device->_context->RSGetState(&_oldRasterizerState);
	_device->_context->OMGetBlendState(&_oldBlendState, _oldBlendFactor, &_oldSampleMask);
	_device->_context->OMGetDepthStencilState(&_oldStencilState, &_oldStencilRef);
#endif
	_device->SetRasterizerState(_rasterizerState.get());
	_device->SetTopology(VertexTopology::TriangleList);
	_device->SetBlendState(_blendState.get());
}

void SpriteBatch::_drawEntry(const spriteBatchEntry &entry)
{
	auto [min, max] = entry.coords;

	auto center = (max + min) / 2.0f;
	min -= center;
	max -= center;

	auto rotation = Matrix3x3::CreateRotation(Math::ToRadians(entry.rotation));

	min += center;
	max += center;

	Vector2 a(min.X, max.Y); //bottom left
	Vector2 b(min.X, min.X); //top left
	Vector2 c(max.X, min.Y); //top right
	Vector2 d(max.X, max.Y); //bottom right

	a -= center;
	b -= center;
	c -= center;
	d -= center;
	
	a.Transform(rotation);
	b.Transform(rotation);
	c.Transform(rotation);
	d.Transform(rotation);

	a += center;
	b += center;
	c += center;
	d += center;

	auto quad = _createQuad(a, b, c, d, entry.flipU, entry.flipV, entry.uvSource);
	VertexBufferV<VertexPointUV> vertexBuffer(_device, quad);

	_prepareGraphicsDevice();
	_setEntry(entry);
	vertexBuffer.Draw();
	_restoreGraphicsDevice();
}

void SpriteBatch::_drawAllEntries_SortByTexture()
{
	std::vector<std::unique_ptr<VertexBufferV<VertexPointUV>>> vertexBuffers;
	unsigned lastID = 1;

	std::vector<VertexPointUV> currentVertices;
	_prepareGraphicsDevice();
	for(auto &entry : _entries)
	{
		if(entry.textureID == lastID)
		{
			auto& [min, max] = entry.coords;
			auto quad = _createQuad(min.X, min.Y, max.X, max.Y, entry.flipU, entry.flipV);
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

void SpriteBatch::_drawAllEntries()
{
	_prepareGraphicsDevice();

	for(auto& entry : _entries)
	{
		_drawEntry(entry);
	}
	_restoreGraphicsDevice();
}

void SpriteBatch::_restoreGraphicsDevice()
{
#ifdef USING_DX11
	_device->_context->RSSetState(_oldRasterizerState.Get());
	_device->_context->OMSetBlendState(_oldBlendState.Get(), _oldBlendFactor, _oldSampleMask);
	_device->_context->OMSetDepthStencilState(_oldStencilState.Get(), _oldStencilRef);
#endif
}

SpriteBatch::SpriteBatch(GraphicsDevice *device) :
	_device(device),
	_sortingMode(SpriteBatchSortMode::Immediate),
	_state(Immediate),
	_lastID(1),
	_oldBlendFactor{},
	_oldSampleMask(0),
	_oldStencilRef(0)
{
	_spriteShader = std::make_unique<SpriteShader>(device);

	_rasterizerState = std::make_unique<RasterizerState>(device, RasterizerFillMode::Solid);
	_samplerState = std::make_unique<SamplerState>(SamplerState::PointWrap(device));
	_depthBufferState = std::make_unique<DepthStencilState>(DepthStencilState::DepthNone(device));
	_blendState = std::make_unique<BlendState>(BlendState::AlphaBlend(device));
}

void SpriteBatch::Begin(SpriteBatchSortMode sortingMode)
{
	if(sortingMode == SpriteBatchSortMode::Immediate)
	{
		if(_state == BeginCalled) throw std::logic_error("Begin() was already called with the sorting mode set by texture!");

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
		else throw std::logic_error("Begin() was called when the sprite batch was waiting for entries.");
	}
}

void SpriteBatch::Begin(SpriteBatchSortMode sortingMode, SamplerState samplerState)
{
	_samplerState.reset();
	_samplerState = std::make_unique<SamplerState>(std::move(samplerState));
	Begin(sortingMode);
}

void SpriteBatch::DrawNormalized(Texture2D* texture, const Math::RectangleF& coords, const Math::RectangleF& source, Color tintColor, float rotation, FlipMode flipMode, float depth)
{
	Vector2 min = coords.TopLeft();
	Vector2 max = coords.BottomRight();

	if (_state == Immediate)
	{
		_textures[1] = texture;
		spriteBatchEntry tempEntry
		{
			.textureID = 1u,
			.coords = std::make_pair(min, max),
			.uvSource = source,
			.tintColor = tintColor,
			.flipU = static_cast<bool>(FlipMode::FlipHorizontally & flipMode),
			.flipV = static_cast<bool>(FlipMode::FlipVertically & flipMode),
			.rotation = rotation,
			.depth = depth,
			.sortingMode = SpriteBatchSortMode::Immediate
		};

		_drawEntry(tempEntry);
		_textures.clear();
	}
	else if (_state == BeginCalled)
	{
		_entries.insert(
			spriteBatchEntry
			{
				.textureID = _lastID,
				.coords = std::make_pair(min, max),
				.uvSource = source,
				.tintColor = tintColor,
				.flipU = static_cast<bool>(FlipMode::FlipHorizontally & flipMode),
				.flipV = static_cast<bool>(FlipMode::FlipVertically & flipMode),
				.rotation = rotation,
				.depth = depth,
				.sortingMode = SpriteBatchSortMode::Immediate
			}
		);
	}
	if (_state == EndCalled) throw std::logic_error("Cannot draw textures when End() was called.");
}

void SpriteBatch::DrawNormalized(Texture2D* texture, const Math::RectangleF& coords, const Math::Rectangle source, Color tintColor, float rotation, FlipMode flipMode, float depth)
{
	DrawNormalized(texture, coords, _fullDefaultUV, tintColor, rotation, flipMode, depth);
}

void SpriteBatch::Draw(Texture2D* texture, const Math::Rectangle& coords, const Math::Rectangle& source, Color tintColor, float rotation, FlipMode flipMode, float depth)
{
	auto screenSize = _device->Resolution();
	RectangleF nCoords =
	{
		static_cast<float>(coords.X) / static_cast<float>(screenSize.X),
		static_cast<float>(coords.Y) / static_cast<float>(screenSize.Y),
		static_cast<float>(coords.Width) / static_cast<float>(screenSize.X),
		static_cast<float>(coords.Height) / static_cast<float>(screenSize.Y),
	};

	auto textureSize = texture->Size();
	RectangleF nSource =
	{
		static_cast<float>(source.X) / static_cast<float>(textureSize.X),
		static_cast<float>(source.Y) / static_cast<float>(textureSize.Y),
		static_cast<float>(source.Width) / static_cast<float>(textureSize.X),
		static_cast<float>(source.Height) / static_cast<float>(textureSize.Y),
	};

	DrawNormalized(texture, nCoords, nSource, tintColor, rotation, flipMode, depth);
}

void SpriteBatch::Draw(Texture2D* texture, const Math::Rectangle& coords, Color tintColor, float rotation, FlipMode flipMode, float depth)
{
	auto screenSize = _device->Resolution();
	RectangleF nCoords =
	{
		static_cast<float>(coords.X) / static_cast<float>(screenSize.X),
		static_cast<float>(coords.Y) / static_cast<float>(screenSize.Y),
		static_cast<float>(coords.Width) / static_cast<float>(screenSize.X),
		static_cast<float>(coords.Height) / static_cast<float>(screenSize.Y),
	};

	DrawNormalized(texture, nCoords, _fullDefaultUV, tintColor, rotation, flipMode, depth);
}

void SpriteBatch::End()
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

bool SpriteBatch::spriteBatchEntry::operator>(const spriteBatchEntry &b) const
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

bool SpriteBatch::spriteBatchEntry::operator<(const spriteBatchEntry &b) const
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

bool SpriteBatch::spriteBatchEntry::operator==(const spriteBatchEntry &b) const
{
	return textureID == b.textureID && flipU == b.flipU && flipV == b.flipV;
}