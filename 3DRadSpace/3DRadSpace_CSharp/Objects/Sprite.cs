using Engine3DRadSpace.Graphics;
using Engine3DRadSpace.Math;
using System.Runtime.InteropServices;

namespace Engine3DRadSpace.Objects
{
	public class Sprite : InstIObject2D
	{
		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Sprite_Create")]
		extern static IntPtr _create();

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Sprite_GetFlipU")]
		extern static byte _getFlipU(IntPtr sprite);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Sprite_SetFlipU")]
		extern static void _setFlipU(IntPtr sprite, byte flipU);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Sprite_GetFlipV")]
		extern static byte _getFlipV(IntPtr sprite);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Sprite_SetFlipV")]
		extern static byte _setFlipV(IntPtr sprite, byte flipV);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Sprite_GetTextureID")]
		extern static uint _getTextureID(IntPtr sprite);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Sprite_SetTextureID")]
		extern static void _setTextureID(IntPtr sprite, uint id);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Sprite_GetTexture")]
		extern static IntPtr _getTexture(IntPtr sprite);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Sprite_GetTintColor")]
		extern static Color _getColor(IntPtr sprite);

		[DllImport("3DRadSpace.FFI.dll", EntryPoint = "E3DRSP_Sprite_SetTintColor")]
		extern static unsafe void _setColor(IntPtr sprite, Color* color);

		public Sprite() : base(_create())
		{

		}

		public bool FlipU
		{
			get => _getFlipU(_handle) > 0;
			set => _setFlipU(_handle, value ? (byte)1 : (byte)0);
		}

		public bool FlipV
		{
			get => _getFlipV(_handle) > 0;
			set => _setFlipV(_handle, value ? (byte)1 : (byte)0);
		}

		public uint TextureID
		{
			get => _getTextureID(_handle);
			set => _setTextureID(_handle, value);
		}

		public ITexture2D GetTexture()  
		{
			return new InstITexture2D(_getTexture(_handle), ownsHandle: false);
		}

		public unsafe Color TintColor
		{
			get => _getColor(_handle);
			set => _setColor(_handle, &value);
		}

	}
}
