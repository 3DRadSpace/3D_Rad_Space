cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Scripting.CSharp")

add_library(3DRadSpace.Scripting.CSharp SHARED 
	"CSharpScript.hpp"
	"CSharpScript.cpp"	
	"Main.cpp"
	"NETCOREHost.hpp"
	"NETCOREHost.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Scripting.CSharp PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Scripting.CSharp PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Scripting.CSharp PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Scripting.CSharp PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Scripting.CSharp PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Scripting.CSharp PRIVATE "/fsanitize=address")
	endif()
endif()

target_link_libraries(3DRadSpace.Scripting.CSharp PRIVATE 3DRadSpace.Core)
target_link_libraries(3DRadSpace.Scripting.CSharp PRIVATE 3DRadSpace.Reflection)
target_link_libraries(3DRadSpace.Scripting.CSharp PRIVATE 3DRadSpace.Math)
target_link_libraries(3DRadSpace.Scripting.CSharp PRIVATE 3DRadSpace.Logging)
target_link_libraries(3DRadSpace.Scripting.CSharp PRIVATE 3DRadSpace.Native)
target_link_libraries(3DRadSpace.Scripting.CSharp PRIVATE 3DRadSpace.Objects)
target_include_directories(3DRadSpace.Scripting.CSharp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

# nethost
find_package(unofficial-nethost CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Scripting.CSharp PRIVATE unofficial::nethost::nethost)