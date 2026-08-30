using System.Drawing;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Graphics;

public class Font : NatPtrWrapper
{
	[DllImport("3DRadSpace.FFI.dll", CharSet = CharSet.Ansi, EntryPoint = "E3DRSP_Font_Create")]
	extern static IntPtr _create(IntPtr device, string path, uint size, string supportedCharacters);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Font_Create")]
	extern static uint _size(IntPtr font);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Font_SupportedCharacters")]
	extern static IntPtr _supportedCharacters(IntPtr font);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Font_GetTexture")]
	extern static IntPtr _texture(IntPtr font);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Font_GetCharGlyph")]
	extern static IntPtr _glyph(IntPtr font, char chr);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Font_GetCharGlyph")]
	extern static IntPtr _srcRect(IntPtr font, char chr);

	[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Font_Destroy")]
	extern static void _destroy(IntPtr font);

	public Font(IGraphicsDevice device, string path, uint size, string supportedCharacters) : base(_create(device.Handle, path, size, supportedCharacters), null)
	{
	}

	public Font(IGraphicsDevice device, string path, uint size = 14) : base(_create(device.Handle, path, size, ""), null)
	{
	}

	public Font(IntPtr handle) : base(handle, null)
	{
	}

	public uint Size
	{
		get => _size(_handle);
	}

	public string SupportedCharacters
	{
		get => Marshal.PtrToStringAnsi(_supportedCharacters(_handle)); 
	}

	public ITexture2D Texture
	{
		get => new InstITexture2D(_texture(_handle));
	}

	unsafe Glyph? _getGliph(char chr)
	{
		var pGlyph = _glyph(_handle, chr);
		if (pGlyph == IntPtr.Zero)
		{
			return null;
		}

		return *((Glyph*)pGlyph);
	}

	public Glyph? GetCharGliph(char chr)
	{
		return _getGliph(chr);
	}

	unsafe Internal.Rectangle? _getSrcRectangle(char chr)
	{
		var pRect = _srcRect(_handle, chr);
		if (pRect == IntPtr.Zero)
		{
			return null;
		}

		return *((Internal.Rectangle*)pRect);
	}

	public Rectangle? GetSourceRectangle(char chr)
	{
		var optR = _getSrcRectangle(chr);
		if (!optR.HasValue)
		{
			return null;
		}

		var r = optR.Value;

		return new Rectangle(r.X, r.Y, r.Width, r.Height);
	}
}
