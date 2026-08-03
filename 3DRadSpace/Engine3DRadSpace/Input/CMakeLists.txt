cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Input")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace.Input SHARED ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Input PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Input PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Input PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Input PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Input PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Input PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Input PRIVATE [[E3DRSP_INPUT_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace.Input PRIVATE _WINDLL=1)
endif()

#
#Dependencies 
#
target_link_libraries(3DRadSpace.Input PRIVATE 3DRadSpace.Core)
target_include_directories(3DRadSpace.Input PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)
