cbuffer Data : register(b0)
{
    row_major matrix matWorld; // World transformation
    row_major matrix matView;  // View transformation
    row_major matrix matProj;  // Projection transformation
}

cbuffer Data2 : register(b1)
{
    float4 HighlightColor;
}

float4 VS_Main(float3 pos : POSITION) : SV_POSITION
{
    float4 p =  mul(float4(pos.xyz,1), matWorld);
    p = mul(p, matView);
    p = mul(p, matProj);
    return p;
}

float4 PS_Main(float4 vertex : SV_POSITION) : SV_TARGET
{
    return HighlightColor;
}