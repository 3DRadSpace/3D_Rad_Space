cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Objects.Gizmos")

add_library(3DRadSpace.Objects.Gizmos STATIC 
	"CameraGizmo.hpp"
	"CameraGizmo.cpp"
	"EOLGizmo.hpp"
	"EOLGizmo.cpp"
	"Gizmo.hpp"
	"SkinmeshGizmo.hpp"
	"SkinmeshGizmo.cpp"
	"SoundSourceGizmo.hpp"
	"SoundSourceGizmo.cpp"
	"SphereGizmo.hpp"
	"SphereGizmo.cpp"
	"SpriteGizmo.hpp"
	"SpriteGizmo.cpp"
	"TextPrintGizmo.hpp"
	"TextPrintGizmo.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Objects.Gizmos PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Objects.Gizmos PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Objects.Gizmos PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Objects.Gizmos PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Objects.Gizmos PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		#target_compile_options(3DRadSpace.Objects.Gizmos PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Objects.Gizmos PRIVATE [[E3DRSP_OBJECTS_GIZMOS_EXPORT=__declspec(dllexport)]])
endif()

target_link_libraries(3DRadSpace.Objects.Gizmos PRIVATE 3DRadSpace.Audio)
target_link_libraries(3DRadSpace.Objects.Gizmos PRIVATE 3DRadSpace.Graphics)
target_link_libraries(3DRadSpace.Objects.Gizmos PRIVATE 3DRadSpace.Content)
target_link_libraries(3DRadSpace.Objects.Gizmos PRIVATE 3DRadSpace.Content.Assets)
target_link_libraries(3DRadSpace.Objects.Gizmos PRIVATE 3DRadSpace.Physics)
target_link_libraries(3DRadSpace.Objects.Gizmos PRIVATE 3DRadSpace.Reflection)
target_link_libraries(3DRadSpace.Objects.Gizmos PRIVATE 3DRadSpace.Objects)
target_include_directories(3DRadSpace.Objects.Gizmos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)