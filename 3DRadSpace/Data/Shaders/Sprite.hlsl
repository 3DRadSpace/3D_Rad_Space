cbuffer Data : register(b0)
{
    float4 TintColor;
    bool FlipU; // sizeof(bool) in HLSL is 4!
    bool FlipV;
}

Texture2D TextureModel : register(t0);
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
    
    //flip X
    if (FlipU)
        r.UV.x = 1 - v.UV.x;
    else
        r.UV.x = v.UV.x;
    
    // flip X
    if(FlipV)
        r.UV.y = 1 - v.UV.y;
    else 
        r.UV.y = v.UV.y;
    return r;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    return TintColor * TextureModel.Sample(TextureSampler, v.UV);
}