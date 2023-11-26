#pragma once
#include "../Libs.hpp"
#include "Key.hpp"
#include "KeyState.hpp"

namespace Engine3DRadSpace
{
	class Window;

	namespace Input
	{
		class DLLEXPORT Keyboard
		{
			uint8_t _keys[10];

			/// used inside the Window class
			void _addKey(uint8_t k);
			void _removeKey(uint8_t k);
			void _erase();
		public:
			Keyboard();

			bool IsKeyDown(Key k);
			bool IsKeyUp(Key k);
			bool IsAnyKeyDown();

			KeyState operator[](const Key k);

			friend class Window;
		};
	}
}