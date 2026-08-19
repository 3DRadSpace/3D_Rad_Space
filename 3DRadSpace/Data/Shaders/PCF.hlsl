// Percentage-Closer Filtering (PCF) shadow sampling helper.
#ifndef PCF_HLSL
#define PCF_HLSL

float PCF_CalculateShadow(Texture2D<float> shadowMap, SamplerState shadowSampler, float2 uv, float currentDepth, float2 texelSize, float shadowBias, float shadowIntensity)
{
    float sum = 0.0;
    [unroll]
    for (int x = -1; x <= 1; x++)
    {
        [unroll]
        for (int y = -1; y <= 1; y++)
        {
            float2 offset = float2(x, y) * texelSize;
            float closestDepth = shadowMap.Sample(shadowSampler, uv + offset).r;
            sum += (currentDepth - shadowBias > closestDepth) ? shadowIntensity : 1.0;
        }
    }

    return sum / 9.0;
}

#endif // PCF_HLSL
