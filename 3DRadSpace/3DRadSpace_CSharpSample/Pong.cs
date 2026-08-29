using Engine3DRadSpace.Graphics;
using Engine3DRadSpace.Internal;
using Engine3DRadSpace.Scripting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpace_CSharp_Sample
{
    public class Pong : Script
    {
        public Pong() { }

        ITexture2D whiteBox;

        public override void Start()
        {
            whiteBox = Object.GraphicsDevice.WhiteBlank();
        }

        public override void Update()
        {
        
        }

        public override void End()
        {
            
        }
    }
}
