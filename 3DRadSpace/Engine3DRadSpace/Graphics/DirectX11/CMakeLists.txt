cmake_minimum_required(VERSION 3.21)

project("3DRadSpace.Graphics.DirectX11")

add_library(3DRadSpace.Graphics.DirectX11 STATIC 
	"BlendState.hpp"
	"BlendState.cpp"
	"DepthStencilBuffer.hpp"
	"DepthStencilBuffer.cpp"
	"DepthStencilState.hpp"
	"DepthStencilState.cpp"
	"GraphicsDevice.hpp"
	"GraphicsDevice.cpp"
	"DomainShader.hpp"
	"DomainShader.cpp"
	"FragmentShader.hpp"
	"FragmentShader.cpp"
	"GeometryShader.hpp"
	"GeometryShader.cpp"
	"HullShader.hpp"
	"HullShader.cpp"
	"IndexBuffer.hpp"
	"IndexBuffer.cpp"
	"ShaderBase.hpp"
	"ShaderBase.cpp"
	"VertexShader.hpp"
	"VertexShader.cpp"
	"RenderTarget.hpp"
	"RenderTarget.cpp"
	"SamplerState.hpp"
	"SamplerState.cpp"
	"Texture1D.hpp"
	"Texture1D.cpp"
	"Texture2D.hpp"
	"Texture2D.cpp"
	"Texture3D.hpp"
	"Texture3D.cpp"
	"TextureCube.hpp"
	"TextureCube.cpp"
	"VertexBuffer.hpp"
	"VertexBuffer.cpp"
	"ShaderCompiler.hpp"
	"ShaderCompiler.cpp"
	"GraphicsCommandList.hpp"
	"GraphicsCommandList.cpp"
	"DeferredCommandList.hpp"
	"DeferredCommandList.cpp"
	"BufferUsage.hpp"
	"BufferUsage.cpp"
	"RasterizerState.hpp"
	"RasterizerState.cpp"
	"PixelFormat.hpp"
	"PixelFormat.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3DRadSpace.Graphics.DirectX11 PROPERTY CXX_STANDARD 23)
endif()

if(MSVC)
	#Disable warning 4251 : 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
	target_compile_options(3DRadSpace.Graphics.DirectX11 PRIVATE "/wd4251")
	#Fix C4530
	target_compile_options(3DRadSpace.Graphics.DirectX11 PRIVATE "/EHsc")
	# Create separate pdb debug info files
	add_compile_options(3DRadSpace.Graphics.DirectX11 PRIVATE "/Zi")
	# Multiprocessor build
	add_compile_options(3DRadSpace.Graphics.DirectX11 PRIVATE "/MP")

	#enable address sanitizer if using a debug configuration
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(3DRadSpace.Graphics.DirectX11 PRIVATE "/fsanitize=address")
	endif()

	target_compile_definitions(3DRadSpace.Graphics.DirectX11 PRIVATE [[E3DRSP_GRAPHICS_DX11_EXPORT=__declspec(dllexport)]])
endif()

if(WIN32)
	target_compile_definitions(3DRadSpace.Graphics.DirectX11 PRIVATE _WINDLL=1)
endif()

#
#Dependencies 
#
target_link_libraries(3DRadSpace.Graphics.DirectX11 PRIVATE 3DRadSpace.Core)
target_link_libraries(3DRadSpace.Graphics.DirectX11 PRIVATE 3DRadSpace.Math)
target_link_libraries(3DRadSpace.Graphics.DirectX11 PRIVATE 3DRadSpace.Graphics)
target_include_directories(3DRadSpace.Graphics.DirectX11 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../)

#DirectXTK
find_package(directxtk CONFIG REQUIRED)
target_link_libraries(3DRadSpace.Graphics.DirectX11 PRIVATE Microsoft::DirectXTK)