// Screen-Space Shadow Application Shader
// Applied as a fullscreen pass to composite shadows onto the rendered scene

#include "PostProcessBase.hlsl"

cbuffer ShadowData : register(b0)
{
    row_major matrix matLightViewProj;     // Light space transformation
    row_major matrix matInvViewProj;       // Inverse of camera view-projection (for position reconstruction)
    float3 LightDirection;
    float ShadowBias;
    float ShadowIntensity;                  // How dark shadows are (0 = black, 1 = no shadow)
    float2 padding;
}

Texture2D colorTexture : register(t0);      // Scene color (backbuffer)
Texture2D depthTexture : register(t1);      // Scene depth
Texture2D shadowMap : register(t2);         // Shadow map from light

SamplerState colorSampler : register(s0);
SamplerState depthSampler : register(s1);
SamplerState shadowSampler : register(s2);

// Reconstruct world position from depth buffer
float3 ReconstructWorldPosition(float2 uv, float depth)
{
    // Convert UV and depth to NDC coordinates
    float4 ndc;
    ndc.x = uv.x * 2.0 - 1.0;
    ndc.y = (1.0 - uv.y) * 2.0 - 1.0;  // Flip Y
    ndc.z = depth;
    ndc.w = 1.0;

    // Transform to world space
    float4 worldPos = mul(ndc, matInvViewProj);
    worldPos /= worldPos.w;  // Perspective divide

    return worldPos.xyz;
}

float CalculateShadow(float3 worldPos)
{
    // Transform world position to light space
    float4 lightSpacePos = mul(float4(worldPos, 1.0), matLightViewProj);

    // Perform perspective divide
    float3 projCoords = lightSpacePos.xyz / lightSpacePos.w;

    // Transform to [0,1] range for texture sampling
    projCoords.x = projCoords.x * 0.5 + 0.5;
    projCoords.y = projCoords.y * -0.5 + 0.5;  // Flip Y for D3D

    // Outside shadow map bounds = not in shadow
    if (projCoords.x < 0.0 || projCoords.x > 1.0 ||
        projCoords.y < 0.0 || projCoords.y > 1.0 ||
        projCoords.z > 1.0)
        return 1.0;

    // Get closest depth from shadow map
    float closestDepth = shadowMap.Sample(shadowSampler, projCoords.xy).r;

    // Get current fragment depth
    float currentDepth = projCoords.z;

    // Compare depths with bias
    float shadow = (currentDepth - ShadowBias) > closestDepth ? ShadowIntensity : 1.0;

    return shadow;
}

float4 PS_Main(VertexOut v) : SV_TARGET
{
    // Sample scene color
    float4 color = colorTexture.Sample(colorSampler, v.UV);

    // Sample depth
    float depth = depthTexture.Sample(depthSampler, v.UV).r;

    // Skip skybox (depth = 1.0 or 0.0 depending on depth configuration)
    if (depth >= 0.9999)
        return color;

    // Reconstruct world position from depth
    float3 worldPos = ReconstructWorldPosition(v.UV, depth);

    // Calculate shadow factor
    float shadowFactor = CalculateShadow(worldPos);

    // Apply shadow to color
    return color * shadowFactor;
}
