#if OPENGL
#define SV_POSITION POSITION
#define VS_SHADERMODEL vs_3_0
#define PS_SHADERMODEL ps_3_0
#else
#define VS_SHADERMODEL vs_4_0_level_9_1
#define PS_SHADERMODEL ps_4_0_level_9_1
#endif

/*
* This is a awful skybox shader. Using BasicEffect for drawing a skybox was a easier approach, but I tried writing my own shader for performance reasons...
*/
matrix World;
matrix View;
matrix Projection;
float UVOffsetX = 0.0f;
float UVOffsetY = 0.0f;

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
	output.UV.x = UVOffsetX - input.UV.x;
	output.UV.y = UVOffsetY - input.UV.y;
	return output;
}

float4 SkyboxPS(VertexShaderOutput input) : COLOR
{
	return tex2D(TextureSampler,input.UV);
}

technique SkyboxDrawing
{
	pass P0
	{
		VertexShader = compile VS_SHADERMODEL SkyboxVS();
		PixelShader = compile PS_SHADERMODEL SkyboxPS();
	}
};