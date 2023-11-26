cbuffer Data : register(b0)
{
    float4 TintColor;
}

Texture2D<float> GlyphTexture : register(t0);
SamplerState TextureSampler : register(s0);

struct VertexIn
{
    float2 Position : POSITION;
    float2 UV : TEXCOORD;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = float4(v.Position.xy, 0, 1);
    return r;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    return TintColor * GlyphTexture.Sample(TextureSampler, v.UV);
}