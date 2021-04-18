#if OPENGL
	#define SV_POSITION POSITION
	#define VS_SHADERMODEL vs_3_0
	#define PS_SHADERMODEL ps_3_0
#else
	#define VS_SHADERMODEL vs_4_0_level_9_1
	#define PS_SHADERMODEL ps_4_0_level_9_1
#endif

matrix World;
matrix View;
matrix Projection;

texture SkyboxTexture;
sampler2D TextureSampler = sampler_state {
	Texture = (SkyboxTexture);
	magfilter = LINEAR;
	minfilter = LINEAR;
	mipfilter = LINEAR;
	AddressU = Mirror;
	AddressV = Mirror;
};

struct VertexShaderInput
{
	float4 Position : POSITION0;
	float2 UV : TEXCOORD0;
};

struct VertexShaderOutput
{
	float4 Position : SV_POSITION;
	float2 UV : TEXCOORD0;
};

VertexShaderOutput SkyboxVS(in VertexShaderInput input)
{
	VertexShaderOutput output = (VertexShaderOutput)0;
	float4 worldPosition = mul(input.Position, World);
	float4 viewPosition = mul(worldPosition, View);
	output.Position = mul(viewPosition, Projection);
	output.UV = input.UV;
	return output;
}

float4 SkyboxPS(VertexShaderOutput input) : COLOR
{
	return tex2D(TextureSampler,input.UV);
}

technique BasicColorDrawing
{
	pass P0
	{
		VertexShader = compile VS_SHADERMODEL SkyboxVS();
		PixelShader = compile PS_SHADERMODEL SkyboxPS();
	}
};