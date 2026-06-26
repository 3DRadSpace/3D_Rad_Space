#include "ForwardShadowMapping.hlsl"

cbuffer Data : register(b0)
{
    row_major matrix matWorld; // World transformation
    row_major matrix matView; // View transformation
    row_major matrix matProj; // Projection transformation
}

cbuffer ShadowData : register(b1)
{
    row_major matrix matLightViewProj; //Light view projection matrix
    float2 ShadowOffset;
    float ShadowBias;
    float ShadowIntensity;
}

Texture2D TextureModel : register(t0);
SamplerState TextureSampler : register(s0);

Texture2D ShadowMap : register(t1);
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
    float2 UV: TEXCOORD0;
    float4 LightSpacePos : TEXCOORD1;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = mul(float4(v.Position.xyz,1), matWorld);
    r.Position = mul(r.Position, matView);
    r.Position = mul(r.Position, matProj);
	r.UV = v.UV;
    
    float4 worldPos = mul(float4(v.Position.xyz, 1), matWorld);
    r.LightSpacePos = mul(worldPos, matLightViewProj);
    
    return r;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    return TextureModel.Sample(TextureSampler, v.UV) * ComputeShadow(v.LightSpacePos, ShadowMap, ShadowSampler, ShadowOffset, ShadowBias, ShadowIntensity);
}