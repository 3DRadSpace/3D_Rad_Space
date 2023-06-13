#pragma once
#include "Texture2D.hpp"
#include "VertexBuffer.hpp"
#include "Shaders/SpriteShader.hpp"
#include "DepthStencilState.hpp"

namespace Engine3DRadSpace::Graphics
{
	enum class SpriteBatchSortMode
	{
		/// <summary>
		/// Do not sort the sprites.
		/// </summary>
		Immediate,
		/// <summary>
		/// Sort by texture.
		/// </summary>
		SortedByTexture,
		/// <summary>
		/// Sort by depth. From front (0.0f) to back.
		/// </summary>
		SortedByDepth_FrontToBack,
		/// <summary>
		/// Sort by depth. From back (-inf) to front (0.0f).
		/// </summary>
		SortedByDepth_BackToFront,
	};

	class SpriteBatch
	{
		GraphicsDevice *_device;
		SpriteBatchSortMode _sortingMode;
		enum SpriteBatchState
		{
			Immediate,
			BeginCalled,
			EndCalled
		} _state;

		std::unique_ptr<Shaders::SpriteShader> _spriteShader;

		struct spriteBatchEntry
		{
			const unsigned textureID;
			const Math::RectangleF rectangle;
			const Color tintColor;
			const bool flipU;
			const bool flipV;
			const float depth;
			const SpriteBatchSortMode sortingMode;

			bool operator >(const spriteBatchEntry &b) const;
			bool operator <(const spriteBatchEntry &b) const;
			bool operator ==(const spriteBatchEntry &b) const;
		};

		std::multiset<spriteBatchEntry> _entries;

		std::unordered_map<unsigned, Texture2D *> _textures;

		std::array<VertexPointUV,6> _createQuad(const Engine3DRadSpace::Math::RectangleF &r, bool flipU = false, bool flipV = false);
		void _setEntry(const spriteBatchEntry &entry);
		void _prepareGraphicsDevice();

		void _drawEntry(const spriteBatchEntry& entry);
		void _drawAllEntries_SortByTexture();
		void _drawAllEntries();
		void _restoreGraphicsDevice();

		unsigned _lastID;

		ID3D11RasterizerState *_oldRasterizerState;

		std::unique_ptr<RasterizerState> _rasterizerState;
		std::unique_ptr<SamplerState> _samplerState;
		std::unique_ptr<DepthStencilState> _depthBufferState;
	public:
		SpriteBatch(GraphicsDevice *device);

		SpriteBatch(SpriteBatch &) = delete;
		SpriteBatch(SpriteBatch &&) = delete;

		void Begin(SpriteBatchSortMode sortingMode);
		void Begin(SpriteBatchSortMode sortingMode,SamplerState samplerState);

		void Draw(Texture2D* texture,const Math::Vector2 &pos,const Math::Vector2 &scale, const Color& tintColor, bool flipU, bool flipV, float depth = 0);
		void Draw(Texture2D* texture,const Math::Vector2 &pos, float rotation, const Math::Vector2 &scale, const Color& tintColor, bool flipU, bool flipV, float depth = 0);
		void End();

		void DrawQuad(Texture2D *texture);

		~SpriteBatch() = default;
	};
}