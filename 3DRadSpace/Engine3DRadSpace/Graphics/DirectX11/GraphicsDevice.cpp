#include "GraphicsDevice.hpp"
#include "../Logging/Logging.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "RenderTarget.hpp"
#include "DepthStencilBuffer.hpp"
#include "..\Core\AssetUUIDReader.hpp"
#include "GraphicsCommandList.hpp"
#include "BlendState.hpp"
#include "ShaderCompiler.hpp"
#include "SamplerState.hpp"
#include "DeferredCommandList.hpp"
#include "Texture1D.hpp"
#include "Texture3D.hpp"
#include "TextureCube.hpp"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

//#include <directxtk\ScreenGrab.h>
#include <wincodec.h>
#include <dxgidebug.h>
#include <dxgi.h>
#include <dxgi1_3.h>
#include <dxgi1_6.h>

#undef min
#undef max

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;

GraphicsDevice::GraphicsDevice(void* nativeWindowHandle, size_t width, size_t height, GraphicsDeviceCreationOptions opt) :
	_resolution(width, height)
{
	Logging::SetLastMessage("Creating DirectX11::GraphicsDevice");

	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.RefreshRate = { 1,60 }; // 1/60
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
	
	//If not fullscreen:
	if((opt & GraphicsDeviceCreationOptions::Fullscreen) != GraphicsDeviceCreationOptions::Fullscreen)
	{
		swapChainDesc.Windowed = true;
		opt &= ~GraphicsDeviceCreationOptions::Fullscreen;
	}
	else swapChainDesc.Windowed = false;

	bool disallowAltEnter = (opt & GraphicsDeviceCreationOptions::NoAltEnter) == GraphicsDeviceCreationOptions::NoAltEnter;

	swapChainDesc.SampleDesc = { 1, 0 }; //count, quality
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT ;
	swapChainDesc.OutputWindow = static_cast<HWND>(nativeWindowHandle);

	UINT flags = 0;

	//Set debug flag
#ifdef _DEBUG
	opt |= GraphicsDeviceCreationOptions::Debug;
#endif // _DEBUG

	if((opt & GraphicsDeviceCreationOptions::Debug) == GraphicsDeviceCreationOptions::Debug)
	{
		flags |= D3D11_CREATE_DEVICE_DEBUG;
		opt &= ~GraphicsDeviceCreationOptions::Debug;
	}

	//Set singlethreaded flag
	if((opt & GraphicsDeviceCreationOptions::Singlethreaded) == GraphicsDeviceCreationOptions::Singlethreaded)
	{
		flags |= D3D11_CREATE_DEVICE_SINGLETHREADED;
		opt &= ~GraphicsDeviceCreationOptions::Singlethreaded;
	}

	//Enumerate GPUs
	Microsoft::WRL::ComPtr<IDXGIFactory> factory;
	HRESULT r = CreateDXGIFactory(__uuidof(IDXGIFactory), &factory);
	if(FAILED(r)) throw Exception("Failed to create DXGI Factory!");

	Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;

	bool selectPerformance = (opt & GraphicsDeviceCreationOptions::SelectGPU_Performance) == GraphicsDeviceCreationOptions::SelectGPU_Performance;
	bool selectIntegrated = (opt & GraphicsDeviceCreationOptions::SelectGPU_Integrated) == GraphicsDeviceCreationOptions::SelectGPU_Integrated;

	Microsoft::WRL::ComPtr<IDXGIAdapter> bestAdapter;
	size_t bestVideoMemory = selectPerformance ? std::numeric_limits<size_t>::min() : (selectIntegrated ? std::numeric_limits<size_t>::max() : 0);

	std::string bestAdapterName;

	//Find adapter by specified criteria
	DXGI_ADAPTER_DESC adapterDesc{};
	for(UINT idxAdapter = 0; ; idxAdapter++)
	{
		r = factory->EnumAdapters(idxAdapter, &adapter);
		if(FAILED(r)) break;

		adapter->GetDesc(&adapterDesc);
		auto memory = adapterDesc.DedicatedVideoMemory /= (1024 * 1024); // bytes -> MB

#pragma warning(push)
#pragma warning(disable: 4244)
		auto adapterName = std::string(
			adapterDesc.Description,
			adapterDesc.Description + lstrlenW(adapterDesc.Description)
		);
#pragma warning(pop)

		auto updateAdapter = [&]()
		{
			bestAdapterName = adapterName;
			bestVideoMemory = memory;
			bestAdapter = adapter;
		};

		Logging::SetLastMessage(std::format("GPU Adapter {} Memory {} MB", adapterName, memory));
		
		if(memory == 0)
		{
			if((opt & GraphicsDeviceCreationOptions::SelectGPU_Software) == GraphicsDeviceCreationOptions::SelectGPU_Software)
			{
				updateAdapter();
				break;
			}
			else continue;
		}

		//If default, just select the first enumerated device.
		if(opt == GraphicsDeviceCreationOptions::Unspecified ||
		  (opt & GraphicsDeviceCreationOptions::SelectGPU_Default) == GraphicsDeviceCreationOptions::SelectGPU_Default)
		{
			updateAdapter();
			break;
		};

		//If performance, select the adapter with the most video memory.
		if(selectPerformance && memory > bestVideoMemory)
		{
			updateAdapter();
		}

		//If dedicated, select the first adapter that is not integrated or software.
		if(selectIntegrated && memory < bestVideoMemory)
		{
			updateAdapter();
		}
	}

	Logging::SetLastMessage(std::format("Selected GPU adapter {} Mem {}", bestAdapterName, bestVideoMemory));

	//Check for HDR support
	bool hdrSupported = false;
	if(bestAdapter != nullptr)
	{
		Microsoft::WRL::ComPtr<IDXGIFactory1> factory1;
		r = factory->QueryInterface(__uuidof(IDXGIFactory1), &factory1);
		if(SUCCEEDED(r))
		{
			Microsoft::WRL::ComPtr<IDXGIOutput> output;
			r = bestAdapter->EnumOutputs(0, &output);
			if(SUCCEEDED(r))
			{
				Microsoft::WRL::ComPtr<IDXGIOutput6> output6;
				r = output->QueryInterface(__uuidof(IDXGIOutput6), &output6);
				if(SUCCEEDED(r))
				{
					DXGI_OUTPUT_DESC1 outputDesc{};
					r = output6->GetDesc1(&outputDesc);
					if(SUCCEEDED(r))
					{
						hdrSupported = (outputDesc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020);
						Logging::SetLastMessage(std::format("HDR Support: {} (ColorSpace: {})", 
							hdrSupported ? "Yes" : "No", 
							static_cast<int>(outputDesc.ColorSpace)));
					}
				}
			}
		}
	}

	//Set swap chain format based on HDR support
	_hasHDR = hdrSupported;
	if(_hasHDR)
	{
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		Logging::SetLastMessage("Using HDR format: DXGI_FORMAT_R16G16B16A16_FLOAT (scRGB) with flip model");
	}
	else
	{
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;
		Logging::SetLastMessage("Using SDR format: DXGI_FORMAT_B8G8R8A8_UNORM with legacy swap effect");
	}

	//DirectX11 Device creation.
	r = D3D11CreateDeviceAndSwapChain(
		bestAdapter.Get(),
		bestAdapter == nullptr ? D3D_DRIVER_TYPE_HARDWARE : D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		flags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&_swapChain,
		&_device,
		nullptr,
		&_context
	);
	if(FAILED(r))
	{
		Logging::SetLastWarning("Failed to create device with specified criteria. Creating default device");
		r = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flags,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&_swapChain,
			&_device,
			nullptr,
			&_context
		);

		if(FAILED(r)) throw Exception("D3D11CreateDeviceAndSwapChain failure!");
	}

	_createBackBuffer();

	if(disallowAltEnter)
	{
		Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
		_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(dxgiDevice.GetAddressOf()));

		Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
		dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(dxgiAdapter.GetAddressOf()));

		Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;
		dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(dxgiFactory.GetAddressOf()));

		dxgiFactory->MakeWindowAssociation(static_cast<HWND>(nativeWindowHandle), DXGI_MWA_NO_WINDOW_CHANGES);
	}

	_stencilBuffer = std::make_unique<DepthStencilBuffer>(this);
	_stencilState = std::make_unique<DepthStencilState>(this);
	_blendState = std::make_unique<BlendState>(this);

	_context->OMSetDepthStencilState(_stencilState->_state.Get(), 1);

	//create screen quad - used for post effects
	auto rr = RectangleF(0, 0, 1, 1);
	Vector2 a = rr.BottomLeft();
	a = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(a);

	Vector2 b = rr.TopLeft();
	b = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(b);

	Vector2 c = rr.TopRight();
	c = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(c);

	Vector2 d = rr.BottomRight();
	d = Vector2::ConvertFromNormalizedScreenSpaceToClipSpace(d);

	Vector2 uv_a = Vector2(0, 1);
	Vector2 uv_b = Vector2(0, 0);
	Vector2 uv_c = Vector2(1, 0);
	Vector2 uv_d = Vector2(1, 1);

	std::array<VertexPointUV, 6> quad =
	{
		VertexPointUV{a, uv_a},
		VertexPointUV{b, uv_b},
		VertexPointUV{c, uv_c},

		VertexPointUV{c, uv_c},
		VertexPointUV(d, uv_d),
		VertexPointUV{a, uv_a}
	};

	_screenQuad = std::make_unique<VertexBuffer>(
		this,
		quad.data(),
		sizeof(VertexPointUV),
		static_cast<size_t>(quad.size()),
		BufferUsage::ReadOnlyGPU
	);
	_screenQuad->SetDebugName("GraphicsDevice::_screenQuad");

#if _DEBUG
	const char deviceName[] = "GraphicsDevice::_device";
	_device->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(deviceName) - 1, deviceName);

	const char contextName[] = "GraphicsDevice::_context";
	_context->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(contextName) - 1, contextName);

	const char textureBackbufferName[] = "GraphicsDevice::_backbufferRT::_texture";
	_backbufferRT->_texture->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureBackbufferName) - 1, textureBackbufferName);

	const char textureBackBufferViewName[] = "GraphicsDevice::_backBufferRT::_resourceView";
	_backbufferRT->_resourceView->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(textureBackBufferViewName) - 1, textureBackBufferViewName);

	const char renderTargetBackBufferName[] = "GraphicsDevice::_backBufferRT::_renderTarget";
	_backbufferRT->_renderTarget->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(renderTargetBackBufferName) - 1, renderTargetBackBufferName);
#endif

	_immediateContext = std::make_unique<GraphicsCommandList>(this);
	_compiler = std::make_unique<DirectX11::ShaderCompiler>(this);

	Color white[] =
	{
		Colors::White, Colors::White,
		Colors::White, Colors::White
	};

	_white2x2 = std::make_unique<Texture2D>(
		this,
		white,
		2,
		2
	);

	Logging::SetLastMessage("Created D3D11 backend");
	Logging::SetLastMessage(std::format("Backbuffer {} {} fullscreen {} Nat Window Handle 0x{:x}", width, height, _fullscreen, reinterpret_cast<intptr_t>(nativeWindowHandle)));
}

void GraphicsDevice::_createBackBuffer()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> rtTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;

	//assign texture to main render target.

	HRESULT r = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), static_cast<void**>(&rtTexture));
	if(FAILED(r)) throw Exception("Failed to get the back buffer texture!");

	//Create shader resource view for back buffer
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = _hasHDR ? DXGI_FORMAT_R16G16B16A16_FLOAT : DXGI_FORMAT_B8G8R8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = -1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	r = _device->CreateShaderResourceView(rtTexture.Get(), &srvDesc, &srv);
	if(FAILED(r)) throw Exception("Failed to create shader resource view for the back buffer!");

	//assign render target view
	r = _device->CreateRenderTargetView(rtTexture.Get(), nullptr, &rtv);
	if(FAILED(r)) throw Exception("Failed to create the main render target!");

	_backbufferRT.reset(
		new RenderTarget(this,
			std::move(rtTexture),
			std::move(srv),
			std::move(rtv)
		)
	);
	_backbufferRT->_retrieveSize();
}

std::string_view GraphicsDevice::BackendName() const noexcept
{
	return std::string_view("DirectX11");
}

Math::Point GraphicsDevice::Resolution() const noexcept
{
	return this->_resolution;
}

IRenderTarget* GraphicsDevice::GetBackBuffer() const noexcept
{
	return _backbufferRT.get();
}

Graphics::ITexture2D* GraphicsDevice::GetBackBufferTexture() const noexcept
{
	return dynamic_cast<Texture2D*>(this->_backbufferRT.get());
}

IDepthStencilBuffer& GraphicsDevice::GetDepthBuffer()
{
	return *this->_stencilBuffer;
}

GraphicsDevice::~GraphicsDevice()
{
	if (_context)
	{
		_context->ClearState();
		_context->Flush();
	}

	_swapChain->SetFullscreenState(false, nullptr);
//
//		UNCOMMENT THE COMMENT BLOCK BELOW IF THERE ARE DIRECTX OBJECTS LEAKING! 
//

/*
#if _DEBUG
	Microsoft::WRL::ComPtr<ID3D11Debug> debug;
	_device->QueryInterface<ID3D11Debug>(&debug);
	debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
#endif
*/
}

std::unique_ptr<IGraphicsCommandList> GraphicsDevice::CreateCommandList()
{
	return std::make_unique<DeferredCommandList>(this);
}

IGraphicsCommandList* GraphicsDevice::ImmediateContext()
{
	return _immediateContext.get();
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState(
	bool alphaCoverage,
	bool indepedentBlend,
	std::array<RenderTargetBlendState, 8> renderTargetBlendStates
)
{
	return std::make_unique<BlendState>(this, alphaCoverage, indepedentBlend, renderTargetBlendStates);
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_Opaque()
{
	return std::make_unique<BlendState>(std::move(BlendState::Opaque(this)));
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_AlphaBlend()
{
	return std::make_unique<BlendState>(std::move(BlendState::AlphaBlend(this)));
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_Additive()
{
	return std::make_unique<BlendState>(std::move(BlendState::Additive(this)));
}

std::unique_ptr<IBlendState> GraphicsDevice::CreateBlendState_NonPremultiplied()
{
	return std::make_unique<BlendState>(std::move(BlendState::NonPremultiplied(this)));
}

std::unique_ptr<IDepthStencilBuffer> GraphicsDevice::CreateDepthStencilBuffer(
	size_t x,
	size_t y
)
{
	return std::make_unique<DepthStencilBuffer>(this, x, y);
}

std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState(
	bool EnableDepth,
	DepthWriteMask Mask,
	ComparisonFunction Function,
	bool EnableStencil,
	uint8_t ReadMask,
	uint8_t WriteMask,
	FaceOperation FrontFace,
	FaceOperation BackFace
)
{
	return std::make_unique<DepthStencilState>(
		this,
		EnableDepth,
		Mask,
		Function,
		EnableStencil,
		ReadMask,
		WriteMask,
		FrontFace,
		BackFace
	);
}

std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthDefault()
{
	return std::make_unique<DepthStencilState>(std::move(DepthStencilState::DepthDefault(this)));
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthNone()
{
	return std::make_unique<DepthStencilState>(std::move(DepthStencilState::DepthNone(this)));
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthRead()
{
	return std::make_unique<DepthStencilState>(std::move(DepthStencilState::DepthRead(this)));
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthReverseZ()
{
	return std::make_unique<DepthStencilState>(std::move(DepthStencilState::DepthReverseZ(this)));
}
std::unique_ptr<IDepthStencilState> GraphicsDevice::CreateDepthStencilState_DepthReadReverseZ()
{
	return std::make_unique<DepthStencilState>(std::move(DepthStencilState::DepthReadReverseZ(this)));
}

IShaderCompiler* GraphicsDevice::ShaderCompiler()
{
	return _compiler.get();
}

ITexture2D* GraphicsDevice::WhiteBlank()
{
	return _white2x2.get();
}

std::unique_ptr<IIndexBuffer> GraphicsDevice::CreateIndexBuffer(std::span<unsigned> indices)
{
	return std::make_unique<IndexBuffer>(this, indices);
}

std::unique_ptr<IIndexBuffer> GraphicsDevice::CreateIndexBuffer(size_t numIndices, BufferUsage usage)
{
	return std::make_unique<IndexBuffer>(this, numIndices, usage);
}

std::unique_ptr<IDepthStencilState> GraphicsDevice::GetDepthStencilState()
{
	return std::make_unique<DepthStencilState>(std::move(DepthStencilState::GetCurrent(this)));
}

std::unique_ptr<IRasterizerState> GraphicsDevice::GetRasterizerState()
{
	return std::make_unique<RasterizerState>(this);
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState(
	RasterizerFillMode filling,
	RasterizerCullMode culling,
	bool switchFrontBack,
	int depthBias,
	float depthBiasClamp,
	float slopeScaleDepthBias,
	bool depthClip,
	bool scissor,
	bool multisample,
	bool aaLine
)
{
	return std::make_unique<RasterizerState>(
		this,
		filling,
		culling,
		switchFrontBack,
		depthBias,
		depthBiasClamp,
		slopeScaleDepthBias,
		depthClip,
		scissor,
		multisample,
		aaLine
	);
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState_CullNone()
{
	return std::make_unique<RasterizerState>(std::move(RasterizerState::CullNone(this)));
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState_CullClockwise()
{
	return std::make_unique<RasterizerState>(std::move(RasterizerState::CullClockwise(this)));
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState_CullCounterClockwise()
{
	return std::make_unique<RasterizerState>(std::move(RasterizerState::CullCounterClockwise(this)));
}

std::unique_ptr<IRasterizerState> GraphicsDevice::CreateRasterizerState_Wireframe()
{
	return std::make_unique<RasterizerState>(std::move(RasterizerState::Wireframe(this)));
}

std::unique_ptr<IRenderTarget> GraphicsDevice::CreateRenderTarget(
	size_t x,
	size_t y,
	PixelFormat format
)
{
	return std::make_unique<RenderTarget>(this, x, y, format);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState()
{
	return std::make_unique<SamplerState>(this);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState(
	TextureFilter Filter,
	TextureAddressMode AddressU,
	TextureAddressMode AddressV,
	TextureAddressMode AddressW,
	float MipLODBias,
	unsigned MaxAnisotropy,
	ComparisonFunction ComparisionFunction,
	const Math::Color &BorderColor,
	float MinLOD,
	float MaxLOD
)
{
	return std::make_unique<SamplerState>(
		this,
		Filter,
		AddressU,
		AddressV,
		AddressW,
		MipLODBias,
		MaxAnisotropy,
		ComparisionFunction,
		BorderColor,
		MinLOD,
		MaxLOD
	);
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_LinearClamp()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::LinearClamp(this)));
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_LinearWrap()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::LinearWrap(this)));
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_PointClamp()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::PointClamp(this)));
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_PointWrap()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::PointWrap(this)));
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_AnisotropicClamp()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::AnisotropicClamp(this)));
}

std::unique_ptr<ISamplerState> GraphicsDevice::CreateSamplerState_AnisotropicWrap()
{
	return std::make_unique<SamplerState>(std::move(SamplerState::AnisotropicWrap(this)));
}

std::unique_ptr<ITexture2D> GraphicsDevice::CreateTexture2D(const std::filesystem::path& path)
{
	return std::make_unique<Texture2D>(this, path);
}

std::unique_ptr<ITexture1D> GraphicsDevice::CreateTexture1D(
	size_t numElements,
	PixelFormat format
)
{
	return std::make_unique<Texture1D>(this, numElements, format);
}

std::unique_ptr<ITexture1D> GraphicsDevice::CreateTexture1D(std::span<Math::Color> colors)
{
	return std::make_unique<Texture1D>(this, colors);
}

std::unique_ptr<ITexture2D> GraphicsDevice::CreateTexture2D(
	void* data,
	size_t x,
	size_t y,
	PixelFormat format,
	BufferUsage usage
)
{
	return std::make_unique<Texture2D>(this, data, x, y, format, usage);
}

std::unique_ptr<ITextureCube> GraphicsDevice::CreateTextureCube(std::array<ITexture2D*, 6> faces)
{
	return std::make_unique<TextureCube>(this, faces);
}

std::unique_ptr<ITextureCube> GraphicsDevice::CreateTextureCube(const std::filesystem::path& path)
{
	return std::make_unique<TextureCube>(this, path);
}

std::unique_ptr<ITexture3D> GraphicsDevice::CreateTexture3D(std::span<ITexture2D*> textures)
{
	return std::make_unique<Texture3D>(this, std::span<Texture2D*>(
		reinterpret_cast<Texture2D**>(*textures.data()), 
		textures.size())
	);
}

std::unique_ptr<IVertexBuffer> GraphicsDevice::CreateVertexBuffer(
	const void* data,
	size_t structSize,
	size_t numVertices,
	BufferUsage usage
)
{
	return std::make_unique<VertexBuffer>(this, data, structSize, numVertices, usage);
}

IVertexBuffer* GraphicsDevice::GetScreenQuad() const noexcept
{
	return _screenQuad.get();
}

void* GraphicsDevice::NativeHandle() const noexcept
{
	return _device.Get();
}