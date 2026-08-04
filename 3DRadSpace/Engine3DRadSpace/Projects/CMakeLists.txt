cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Projects")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace.Projects SHARED ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Projects PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Projects PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Projects PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Projects PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Projects PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Projects PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Projects PRIVATE [[E3DRSP_PROJECTS_EXPORT=__declspec(dllexport)]])
endif()

target_link_libraries(3DRadSpace.Projects PRIVATE 3DRadSpace.Core)
target_link_libraries(3DRadSpace.Projects PRIVATE 3DRadSpace.Math)
target_link_libraries(3DRadSpace.Projects PRIVATE 3DRadSpace.Reflection)
target_link_libraries(3DRadSpace.Projects PRIVATE 3DRadSpace.Objects)
target_link_libraries(3DRadSpace.Projects PUBLIC 3DRadSpace.Graphics)
target_link_libraries(3DRadSpace.Projects PRIVATE 3DRadSpace.Objects.Impl)
target_link_libraries(3DRadSpace.Projects PRIVATE 3DRadSpace.Objects.Gizmos)
target_include_directories(3DRadSpace.Projects PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Projects PUBLIC nlohmann_json::nlohmann_json)