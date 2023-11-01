cbuffer mybuff : register(b0)
{
    row_major matrix matWorldViewProj;
    uint ID;
};

struct VertexIn
{
    float4 Position : POSITION;
};

struct VertexOut
{
    float4 Position : SV_Position;
};

VertexIn VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = mul(v.Position, matWorldViewProj);
    return r;
}

float4 PS_Main(VertexIn v) : SV_TARGET
{
    return float4(ID);
}