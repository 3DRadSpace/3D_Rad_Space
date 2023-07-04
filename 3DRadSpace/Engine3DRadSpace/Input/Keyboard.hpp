#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace
{
	class Window;

	namespace Input
	{
		//Read https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes (most used keys are implemented here)
		enum class Key : uint8_t
		{
			None = 0,
			LeftMouseButton = 0x01,
			RightMouseButton = 0x02,
			Cancel = 0x03,
			MiddleMouseButton = 0x04,
			X1MouseButton = 0x05,
			X2MouseButton = 0x06,

			Backspace = 0x08,
			Tab = 0x09,

			Clear = 0x0C,
			Enter = 0x0D,

			Shift = 0x10,
			Ctrl = 0x11,
			Alt = 0x12,
			Pause = 0x13,
			CapsLock = 0x14,

			ESC = 0x1B,

			Space = 0x20,
			PageUp = 0x21,
			PageDown = 0x22,
			End = 0x23,
			Home = 0x24,

			LeftArrow = 0x25,
			UpArrow = 0x26,
			RightArrow = 0x27,
			DownArrow = 0x28,

			PrintScreen = 0x2C,

			K0 = 0x30,
			K1,
			K2,
			K3,
			K4,
			K5,
			K6,
			K7,
			K8,
			K9,

			A = 0x41,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,

			Num0 = 0x60,
			Num1,
			Num2,
			Num3,
			Num4,
			Num5,
			Num6,
			Num7,
			Num8,
			Num9,

			NumPlus = 0x6B,
			NumSeparator = 0x6C,
			NumMinus = 0x6D,
			NumDecimal = 0x6E,
			NumDivide = 0x6F,

			F1 = 0x70,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			F16,
			F17,
			F18,
			F19,
			F20,
			F21,
			F22,
			F23,
			F24,

			LeftShift = 0xA0,
			RightShift,
			LeftCtrl,
			RightCtrl,
			LeftAlt,
			RightAlt,

			Plus = 0xBB,
			Comma = 0xBC,
			Minus = 0xBD,
			Period = 0xBE,
			
			QuestionMark = 0xBF,

			Tilde = 0xC0,
		};

		enum class KeyState : bool
		{
			Down = 0,
			Up = 1
		};

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

			friend class Engine3DRadSpace::Window;
		};
	}
}