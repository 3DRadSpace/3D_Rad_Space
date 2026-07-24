cmake_minimum_required(VERSION 3.14)
project("3DRadSpace.Tests")

file(GLOB 3DRadSpace_tests_src CONFIGURE_DEPENDS "*.cpp")
#list(REMOVE_ITEM 3DRadSpace_tests_src "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp")
add_executable(3DRadSpace.Tests ${3DRadSpace_tests_src})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Tests PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Fix C4530
	target_compile_options(3DRadSpace.Tests PRIVATE "/EHsc")
	# Create separate pdb debug info files
	target_compile_options(3DRadSpace.Tests PRIVATE "/Zi")

	# Multiprocessor build
	target_compile_options(3DRadSpace.Tests PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Tests PRIVATE "/fsanitize=address")
	endif()
endif()

#Link 3DRadSpace
target_link_libraries(3DRadSpace.Tests PRIVATE 3DRadSpace.Math)
target_link_libraries(3DRadSpace.Tests PRIVATE 3DRadSpace.Reflection)
target_link_libraries(3DRadSpace.Tests PRIVATE 3DRadSpace.Graphics)
target_link_libraries(3DRadSpace.Tests PRIVATE 3DRadSpace.Objects)
target_link_libraries(3DRadSpace.Tests PRIVATE 3DRadSpace.Objects.Impl)
target_link_libraries(3DRadSpace.Tests PRIVATE 3DRadSpace.Objects.Gizmos)
target_link_libraries(3DRadSpace.Tests PRIVATE 3DRadSpace.Games)
target_include_directories(3DRadSpace.Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

enable_testing()
option(3DRadSpace.Tests "Build unit tests" ON)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

if(PROJECT_IS_TOP_LEVEL)
	add_dependencies(3DRadSpace.Tests e3drsp_copy_assets)

	add_custom_target(e3drsp_copy_testing ALL
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/Testing
				${CMAKE_BINARY_DIR}/Testing
	)

	add_dependencies(3DRadSpace.Tests e3drsp_copy_testing)
endif()

include(GoogleTest)
gtest_discover_tests(3DRadSpace.Tests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	DISCOVERY_MODE PRE_TEST
)