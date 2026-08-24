#pragma once
#include "ITexture2D.hpp"
#include "IVertexBuffer.hpp"
#include "IIndexBuffer.hpp"
#include "IDepthStencilState.hpp"
#include "IRasterizerState.hpp"
#include "IBlendState.hpp"
#include "ISamplerState.hpp"
#include "FlipMode.hpp"
#include "Font.hpp"
#include "Effect.hpp"
#include "../Core/IService.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents how the sprite batch sorts the submitted sprites.
	/// </summary>
	enum class SpriteBatchSortMode
	{
		/// <summary>
		/// Do not sort the sprites.
		/// </summary>
		Immediate,
		/// <summary>
		/// Sort by texture. Use this if you want to optimize the number of draw calls.
		/// </summary>
		SortedByTexture,
		/// <summary>
		/// Sort by depth. From front (0.0f) to back (-inf).
		/// </summary>
		SortedByDepth_FrontToBack,
		/// <summary>
		/// Sort by depth. From back (-inf) to front (0.0f).
		/// </summary>
		SortedByDepth_BackToFront,
	};

	/// <summary>
	/// A SpriteBatch renders 2D sprites with a specified order.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT SpriteBatch : public IService
	{
		IGraphicsDevice *_device;
		SpriteBatchSortMode _sortingMode;
		enum SpriteBatchState
		{
			Immediate,
			BeginCalled,
			EndCalled
		} _state;

		Effect* _spriteShader;

		std::unique_ptr<IVertexBuffer> _vertexBuffer;
		std::unique_ptr<IIndexBuffer> _indexBuffer;
		size_t _capacity = 256;

		struct spriteBatchEntry
		{
			unsigned textureID;
			std::pair<Math::Vector2,Math::Vector2> coords;
			Math::RectangleF uvSource;
			Math::Color tintColor;
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

		std::vector<ITexture2D*> _textures;

		static std::array<VertexPointUVColor, 4> _createQuad(
			const Math::RectangleF &r,
			bool flipU = false,
			bool flipV = false,
			const Math::Color &tintColor = Math::Colors::White,
			const Math::RectangleF &uvRect = Math::RectangleF(0.0f,0.0f,1.0f,1.0f)
		);
		
		static std::array<VertexPointUVColor, 4> _createQuad(
			const Math::Vector2& a,
			const Math::Vector2& b,
			const Math::Vector2& c,
			const Math::Vector2& d,
			bool flipU,
			bool flipV,
			const Math::Color &tintColor = Math::Colors::White, 
			const Math::RectangleF &uvRect = Math::RectangleF(0.0f,0.0f,1.0f,1.0f)
		);
		
		static std::array<unsigned, 6> _createIndexQuad(unsigned offset);
		
		void _prepareGraphicsDevice();

		void _drawEntry(const spriteBatchEntry& entry);
		void _drawAllEntries_SortByTexture();
		void _drawAllEntries();
		void _restoreGraphicsDevice();

		std::unique_ptr<IRasterizerState> _oldRasterizerState;

		std::unique_ptr<IBlendState> _oldBlendState;
		float _oldBlendFactor[4];
		unsigned _oldSampleMask;

		IDepthStencilState* _oldStencilState;
		unsigned _oldStencilRef;

		std::unique_ptr<IRasterizerState> _rasterizerState;
		std::unique_ptr<ISamplerState> _samplerState;
		std::unique_ptr<IDepthStencilState> _depthBufferState;
		std::unique_ptr<IBlendState> _blendState;
	public:
		/// <summary>
		/// Constructs a sprite batch.
		/// </summary>
		/// <param name="device">Graphics device</param>
		SpriteBatch(IGraphicsDevice *device);

		SpriteBatch(SpriteBatch &) = delete;
		SpriteBatch(SpriteBatch &&) noexcept = default;

		SpriteBatch& operator=(SpriteBatch &) = delete;
		SpriteBatch& operator=(SpriteBatch &&) noexcept = default;

		/// <summary>
		/// Begins a sprite batch with the specified sorting mode.
		/// </summary>
		/// <param name="sortingMode">The sorting mode to use for the sprite batch.</param>
		void Begin(SpriteBatchSortMode sortingMode = SpriteBatchSortMode::Immediate);
		/// <summary>
		/// Begins a sprite batch with the specified sorting mode and sampler state.
		/// </summary>
		/// <param name="sortingMode">The sorting mode to use for the sprite batch.</param>
		/// <param name="samplerState">The sampler state to use for the sprite batch.</param>
		void Begin(SpriteBatchSortMode sortingMode, std::unique_ptr<ISamplerState> &&samplerState);
		
		/// <summary>
		/// Draws a sprite with normalized coordinates and source rectangle.
		/// </summary>
		/// <param name="texture">The texture to draw.</param>
		/// <param name="coords">The normalized coordinates of the sprite.</param>
		/// <param name="source">The source rectangle of the texture.</param>
		/// <param name="tintColor">The tint color to apply to the sprite.</param>
		/// <param name="rotation">The rotation of the sprite in radians.</param>
		/// <param name="flipMode">The flip mode to apply to the sprite.</param>
		/// <param name="depth">The depth of the sprite.</param>
		void DrawNormalized(
			ITexture2D* texture,
			const Math::RectangleF& coords,
			const Math::RectangleF& source = Math::RectangleF(0.0f, 0.0f, 1.0f, 1.0f),
			const Math::Color& tintColor = Math::Colors::White,
			float rotation = 0.0f, 
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);

		/// <summary>
		///	Draws a sprite with normalized coordinates and source rectangle.
		/// </summary>
		/// <param name="texture">The texture to draw.</param>
		/// <param name="coords">The normalized coordinates of the sprite.</param>
		/// <param name="source">The source rectangle of the texture.</param>
		/// <param name="tintColor">The tint color to apply to the sprite.</param>
		/// <param name="rotation">The rotation of the sprite in radians.</param>
		/// <param name="flipMode">The flip mode to apply to the sprite.</param>
		/// <param name="depth">The depth of the sprite.</param>
		void DrawNormalized(
			ITexture2D* texture,
			const Math::RectangleF& coords,
			const Math::Rectangle& source,
			const Math::Color& tintColor = Math::Colors::White,
			float rotation = 0.0f,
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);

		/// <summary>
		/// Draws a sprite with pixel screen coordinates and source rectangle.
		/// </summary>
		/// <param name="texture">The texture to draw.</param>
		/// <param name="coords">The pixel screen coordinates of the sprite.</param>
		/// <param name="source">The source rectangle of the texture.</param>
		/// <param name="tintColor">The tint color to apply to the sprite.</param>
		/// <param name="rotation">The rotation of the sprite in radians.</param>
		/// <param name="flipMode">The flip mode to apply to the sprite.</param>
		/// <param name="depth">The depth of the sprite.</param>
		void Draw(
			ITexture2D* texture,
			const Math::Rectangle& coords,
			const Math::Rectangle& source,
			const Math::Color& tintColor = Math::Colors::White,
			float rotation = 0.0f,
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);
		/// <summary>
		/// Draws a sprite with pixel screen coordinates and no source rectangle.
		/// </summary>
		/// <param name="texture">The texture to draw.</param>
		/// <param name="coords">The pixel screen coordinates of the sprite.</param>
		/// <param name="tintColor">The tint color to apply to the sprite.</param>
		/// <param name="rotation">The rotation of the sprite in radians.</param>
		/// <param name="flipMode">The flip mode to apply to the sprite.</param>
		/// <param name="depth">The depth of the sprite.</param>
		void Draw(
			ITexture2D* texture, 
			const Math::Rectangle& coords,
			const Math::Color &tintColor = Math::Colors::White,
			float rotation = 0.0f,
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);

		/// <summary>
		/// Draws a string using the specified font, position, size, and other parameters.
		/// </summary>
		/// <param name="font">The font to use for drawing the text.</param>
		/// <param name="text">The text to draw.</param>
		/// <param name="pos">The position to draw the text.</param>
		/// <param name="size">The size of the text.</param>
		/// <param name="tintColor">The tint color to apply to the text.</param>
		/// <param name="rotation">The rotation of the text in radians.</param>
		/// <param name="flipMode">The flip mode to apply to the text.</param>
		/// <param name="depth">The depth of the text.</param>
		void DrawString(
			Font* font,
			const std::string& text, 
			const Math::Vector2& pos,
			float size,
			const Math::Color &tintColor = Math::Colors::White,
			float rotation = 0.0f,
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);

		/// <summary>
		/// Draws a string using the specified font, position, size, and other parameters.
		/// </summary>
		/// <param name="font">The font to use for drawing the text.</param>
		/// <param name="text">The text to draw.</param>
		/// <param name="pos">The position to draw the text.</param>
		/// <param name="size">The size of the text.</param>
		/// <param name="tintColor">The tint color to apply to the text.</param>
		/// <param name="rotation">The rotation of the text in radians.</param>
		/// <param name="flipMode">The flip mode to apply to the text.</param>
		/// <param name="depth">The depth of the text.</param>
		void DrawString(
			Font* font, 
			const std::string& text,
			const Math::Point& pos, 
			float size, 
			const Math::Color &tintColor = Math::Colors::White, 
			float rotation = 0.0f,
			FlipMode flipMode = FlipMode::None,
			float depth = 0
		);

		/// <summary>
		///	Stop receiving draw commands, submit all data to the GPU then flush the internal data of this instance.
		/// </summary>
		void End();

		~SpriteBatch() override = default;
	};
}