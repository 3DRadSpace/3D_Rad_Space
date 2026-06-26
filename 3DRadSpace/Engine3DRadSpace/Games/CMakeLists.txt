cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Games")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace.Games SHARED ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Games PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Games PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Games PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Games PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Games PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Games PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Games PRIVATE [[E3DRSP_GAMES_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace.Games PRIVATE _WINDLL=1)
endif()

#
#Dependencies 
#
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Audio)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Graphics)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Graphics.DirectX11)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Graphics.Null)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Graphics.Rendering)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Content)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Objects)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Objects.Impl)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Objects.Gizmos)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Content.Assets)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Input)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Native)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Physics)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Physics.NVPhysX)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Physics.Objects)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Projects)
target_link_libraries(3DRadSpace.Games PRIVATE 3DRadSpace.Reflection)
target_include_directories(3DRadSpace.Games PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Games PRIVATE nlohmann_json::nlohmann_json)