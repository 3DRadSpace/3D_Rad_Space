cbuffer Data : register(b0)
{
    row_major matrix matWorldViewProj; // MVP transformation
}

struct VertexIn
{
    float3 Position : POSITION;
    float4 Color : COLOR;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = mul(float4(v.Position.xyz,1), matWorldViewProj);
    r.Color = v.Color;
    return r;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    return v.Color;
}