using System.Runtime.InteropServices;
using System.Numerics;

namespace Engine3DRadSpace.Graphics.Rendering;

[StructLayout(LayoutKind.Sequential)]
public struct DirectionalLight
{
    public Math.Color LightColor;
    public Math.Color AmbientColor;
    public Vector3 LightDirection;
    public float Intensity;

    public DirectionalLight(Math.Color lightColor, Math.Color ambientColor, Vector3 lightDirection, float intensity)
    {
        LightColor = lightColor;
        AmbientColor = ambientColor;
        LightDirection = lightDirection;
        Intensity = intensity;
    }
}
