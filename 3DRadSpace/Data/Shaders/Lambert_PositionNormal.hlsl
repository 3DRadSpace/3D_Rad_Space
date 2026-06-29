cbuffer AllData : register(b0)
{
    row_major matrix matWorldViewProj;
    row_major matrix matWorldInverseTranspose;
    float4 LightColor;
    float4 AmbientColor;
    float3 LightDirection;
    float Intensity;
}

struct VertexIn
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float4 Color : COLOR;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL;
    float4 Color : COLOR;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = mul(float4(v.Position.xyz, 1), matWorldViewProj);
    r.Normal = mul(float4(v.Normal.xyz, 0), matWorldInverseTranspose).xyz;
    r.Color = v.Color;
    return r;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    float diffuse = max(0, dot(normalize(v.Normal), -LightDirection));
    return v.Color * (AmbientColor + LightColor * Intensity * diffuse);
}