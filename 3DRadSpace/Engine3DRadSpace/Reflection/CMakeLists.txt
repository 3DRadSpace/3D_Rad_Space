cmake_minimum_required(VERSION 3.21)

project("Engine3DRadSpace.Reflection")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp" "*.hpp" )

add_library(3DRadSpace.Reflection SHARED
	"Any.hpp"
	"Any.cpp"
	"CallbackEvent.hpp"
	"CallbackEvent.cpp"
	"EnumEntry.hpp"
	"Event.hpp"
	"Event.cpp"
	"FieldRepresentation.hpp"
	"FieldRepresentation.cpp"
	"IEvent.hpp"
	"IReflectedField.hpp"
	"IReflectedField.cpp"
	"IReflectedFunction.hpp"
	"IReflectedFunction.cpp"
	"ReflectedAsset.hpp"
	"ReflectedEnum.hpp"
	"ReflectedEnum.cpp"
	"ReflectedEnumField.hpp"
	"ReflectedField.hpp"
	"ReflectedFunction.hpp"
	"MultiEvent.hpp"
	"MultiEvent.cpp"
	"ReflectedMemberFunction.hpp"
	"ReflectedObject.hpp"
	"ReflectedObject.cpp"
	"Reflection.hpp"
	"UUID.hpp"
	"UUID.cpp"
	"UnknownVariable.hpp"
	"UnknownVariable.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Reflection PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Reflection PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Reflection PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Reflection PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Reflection PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		#target_compile_options(3DRadSpace.Reflection PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Reflection PRIVATE [[E3DRSP_REFLECTION_EXPORT=__declspec(dllexport)]])
endif()

target_link_libraries(3DRadSpace.Reflection PRIVATE 3DRadSpace.Math)
target_include_directories(3DRadSpace.Reflection PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#Nlohmann JSON
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Reflection PRIVATE nlohmann_json::nlohmann_json)