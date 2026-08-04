cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Objects.ObjectRegistry")

add_library(3DRadSpace.Objects.ObjectRegistry SHARED
	"ObjectRegistry.hpp"
	"ObjectRegistry.cpp"
)

if(MSVC)
	set_property(TARGET 3DRadSpace.Objects.ObjectRegistry PROPERTY CXX_STANDARD 23)
	set_property(TARGET 3DRadSpace.Objects.ObjectRegistry PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

	target_compile_options(3DRadSpace.Objects.ObjectRegistry PRIVATE "/wd4251")
	target_compile_options(3DRadSpace.Objects.ObjectRegistry PRIVATE "/EHsc")

	target_compile_definitions(3DRadSpace.Objects.ObjectRegistry PRIVATE BUILDING_OBJECT_REGISTRY)
endif()

target_link_libraries(3DRadSpace.Objects.ObjectRegistry PUBLIC 3DRadSpace.Reflection)
target_include_directories(3DRadSpace.Objects.ObjectRegistry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../)
