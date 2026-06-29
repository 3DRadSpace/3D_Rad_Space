cbuffer Data : register(b0)
{
	row_major matrix matWorldViewProj; // MVP transformation
}

TextureCube CubeMapTexture : register(t0);
SamplerState CubeMapSampler
{
	Texture = <CubeMapTexture>;
	AddressU = CLAMP;
	AddressV = CLAMP;

	AddressW = CLAMP;
	BorderColor = float4(1, 1, 1, 1);

	Filter = LINEAR;
};

struct VertexIn
{
	float3 Position : POSITION;
};

struct VertexOut
{
	float4 Position : SV_POSITION;
	float3 UVW : TEXCOORD0;
};

VertexOut VS_Main(VertexIn v)
{
	VertexOut output;
	output.Position = mul(float4(v.Position, 1.0f), matWorldViewProj);
	output.Position.z = output.Position.w;
	output.UVW = v.Position;
	return output;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
	return CubeMapTexture.Sample(CubeMapSampler, normalize(v.UVW));
}