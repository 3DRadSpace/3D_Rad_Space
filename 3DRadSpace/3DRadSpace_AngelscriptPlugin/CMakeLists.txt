cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.AngelScript")

file(GLOB_RECURSE 3DRadSpace.AngelScript-src CONFIGURE_DEPENDS "*.cpp" "*.hpp" )
add_library(3DRadSpace.AngelScript SHARED ${3DRadSpace.AngelScript-src})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.AngelScript PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.AngelScript PRIVATE "/wd4251")
	#Use UNICODE.
	target_compile_definitions(3DRadSpace.AngelScript PUBLIC UNICODE _UNICODE)
	#Fix C4530
	target_compile_options(3DRadSpace.AngelScript PRIVATE "/EHsc")
	# Create separate pdb debug info
	target_compile_options(3DRadSpace.AngelScript PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.AngelScript PRIVATE "/MP")

	target_compile_definitions(3DRadSpace.AngelScript PRIVATE [[E3DRSP_ANGELSCRIPT_EXPORT=__declspec(dllexport)]])

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.AngelScript PRIVATE "/fsanitize=address")
	endif()
endif()

#Link 3DRadSpace
target_link_libraries(3DRadSpace.AngelScript PRIVATE 3DRadSpace.Logging)
target_link_libraries(3DRadSpace.AngelScript PRIVATE 3DRadSpace.Math)
target_link_libraries(3DRadSpace.AngelScript PRIVATE 3DRadSpace.Reflection)
target_link_libraries(3DRadSpace.AngelScript PRIVATE 3DRadSpace.Games)
target_link_libraries(3DRadSpace.AngelScript PRIVATE 3DRadSpace.Objects)
target_link_libraries(3DRadSpace.AngelScript PRIVATE 3DRadSpace.Scripting)
target_link_libraries(3DRadSpace.AngelScript PRIVATE 3DRadSpace.Projects)
target_include_directories(3DRadSpace.AngelScript PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Add Angelscript
find_package(Angelscript CONFIG REQUIRED)
target_link_libraries(3DRadSpace.AngelScript PRIVATE Angelscript::angelscript)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace.AngelScript PRIVATE nlohmann_json::nlohmann_json)