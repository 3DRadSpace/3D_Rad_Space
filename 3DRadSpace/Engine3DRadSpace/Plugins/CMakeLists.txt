cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Plugins")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace.Plugins STATIC ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Plugins PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Plugins PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Plugins PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Plugins PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Plugins PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Plugins PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Plugins PRIVATE [[E3DRSP_PLUGINS_EXPORT=__declspec(dllexport)]])
endif()

target_link_libraries(3DRadSpace.Plugins PRIVATE 3DRadSpace.Logging)
target_link_libraries(3DRadSpace.Plugins PRIVATE 3DRadSpace.Objects)
target_link_libraries(3DRadSpace.Plugins PRIVATE 3DRadSpace.Objects.Impl)
target_link_libraries(3DRadSpace.Plugins PRIVATE 3DRadSpace.Graphics)
target_link_libraries(3DRadSpace.Plugins PRIVATE 3DRadSpace.Native)
target_include_directories(3DRadSpace.Plugins PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)