// Percentage-Closer Filtering (PCF) shadow sampling helper.
#ifndef PCF_HLSL
#define PCF_HLSL

// Computes the receiver plane depth bias (dz/du, dz/dv), i.e. how much the light-space depth
// changes per unit of shadow map UV, derived from the screen-space derivatives of the projected
// shadow coordinates. Used to compensate the per-tap PCF depth comparison for surface slope,
// which otherwise produces triangle/spike-shaped self-shadowing artifacts ("perspective aliasing")
// on surfaces that are steeply angled relative to the light.
float2 PCF_ComputeReceiverPlaneDepthBias(float3 projCoords)
{
    float3 duvdist_dx = ddx(projCoords);
    float3 duvdist_dy = ddy(projCoords);

    float det = (duvdist_dx.x * duvdist_dy.y) - (duvdist_dy.x * duvdist_dx.y);
    float invDet = (abs(det) > 1e-8) ? (1.0 / det) : 0.0;

    float2 ddist_duv;
    ddist_duv.x = duvdist_dy.y * duvdist_dx.z - duvdist_dx.y * duvdist_dy.z;
    ddist_duv.y = duvdist_dx.x * duvdist_dy.z - duvdist_dy.x * duvdist_dx.z;
    ddist_duv *= invDet;

    // Clamp: near-silhouette/grazing angles make the Jacobian ill-conditioned, producing huge
    // (unstable) bias values. Clamping keeps the correction bounded and prevents light-bleeding.
    return clamp(ddist_duv, -10.0, 10.0);
}

float PCF_CalculateShadow(Texture2D<float> shadowMap, SamplerState shadowSampler, float3 projCoords, float2 texelSize, float shadowBias, float shadowIntensity)
{
    float2 receiverPlaneDepthBias = PCF_ComputeReceiverPlaneDepthBias(projCoords);

    float sum = 0.0;
    [unroll]
    for (int x = -1; x <= 1; x++)
    {
        [unroll]
        for (int y = -1; y <= 1; y++)
        {
            float2 offset = float2(x, y) * texelSize;
            float closestDepth = shadowMap.Sample(shadowSampler, projCoords.xy + offset).r;

            // Adjust the compared depth by how much the surface's depth is expected to change
            // across this texel offset, so the comparison follows the surface slope instead of
            // a single flat bias value.
            float slopeAdjustedDepth = projCoords.z + dot(receiverPlaneDepthBias, offset);

            sum += (slopeAdjustedDepth - shadowBias > closestDepth) ? shadowIntensity : 1.0;
        }
    }

    return sum / 9.0;
}

#endif // PCF_HLSL
