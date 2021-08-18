using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using System.IO;

namespace Lib3DRadSpace_DX
{
    internal static class ContentHelper
    {
        internal static Texture2D LoadTextureFromFile(GraphicsDevice gd, string path)
        {
            FileStream stream = new FileStream(path, FileMode.Open);
            Texture2D txt = Texture2D.FromStream(gd, stream);
            stream.Dispose();
            return txt;
        }
    }
}
