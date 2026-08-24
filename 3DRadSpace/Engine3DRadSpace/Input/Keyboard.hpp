#pragma once
#include "../Core/Libs.hpp"
#include "Key.hpp"
#include "KeyState.hpp"

namespace Engine3DRadSpace
{
	namespace Native
	{
		class Window;
	}

	namespace Input
	{
		/// <summary>
		/// Represents the keyboard input state.
		/// </summary>
		class E3DRSP_INPUT_EXPORT Keyboard
		{
			uint8_t _keys[10];

			/// used inside the Window class
			void _addKey(uint8_t k);
			void _removeKey(uint8_t k);
			void _erase();
		public:
			/// <summary>
			///	Constructs an empty keyboard input state.
			/// </summary>
			Keyboard();

			/// <summary>
			/// Is the specified key currently down?
			/// </summary>
			/// <param name="k">Key to check</param>
			/// <returns>True if the key is down, false otherwise</returns>
			bool IsKeyDown(Key k) const noexcept;
			/// <summary>
			/// Is the specified key currently up?
			/// </summary>
			/// <param name="k">Key to check</param>
			/// <returns>True if the key is up, false otherwise</returns>
			bool IsKeyUp(Key k) const noexcept;
			/// <summary>
			/// Is any key currently down?
			/// </summary>
			/// <returns>True if any key is down, false otherwise</returns>
			bool IsAnyKeyDown() const noexcept;

			/// <summary>
			/// Returns the key state of the specified key.
			/// </summary>
			/// <param name="k">specified key</param>
			/// <returns>Key state of the specified key</returns>
			KeyState operator[](const Key k);

			friend class Native::Window;
		};
	}
}