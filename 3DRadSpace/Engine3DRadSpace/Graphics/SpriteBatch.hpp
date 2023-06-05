#pragma once
#include "Texture2D.hpp"
#include "VertexBuffer.hpp"
#include "Shaders/SpriteShader.hpp"
#include <CommonStates.h>

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
		GraphicsDevice *gdevice;
		SpriteBatchSortMode sortingMode;
		enum SpriteBatchState
		{
			Immediate,
			Ready,
			BeginCalled,
			EndCalled
		} state;

		std::unique_ptr<Shaders::SpriteShader> spriteShader;
		struct spriteBatchEntry
		{
			const unsigned textureID;
			const Math::RectangleF rectangle;
			const Color tintColor;
			const bool flipU;
			const bool flipV;
		};
		std::vector<spriteBatchEntry> entries;
		std::unordered_map<unsigned, Texture2D *> textures;

		void drawEntry(const spriteBatchEntry& entry);

		ID3D11RasterizerState *oldRasterizerState;

		std::unique_ptr<RasterizerState> rasterizerState;
		std::unique_ptr<SamplerState> samplerState;
	public:
		SpriteBatch(GraphicsDevice *device);

		SpriteBatch(SpriteBatch &) = delete;
		SpriteBatch(SpriteBatch &&) = delete;

		void Begin(SpriteBatchSortMode sortingMode);
		void Draw(Texture2D* texture,const Math::Vector2 &pos,const Math::Vector2 &scale, const Color& tintColor, bool flipU, bool flipV);
		void End();

		~SpriteBatch() = default;
	};
}