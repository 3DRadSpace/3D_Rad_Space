cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Native")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace.Native SHARED ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Native PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Native PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Native PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Native PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Native PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Native PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Native PRIVATE [[E3DRSP_NATIVE_EXPORT=__declspec(dllexport)]])
endif()

target_link_libraries(3DRadSpace.Native PRIVATE 3DRadSpace.Math)
target_link_libraries(3DRadSpace.Native PRIVATE 3DRadSpace.Input)
target_include_directories(3DRadSpace.Native PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)