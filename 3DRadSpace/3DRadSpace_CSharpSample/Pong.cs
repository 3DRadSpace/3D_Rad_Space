using Engine3DRadSpace;
using Engine3DRadSpace.Math;
using Engine3DRadSpace.Graphics;
using Engine3DRadSpace.Reflection;
using Engine3DRadSpace.Scripting;
using System;
using System.Numerics;
using System.Drawing;

namespace _3DRadSpace_CSharp_Sample
{
    static class Randomizer
    {
        static Random random = new Random();

        public static float NextSingle(float min, float max)
        {
            return (float)(random.NextDouble() * (max - min) + min);
        }

        public static Vector2 NextDirection()
        {
            float theta = NextSingle(0, (float)(2 * Math.PI));
            return new Vector2((float)Math.Cos(theta), (float)Math.Sin(theta));
        }
    }

    struct Ball
    {
        public float x;
        public float y;
        public float radius;

        public Ball(float x, float y, float radius)
        {
            this.x = x;
            this.y = y;
            this.radius = radius;
        }
    }

    public class Pong : Script
    {
        Ball Ball;
        private static Random random = new Random();

        SpriteBatch spriteBatch;
        ITexture2D ball;

        public override void Start()
        {
            Ball = new Ball(random.NextSingle(), random.NextSingle(), random.NextSingle());

            spriteBatch = ((Object.GraphicsDevice as InstIGraphicsDevice).Owner as Game).SpriteBatch;

            UUID uuid = InstITexture2D.UUID;
            ball = ((Object.GraphicsDevice as InstIGraphicsDevice).Owner as Game).ContentManager.Load(ref uuid, "ball.png").Item1 as InstITexture2D;
        }

        public override void Update()
        {
            spriteBatch.Begin(SpriteBatchSortMode.Immediate);
            spriteBatch.DrawNormalized(
                ball,
                new RectangleF(Ball.x, Ball.y, Ball.radius * 2, Ball.radius * 2), 
                new RectangleF(0, 0, 1, 1), 
                new Engine3DRadSpace.Math.Color(1, 1, 1, 1),
                0.0f,
                FlipMode.None,
                0
            );
            spriteBatch.End();
        }
        public override void End()
        {
            
        }
    }
}
