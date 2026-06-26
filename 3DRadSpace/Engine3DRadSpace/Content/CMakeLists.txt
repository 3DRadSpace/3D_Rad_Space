cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Content")

add_library(3DRadSpace.Content SHARED 
	"AssetID.hpp"
	"ContentManager.hpp"
	"ContentManager.cpp"
	"IAsset.hpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Content PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Content PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Content PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Content PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Content PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Content PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Content PRIVATE [[E3DRSP_CONTENT_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace.Content PRIVATE _WINDLL=1)
endif()

#
#Dependencies 
#

target_link_libraries(3DRadSpace.Content PRIVATE 3DRadSpace.Core)
target_link_libraries(3DRadSpace.Content PRIVATE 3DRadSpace.Logging)
target_link_libraries(3DRadSpace.Content PRIVATE 3DRadSpace.Math)
target_link_libraries(3DRadSpace.Content PRIVATE 3DRadSpace.Reflection)
target_link_libraries(3DRadSpace.Content PRIVATE 3DRadSpace.Graphics)
target_include_directories(3DRadSpace.Content PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)