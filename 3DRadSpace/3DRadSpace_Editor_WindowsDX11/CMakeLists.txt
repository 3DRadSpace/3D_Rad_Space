cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Editor")

file(GLOB_RECURSE 3DRadSpace.Editor-src CONFIGURE_DEPENDS "*.cpp" "*.hpp" )
add_executable(3DRadSpace.Editor WIN32 ${3DRadSpace.Editor-src})

target_sources(3DRadSpace.Editor PRIVATE 3DRadSpace_Editor_WindowsDX11.rc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Editor PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Editor PRIVATE "/wd4251")
	#Use UNICODE.
	target_compile_definitions(3DRadSpace.Editor PUBLIC UNICODE _UNICODE)
	#Fix C4530
	target_compile_options(3DRadSpace.Editor PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Editor PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Editor PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Editor PRIVATE "/fsanitize=address")
	endif()
endif()

#Link 3DRadSpace
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Logging)
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Objects)
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Objects.Impl)
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Objects.Gizmos)
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Graphics)
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Graphics.DirectX11)
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Graphics.Primitives)
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Graphics.Rendering)
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Games)
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Input)
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Plugins)
target_link_libraries(3DRadSpace.Editor PRIVATE 3DRadSpace.Projects)
target_include_directories(3DRadSpace.Editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Editor PRIVATE nlohmann_json::nlohmann_json)

#Copy assets
add_custom_target(e3drsp_copy_assets ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/Data
			${CMAKE_BINARY_DIR}/Data
)

add_dependencies(3DRadSpace.Editor e3drsp_copy_assets)

#TODO: Copy binaries for the project generator.