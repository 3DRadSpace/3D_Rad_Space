cbuffer Data : register(b0)
{
    row_major matrix matWorldViewProj; // MVP transformation
}

cbuffer Data2 : register(b1)
{
    float4 HighlightColor;
}

float4 VS_Main(float3 pos : POSITION) : SV_POSITION
{
    return mul(float4(pos.xyz,1), matWorldViewProj);
}

float4 PS_Main(float4 vertex : SV_POSITION) : SV_TARGET
{
    return HighlightColor;
}