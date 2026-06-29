cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Physics")

add_library(3DRadSpace.Physics SHARED
	"ICharacterController.hpp"
	"ICharacterController.cpp"
	"ICollider.hpp"
	"ICollider.cpp"
	"IDynamicCollider.hpp"
	"IDynamicCollider.cpp"
	"IJoint.hpp"
	"IJoint.cpp"
	"IPhysicsEngine.hpp"
	"IStaticCollider.hpp"
	"IStaticCollider.cpp"
	"JointType.hpp"
	"JointType.refl.cpp"
	"PhysicsSettings.hpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Physics PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Physics PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Physics PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Physics PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Physics PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		#target_compile_options(3DRadSpace.Physics PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Physics PRIVATE [[E3DRSP_PHYSICS_EXPORT=__declspec(dllexport)]])
endif()

find_package(unofficial-omniverse-physx-sdk CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Physics PRIVATE unofficial::omniverse-physx-sdk::sdk)

target_link_libraries(3DRadSpace.Physics PRIVATE 3DRadSpace.Core)
target_link_libraries(3DRadSpace.Physics PRIVATE 3DRadSpace.Math)
target_link_libraries(3DRadSpace.Physics PRIVATE 3DRadSpace.Logging)
target_include_directories(3DRadSpace.Physics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)