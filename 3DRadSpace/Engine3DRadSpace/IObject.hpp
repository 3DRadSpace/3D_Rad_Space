#pragma once
#include "Math\Matrix4x4.hpp"
#include "IInitializable.hpp"
#include "IUpdateable.hpp"
#include "Reflection/UUID.hpp"
#include "ILoadable.hpp"

namespace Engine3DRadSpace
{
	class Game;
	class DLLEXPORT IObject : public IInitiializable, public IUpdateable, public ILoadable
	{
	protected:
		Game* _game = nullptr;
		GraphicsDevice* _device = nullptr;
		/// <summary>
		/// Default constructor used for reflection. Objects created with this constructor are invalid, unless the _device field is explicitly set after a IObject instance is constructed.
		/// </summary>
		/// <param name="name"></param>
		/// <param name="tag"></param>
		/// <param name="enabled"></param>
		/// <param name="visible"></param>
		explicit IObject(const std::string& name = "Empty", const std::string& tag = "...", bool enabled = false, bool visible = false);

		void internalInitialize(Game* game);
	public:
		std::string Name;
		std::string Tag;
		bool Enabled;
		bool Visible;

		virtual void EditorInitialize() = 0;
		virtual void EditorLoad(Content::ContentManager *content) = 0;

		virtual Reflection::UUID GetUUID() = 0;

		GraphicsDevice *GetGraphicsDeviceHandle();
		Game* GetGame();

		virtual ~IObject() = default;

		friend class Game;
	};
}


