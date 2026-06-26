cbuffer Data : register(b0)
{
    row_major matrix matWorld; // World transformation
    row_major matrix matView; // View transformation
    row_major matrix matProj; // Projection transformation
}

Texture2D texDiffuse : register(t0);
SamplerState texSampler : register(s0);

struct VertexIn
{
    float3 Position : POSITION;
    float2 UV : TEXCOORD0;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = mul(float4(v.Position.xyz,1), matWorld);
    r.Position = mul(r.Position, matView);
    r.Position = mul(r.Position, matProj);
    r.UV = v.UV;
    return r;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    return texDiffuse.Sample(texSampler, v.UV);
}