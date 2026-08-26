using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics.Rendering;

[StructLayout(LayoutKind.Sequential)]
public struct MaterialDescriptor
{
    public bool HasShadows;
    public IntPtr Extra;
    public MaterialDescriptor(bool hasShadows, IntPtr extra) 
    {
        HasShadows = hasShadows;
        Extra = extra;
    }
}
