#pragma once
#include "Libs.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace Engine3DRadSpace
{
	class IUpdateable
	{
	public:
		virtual void Update(Input::Keyboard& keyboard,Input::Mouse& mouse, double dt) = 0;
		inline virtual ~IUpdateable()
		{

		}
	};
}

