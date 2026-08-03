cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Audio")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace.Audio SHARED ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Audio PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Audio PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Audio PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Audio PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Audio PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Audio PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Audio PRIVATE [[E3DRSP_AUDIO_EXPORT=__declspec(dllexport)]])
endif()

#
#Dependencies 
#
target_link_libraries(3DRadSpace.Audio PRIVATE 3DRadSpace.Core)
target_link_libraries(3DRadSpace.Audio PRIVATE 3DRadSpace.Math)
target_link_libraries(3DRadSpace.Audio PRIVATE 3DRadSpace.Logging)
target_include_directories(3DRadSpace.Audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#OpenAL-Soft
find_package(OpenAL CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Audio PRIVATE OpenAL::OpenAL)

# Vorbis reference encoder and decoder, low-level API
find_package(Vorbis CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Audio PRIVATE Vorbis::vorbis)

# Audio stream decoding and basic manipulation, high-level API
find_package(Vorbis CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Audio PRIVATE Vorbis::vorbisfile)

# Convenience API for setting up an encoding environment
find_package(Vorbis CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Audio PRIVATE Vorbis::vorbisenc)