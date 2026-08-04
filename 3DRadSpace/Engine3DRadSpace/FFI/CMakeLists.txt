cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.FFI")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace.FFI SHARED ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.FFI PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.FFI PRIVATE "/wd4251")
	#Use UNICODE.
	target_compile_definitions(3DRadSpace.FFI PUBLIC UNICODE _UNICODE)
	#Fix C4530
	target_compile_options(3DRadSpace.FFI PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.FFI PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.FFI PRIVATE "/MP")
	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.FFI PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.FFI PRIVATE [[E3DRSP_FFI_EXPORT=__declspec(dllexport)]])
endif()

#Link 3DRadSpace
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Logging)
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Objects)
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Objects.Impl)
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Objects.Gizmos)
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Graphics)
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Graphics.DirectX11)
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Graphics.Primitives)
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Graphics.Rendering)
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Games)
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Input)
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Plugins)
target_link_libraries(3DRadSpace.FFI PRIVATE 3DRadSpace.Projects)
target_include_directories(3DRadSpace.FFI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)