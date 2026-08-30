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
        Game game;

        ObjectList list;

        IObject2D playerPlatform;
        IObject2D cpuPlatform;

        TextPrint scoreText;

        Vector2 direction;
        Random rng;

        public PongBall()
        {
            rng = new Random();
        }

        float playerScore = 0;
        float cpuScore = 0;

        const float ballSpeed = 5.0f;

        public override void Start()
        {
            ball = Object.Parent as IObject2D;
            if (ball == null ) throw new NullReferenceException("This script is supposed to atteched to a Sprite");

            game = ((Object.GraphicsDevice as InstIGraphicsDevice).Owner as Game);
            if (game == null ) throw new NullReferenceException("IGraphicsDevice is invalid");

            list = game.ObjectList;
            if(list == null ) throw new NullReferenceException("ObjectList is null");

            playerPlatform = list.Find(1) as IObject2D;
            if(playerPlatform == null) throw new NullReferenceException("Player platform is null");

            cpuPlatform = list.Find(2) as IObject2D;
            if(cpuPlatform == null) throw new NullReferenceException("CPU platform is null");

            Reset();
        }

        void Reset()
        {
            float theta = rng.NextSingle() * 2 * (float)Math.PI;
            direction = new Vector2((float)Math.Cos(theta), (float)Math.Sin(theta));
            direction = Vector2.Normalize(direction);

            ball.Position = new Vector2(0.5f - (ball.Scale.X / 2), 0.5f - (ball.Scale.Y / 2));
        }

        public override void Update()
        {
            scoreText.Text = $"Player {playerScore} - CPU {cpuScore}";
            ball.Position += direction * ballSpeed;

            if(ball.Position.X < -ball.Scale.X)
            {
                cpuScore++;
                Reset();
            }
            else if (ball.Position.X > 1.0f)
            {
                playerScore++;
                Reset();
            }

            if(collidesWith(playerPlatform))
            {
                direction.X = Math.Abs(direction.X);
                direction.Y = (ball.Position.Y + ball.Scale.Y / 2 - (playerPlatform.Position.Y + playerPlatform.Scale.Y / 2)) / (playerPlatform.Scale.Y / 2);
            }
            else if (collidesWith(cpuPlatform))
            {
                direction.X = -Math.Abs(direction.X);
                direction.Y = (ball.Position.Y + ball.Scale.Y / 2 - (cpuPlatform.Position.Y + cpuPlatform.Scale.Y / 2)) / (cpuPlatform.Scale.Y / 2);
            }
        }

        bool collidesWith(IObject2D other)
        {
            return ball.Position.X < other.Position.X + other.Scale.X &&
                   ball.Position.X + ball.Scale.X > other.Position.X &&
                   ball.Position.Y < other.Position.Y + other.Scale.Y &&
                   ball.Position.Y + ball.Scale.Y > other.Position.Y;
        }
    }
}
