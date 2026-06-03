cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Graphics.Rendering")

add_library(3DRadSpace.Graphics.Rendering STATIC 
	"ForwardRenderer.hpp"	
	"ForwardRenderer.cpp"
	"IRenderer.hpp"
	"IRenderer.cpp"
	"LinearPixelFogEffect.hpp"
	"LinearPixelFogEffect.cpp"
	"NullRenderer.hpp"
	"NullRenderer.cpp"
	"PostProcessCollection.hpp"
	"PostProcessCollection.cpp"
	"PostProcessEffect.hpp"
	"PostProcessEffect.cpp"
	"RenderingManager.hpp"
	"RenderingManager.cpp"
	"ShadowMapRenderer.hpp"
	"ShadowMapRenderer.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Graphics.Rendering PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Graphics.Rendering PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Graphics.Rendering PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Graphics.Rendering PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Graphics.Rendering PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Graphics.Rendering PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Graphics.Rendering PRIVATE [[E3DRSP_GRAPHICS_RENDERING_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace.Graphics.Rendering PRIVATE _WINDLL=1)
endif()

#
#Dependencies 
#
target_link_libraries(3DRadSpace.Graphics.Rendering PRIVATE 3DRadSpace.Core)
target_link_libraries(3DRadSpace.Graphics.Rendering PRIVATE 3DRadSpace.Reflection)
target_link_libraries(3DRadSpace.Graphics.Rendering PRIVATE 3DRadSpace.Math)
target_include_directories(3DRadSpace.Graphics.Rendering PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)