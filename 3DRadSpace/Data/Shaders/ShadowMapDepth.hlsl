// Shadow Map Depth Shader
// Renders depth from light's perspective for shadow mapping

cbuffer ShadowData : register(b0)
{
    row_major matrix matWorld;              // World transformation
    row_major matrix matLightViewProj;      // Light space VP
};

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
    // Transform vertex to world space, then to light space
    float4 worldPos = mul(float4(v.Position.xyz, 1), matWorld);
    r.Position = mul(worldPos, matLightViewProj);
    r.Depth = r.Position.z / r.Position.w;
    return r;
}

// Pixel shader can be empty for depth-only rendering
// The depth buffer is automatically written by the hardware
void PS_Main(VertexOut v)
{
    // No output needed - depth is written automatically
}
