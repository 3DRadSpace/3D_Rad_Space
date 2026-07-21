#include "pch.h"
#include <Engine3DRadSpace/Reflection/Event.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

void dummy()
{
	std::cout << "Dummy function called" << std::endl;
}

//TEST(EventTests, MemLeakTest)
//{
//	Event e;
//
//	e.Bind<void>(dummy);
//
//	for (int i = 0; i < 100000; ++i)
//	{
//		e.InvokeAll();
//	}
//
//	
//}
