cbuffer Data : register(b0)
{
    row_major matrix matWorldViewProj; // MVP transformation
}

Texture2D TextureModel : register(t0);
SamplerState TextureSampler : register(s0);

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
    float2 UV: TEXCOORD;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = mul(float4(v.Position.xyz,1), matWorldViewProj);
	r.UV = v.UV;
    return r;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    return TextureModel.Sample(TextureSampler, v.UV);
}