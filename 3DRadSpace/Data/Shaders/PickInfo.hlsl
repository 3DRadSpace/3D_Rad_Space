cbuffer Data : register(b0)
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

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = mul(v.Position, matWorldViewProj);
    return r;
}

int PS_Main(VertexOut v) : SV_TARGET
{
    return ID;
}