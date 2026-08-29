using System.Globalization;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Reflection;

/// <summary>
/// Type with the same memory layout as Reflection::UUID.
/// </summary>
[StructLayout(LayoutKind.Sequential)]
public struct UUID
{
    public uint Data1;
    public ushort Data2;
    public ushort Data3;
    public byte Data4_1;
    public byte Data4_2;
    public byte Data4_3;
    public byte Data4_4;
    public byte Data4_5;
    public byte Data4_6;
    public byte Data4_7;
    public byte Data4_8;

    public UUID(string uuid)
    {
        uuid = uuid.Trim('{', '}');

        var parts = uuid.Split('-');

        Data1 = uint.Parse(parts[0], NumberStyles.HexNumber);
        Data2 = ushort.Parse(parts[1], NumberStyles.HexNumber);
        Data3 = ushort.Parse(parts[2], NumberStyles.HexNumber);

        var data4 = parts[3] + parts[4];

        Data4_1 = byte.Parse(data4.Substring(0, 2), NumberStyles.HexNumber);
        Data4_2 = byte.Parse(data4.Substring(2, 2), NumberStyles.HexNumber);
        Data4_3 = byte.Parse(data4.Substring(4, 2), NumberStyles.HexNumber);
        Data4_4 = byte.Parse(data4.Substring(6, 2), NumberStyles.HexNumber);
        Data4_5 = byte.Parse(data4.Substring(8, 2), NumberStyles.HexNumber);
        Data4_6 = byte.Parse(data4.Substring(10, 2), NumberStyles.HexNumber);
        Data4_7 = byte.Parse(data4.Substring(12, 2), NumberStyles.HexNumber);
        Data4_8 = byte.Parse(data4.Substring(14, 2), NumberStyles.HexNumber);
    }

    public UUID(uint data1, ushort data2, ushort data3, byte data4_1, byte data4_2, byte data4_3, byte data4_4, byte data4_5, byte data4_6, byte data4_7, byte data4_8)
    {
        Data1 = data1;
        Data2 = data2;
        Data3 = data3;
        Data4_1 = data4_1;
        Data4_2 = data4_2;
        Data4_3 = data4_3;
        Data4_4 = data4_4;
        Data4_5 = data4_5;
        Data4_6 = data4_6;
        Data4_7 = data4_7;
        Data4_8 = data4_8;
    }
}