using Engine3DRadSpace;
using Engine3DRadSpace.Math;
using Engine3DRadSpace.Graphics;
using Engine3DRadSpace.Reflection;
using Engine3DRadSpace.Scripting;
using System;
using System.Numerics;
using System.Drawing;
using Engine3DRadSpace.Objects;

namespace _3DRadSpace_CSharp_Sample
{
    public class PongBall : Script
    {
        IObject2D ball;

        public override void Start()
        {
            ball = Object.Parent as IObject2D;
        }

        public override void Update()
        {
            var game = ((Object.GraphicsDevice as InstIGraphicsDevice).Owner as Game);
        }
        public override void End()
        {
            
        }
    }
}
