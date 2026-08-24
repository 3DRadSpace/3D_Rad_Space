#pragma once
#include "../Graphics/IGraphicsDevice.hpp"
#include "../Native/Window.hpp"

namespace Engine3DRadSpace
{
	class Game;
	/// <summary>
	/// Factory class for Game instances. Sets services, GraphicsDevice, AudioEngine, PhysicsEngine, etc...
	/// </summary>
	/// <remarks>
	/// A Game instance can still be constructed without this, but it will fallback to provided defaults.
	/// </remarks>
	class E3DRSP_GAMES_EXPORT GameFactory
	{
	public:
		typedef std::unique_ptr<Graphics::IGraphicsDevice>(*FnCreateGraphicsDevice)(void* hwnd, size_t x, size_t y);
	private:
		static std::unordered_map<std::string, FnCreateGraphicsDevice> _deviceCtors;
		static FnCreateGraphicsDevice _fallback;

		std::unique_ptr<Game> _game;
	public:
		/// <summary>
		/// Constructs an GameFactory instance.
		/// </summary>
		GameFactory();

		GameFactory(const GameFactory&) = delete;
		GameFactory(GameFactory&&) = delete;

		GameFactory& operator=(const GameFactory&) = delete;
		GameFactory& operator=(GameFactory&&) = delete;

		/// <summary>
		/// Creates a Graphics device.
		/// </summary>
		/// <param name="name">Named backend. If empty, first element in _deviceCtors is called.</param>
		/// <returns></returns>
		static std::unique_ptr<Graphics::IGraphicsDevice> CreateGraphicsDevice(const std::string &name, void* hwnd, size_t x, size_t y);

		/// <summary>
		/// Registers a new graphics device type for this factory class.
		/// </summary>
		/// <param name="name">String name representation</param>
		/// <param name="fn">Function pointer to a function that creates a new concrete instance of IGraphicsDevice</param>
		static void RegisterDevice(const std::string& name, FnCreateGraphicsDevice fn);

		/// <summary>
		/// Begin Game instance creation.
		/// </summary>
		/// <param name="title">Title of the window.</param>
		/// <param name="width">Width of the window.</param>
		/// <param name="height">Height of the window.</param>
		void Begin(const std::string& title, size_t width, size_t height);
		/// <summary>
		/// Begin Game instance creation.
		/// </summary>
		/// <param name="window">Window instance to use for the game. The game instance will own the window.</param>
		void Begin(Native::Window&& window);

		/// <summary>
		///	Adds an service to the game instance.
		/// </summary>
		/// <param name="service"></param>
		void AddService(std::unique_ptr<IService>&& service);

		/// <summary>
		/// Sets the fallback graphics device constructor. This is used if no named backend is specified or if the named backend is not found.
		/// </summary>
		/// <param name="fn">Function pointer to the graphics device constructor.</param>
		static void SetFallbackGraphicsDeviceCtor(FnCreateGraphicsDevice fn);

		/// <summary>
		/// Creates the game application instance. Must be called after Begin().
		/// </summary>
		/// <returns>a new Game instance</returns>
		std::unique_ptr<Game> CreateGame();
	};
}