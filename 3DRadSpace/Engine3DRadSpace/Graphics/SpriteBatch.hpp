#pragma once
#include "Texture2D.hpp"
#include "VertexBuffer.hpp"
#include "Shaders/SpriteShader.hpp"
#include "DepthStencilState.hpp"
#include "FlipMode.hpp"

namespace Engine3DRadSpace::Graphics
{
	namespace Fonts
	{
		class FontRenderer;
	}

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

	class DLLEXPORT SpriteBatch
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
			unsigned textureID;
			std::pair<Math::Vector2,Math::Vector2> coords;
			Math::RectangleF uvSource;
			Color tintColor;
			bool flipU;
			bool flipV;
			float rotation;
			float depth;
			SpriteBatchSortMode sortingMode;

			bool operator >(const spriteBatchEntry &b) const;
			bool operator <(const spriteBatchEntry &b) const;
			bool operator ==(const spriteBatchEntry &b) const;
		};

		std::multiset<spriteBatchEntry> _entries;

		std::unordered_map<unsigned, Texture2D *> _textures;

		static std::array<VertexPointUV,6> _createQuad(const Math::RectangleF &r, bool flipU = false, bool flipV = false);
		static std::array<VertexPointUV, 6> _createQuad(const Math::Vector2& a, const Math::Vector2& b, const Math::Vector2& c, const Math::Vector2& d, bool flipU, bool flipV,
														const Math::RectangleF uvRect = Math::RectangleF(0.0f,0.0f,1.0f,1.0f));
		void _setEntry(const spriteBatchEntry &entry);
		void _prepareGraphicsDevice();

		void _drawEntry(const spriteBatchEntry& entry);
		void _drawAllEntries_SortByTexture();
		void _drawAllEntries();
		void _restoreGraphicsDevice();

		unsigned _lastID;

#ifdef USING_DX11
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _oldRasterizerState;

		Microsoft::WRL::ComPtr<ID3D11BlendState> _oldBlendState;
		float _oldBlendFactor[4];
		unsigned _oldSampleMask;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _oldStencilState;
		unsigned _oldStencilRef;
#endif
		std::unique_ptr<RasterizerState> _rasterizerState;
		std::unique_ptr<SamplerState> _samplerState;
		std::unique_ptr<DepthStencilState> _depthBufferState;
		std::unique_ptr<BlendState> _blendState;
	public:
		SpriteBatch(GraphicsDevice *device);

		SpriteBatch(SpriteBatch &) = delete;
		SpriteBatch(SpriteBatch &&) noexcept = default;

		SpriteBatch& operator=(SpriteBatch &) = delete;
		SpriteBatch &operator=(SpriteBatch &&) noexcept = default;

		void Begin(SpriteBatchSortMode sortingMode);
		void Begin(SpriteBatchSortMode sortingMode,SamplerState samplerState);
		
		void DrawNormalized(Texture2D* texture, const Math::RectangleF& coords, const Math::RectangleF& source = Math::RectangleF(0.0f, 0.0f, 1.0f, 1.0f), Color tintColor = Colors::White, float rotation = 0.0f, FlipMode flipMode = FlipMode::None, float depth = 0);
		void DrawNormalized(Texture2D* texture, const Math::RectangleF& coords, const Math::Rectangle source, Color tintColor = Colors::White, float rotation = 0.0f, FlipMode flipMode = FlipMode::None, float depth = 0);

		void Draw(Texture2D* texture, const Math::Rectangle& coords, const Math::Rectangle& source, Color tintColor = Colors::White, float rotation = 0.0f, FlipMode flipMode = FlipMode::None, float depth = 0);
		void Draw(Texture2D* texture, const Math::Rectangle& coords, Color tintColor = Colors::White, float rotation = 0.0f, FlipMode flipMode = FlipMode::None, float depth = 0);

		void End();

		~SpriteBatch() = default;

		friend class ::Engine3DRadSpace::Graphics::Fonts::FontRenderer;
	};
}