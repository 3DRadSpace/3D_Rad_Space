cmake_minimum_required(VERSION 3.21)

project("3DRadSpace HelloWorld Plugin")

add_library(3DRadSpace_HelloWorld_plugin SHARED "Main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace_HelloWorld_plugin PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace_HelloWorld_plugin PRIVATE "/wd4251")
	#Use UNICODE.
	target_compile_definitions(3DRadSpace_HelloWorld_plugin PUBLIC UNICODE _UNICODE)
	#Fix C4530
	target_compile_options(3DRadSpace_HelloWorld_plugin PRIVATE "/EHsc")
	# Create separate pdb debug info compiler
	target_compile_options(3DRadSpace_HelloWorld_plugin PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace_HelloWorld_plugin PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Scripting PRIVATE "/fsanitize=address")
	endif()
endif()

#Link 3DRadSpace
target_link_libraries(3DRadSpace_HelloWorld_plugin PRIVATE 3DRadSpace.Logging)
target_include_directories(3DRadSpace_HelloWorld_plugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)
