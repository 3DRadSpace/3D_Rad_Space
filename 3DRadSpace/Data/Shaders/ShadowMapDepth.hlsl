// Shadow Map Depth Shader
// Renders depth from light's perspective for shadow mapping

cbuffer ShadowData : register(b0)
{
    row_major matrix matLight; // Light space transformation matrix
    row_major matrix matView; // View matrix for the light
    row_major matrix matProj; // Projection matrix for the light
}

struct VertexIn
{
    float3 Position : POSITION;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float Depth : TEXCOORD0;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = mul(float4(v.Position.xyz, 1), matLight);
    r.Position = mul(r.Position, matView);
    r.Position = mul(r.Position, matProj);
    r.Depth = r.Position.z / r.Position.w;
    return r;
}

void PS_Main(VertexOut v)
{
    //Depth is written automatically
}
