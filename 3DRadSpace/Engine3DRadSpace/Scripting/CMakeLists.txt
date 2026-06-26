cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Scripting")

add_library(3DRadSpace.Scripting SHARED 
	"CompilationResults.hpp"
	"IScript.hpp"
	"IScriptBuilder.hpp"
	"ScriptEngine.hpp"
	"ScriptEngine.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Scripting PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Scripting PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Scripting PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Scripting PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Scripting PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Scripting PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Scripting PRIVATE [[E3DRSP_SCRIPTING_EXPORT=__declspec(dllexport)]])
endif()

target_link_libraries(3DRadSpace.Scripting PRIVATE 3DRadSpace.Games)
target_link_libraries(3DRadSpace.Scripting PRIVATE 3DRadSpace.Objects)
target_link_libraries(3DRadSpace.Scripting PRIVATE 3DRadSpace.Objects.Impl)
target_link_libraries(3DRadSpace.Scripting PRIVATE 3DRadSpace.Physics)
target_link_libraries(3DRadSpace.Scripting PRIVATE 3DRadSpace.Physics.NVPhysX)
target_link_libraries(3DRadSpace.Scripting PRIVATE 3DRadSpace.Physics.Objects)
target_link_libraries(3DRadSpace.Scripting PRIVATE 3DRadSpace.Projects)
target_link_libraries(3DRadSpace.Scripting PRIVATE 3DRadSpace.Objects.Gizmos)
target_include_directories(3DRadSpace.Scripting PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Scripting PRIVATE nlohmann_json::nlohmann_json)