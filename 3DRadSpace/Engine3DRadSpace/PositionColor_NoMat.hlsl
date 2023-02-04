struct VertexIn
{
    float4 Position : POSITION;
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
    r.Position = v.Position;
    r.Color = v.Color;
    return r;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    return v.Color;
}