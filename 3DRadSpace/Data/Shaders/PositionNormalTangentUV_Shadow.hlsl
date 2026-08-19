#include "PCF.hlsl"

cbuffer Data : register(b0)
{
    row_major matrix matWorldViewProj; // MVP transformation
    row_major matrix matWorld; // World transformation
}

cbuffer ShadowData : register(b1)
{
    row_major matrix matLightViewProj; // World-space to light clip-space transform
    row_major matrix matInvViewProj; //Camera Inv(VP)
    float3 LightDirection;
    float ShadowBias;
    float ShadowIntensity;
    float2 TexelSize;
}

Texture2D TextureModel : register(t0);
SamplerState TextureSampler : register(s0);

Texture2D<float> ShadowMap : register(t1);
SamplerState ShadowSampler : register(s1);

struct VertexIn
{
    float3 Position : POSITION;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 Bitangent: BITANGENT;
	float2 UV : TEXCOORD;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float3 WorldPos : POSITION;
    float2 UV: TEXCOORD;
};

VertexOut VS_Main(VertexIn v)
{
	VertexOut r;
	r.Position = mul(float4(v.Position.xyz,1), matWorldViewProj);
	r.WorldPos = mul(float4(v.Position.xyz,1), matWorld).xyz;
	r.UV = v.UV;
	return r;
}

float CalculateShadow(float3 worldPos)
{
    // Transform world position to light space
    float4 lightSpacePos = mul(float4(worldPos, 1.0), matLightViewProj);

    // Perform perspective divide
    float3 projCoords = lightSpacePos.xyz / lightSpacePos.w;

    // Transform to [0,1] range for texture sampling
    projCoords.x = projCoords.x * 0.5 + 0.5;
    projCoords.y = projCoords.y * -0.5 + 0.5; // Flip Y for D3D

    // Outside shadow map bounds = not in shadow
    if (projCoords.x < 0.0 || projCoords.x > 1.0 ||
        projCoords.y < 0.0 || projCoords.y > 1.0 ||
        projCoords.z > 1.0)
        return 1.0;

    return PCF_CalculateShadow(ShadowMap, ShadowSampler, projCoords.xy, projCoords.z, TexelSize, ShadowBias, ShadowIntensity);
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    float shadowFactor = CalculateShadow(v.WorldPos);
    float4 textureSample = TextureModel.Sample(TextureSampler, v.UV);
    return float4(textureSample.rgb * shadowFactor, textureSample.a);
}