cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Objects.Impl")

add_library(3DRadSpace.Objects.Impl STATIC 
	"Box.hpp"
	"Box.cpp"
	"Button.hpp"
	"Button.cpp"
	"Camera.hpp"
	"Camera.cpp"
	"Cone.hpp"
	"Cone.cpp"
	"Counter.hpp"
	"Counter.cpp"
	"Cylinder.hpp"
	"Cylinder.cpp"
	"DirectionalLight.hpp"
	"DirectionalLight.cpp"
	"Empty.hpp"
	"Empty.cpp"
	"EventOnKey.hpp"
	"EventOnKey.cpp"
	"EventOnLocation.hpp"
	"EventOnLocation.cpp"
	"ExitFade.hpp"
	"ExitFade.cpp"
	"Fog.hpp"
	"Fog.cpp"
	"FreeCam.hpp"
	"FreeCam.cpp"
	"Objects.hpp"
	"Objects.cpp"
	"SettingsManager.hpp"
	"SettingsManager.cpp"
	"Skinmesh.hpp"
	"Skinmesh.cpp"
	"Skybox.hpp"
	"Skybox.cpp"
	"SkyColor.hpp"
	"SkyColor.cpp"
	"SoundEffect.hpp"
	"SoundEffect.cpp"
	"SoundSource.hpp"
	"SoundSource.cpp"
	"Sprite.hpp"
	"Sprite.cpp"
	"Sphere.hpp"
	"Sphere.cpp"
	"TextPrint.hpp"
	"TextPrint.cpp"
	"Timer.hpp"
	"Timer.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Objects.Impl PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Objects.Impl PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Objects.Impl PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Objects.Impl PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Objects.Impl PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		#target_compile_options(3DRadSpace.Objects.Impl PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Objects.Impl PRIVATE [[E3DRSP_OBJECTS_IMPL_EXPORT=__declspec(dllexport)]])
endif()

target_link_libraries(3DRadSpace.Objects.Impl PRIVATE 3DRadSpace.Audio)
target_link_libraries(3DRadSpace.Objects.Impl PUBLIC 3DRadSpace.Graphics)
target_link_libraries(3DRadSpace.Objects.Impl PRIVATE 3DRadSpace.Graphics.Rendering)
target_link_libraries(3DRadSpace.Objects.Impl PRIVATE 3DRadSpace.Content)
target_link_libraries(3DRadSpace.Objects.Impl PRIVATE 3DRadSpace.Content.Assets)
target_link_libraries(3DRadSpace.Objects.Impl PRIVATE 3DRadSpace.Input)
target_link_libraries(3DRadSpace.Objects.Impl PRIVATE 3DRadSpace.Physics)
target_link_libraries(3DRadSpace.Objects.Impl PRIVATE 3DRadSpace.Physics.NVPhysX)
target_link_libraries(3DRadSpace.Objects.Impl PRIVATE 3DRadSpace.Physics.Objects)
target_link_libraries(3DRadSpace.Objects.Impl PRIVATE 3DRadSpace.Reflection)
target_link_libraries(3DRadSpace.Objects.Impl PRIVATE 3DRadSpace.Native)
target_link_libraries(3DRadSpace.Objects.Impl PRIVATE 3DRadSpace.Objects.Gizmos)
target_include_directories(3DRadSpace.Objects.Impl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)