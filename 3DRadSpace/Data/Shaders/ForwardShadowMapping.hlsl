/// Computes the shadow factor for a given light space position using a shadow map.
float ComputeShadow(float4 lightSpacePos, Texture2D<float> shadowMap, SamplerState shadowSampler, float2 offset, float shadowBias, float shadowIntensity)
{
    float3 proj = lightSpacePos.xyz / lightSpacePos.w;

    // NDC [-1,1] -> texture UV [0,1], flipping Y for D3D.
    float2 uv = proj.xy * float2(0.5, -0.5) + 0.5;

    // Outside the shadow map (or beyond the far plane) means lit.
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0 || proj.z > 1.0 || proj.z < 0.0)
        return 1.0;

    float currentDepth = proj.z;
    
    float closestDepth = shadowMap.Sample(shadowSampler, uv + offset).r;
    return (currentDepth - shadowBias > closestDepth) ? (1.0 - shadowIntensity) : 1.0;
}

float ComputeShadowPCF(float4 lightSpacePos, Texture2D<float> shadowMap, SamplerState shadowSampler, float2 offset, float shadowBias, float shadowIntensity)
{
    float3 proj = lightSpacePos.xyz / lightSpacePos.w;
    // NDC [-1,1] -> texture UV [0,1], flipping Y for D3D.
    float2 uv = proj.xy * float2(0.5, -0.5) + 0.5;
    // Outside the shadow map (or beyond the far plane) means lit.
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0 || proj.z > 1.0 || proj.z < 0.0)
        return 1.0;
    float currentDepth = proj.z;
    
    // Percentage Closer Filtering (PCF)
    int samples = 4;
    float shadowFactor = 0.0;
    for (int x = -samples; x <= samples; ++x)
    {
        for (int y = -samples; y <= samples; ++y)
        {
            float2 sampleOffset = offset * float2(x, y);
            float closestDepth = shadowMap.Sample(shadowSampler, uv + sampleOffset).r;
            if (currentDepth - shadowBias > closestDepth)
                shadowFactor += 1.0;
        }
    }
    
    float totalSamples = (samples * 2 + 1) * (samples * 2 + 1);
    return 1.0 - (shadowFactor / totalSamples) * shadowIntensity;
}