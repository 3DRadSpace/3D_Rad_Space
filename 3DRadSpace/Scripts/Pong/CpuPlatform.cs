using Engine3DRadSpace;
using Engine3DRadSpace.Objects;
using Engine3DRadSpace.Scripting;
using System.Numerics;

namespace _3DRadSpace_CSharp_Sample
{
    public class CpuPlatform : Script
    {
        IObject2D platform;
        IObject2D ball;

        Game game;

        public CpuPlatform()
        {
        }

        const float aiMovementSpeed = 3.0f;

        public override void Start()
        {
            platform = Object.Parent as IObject2D;
            if (platform == null) throw new NullReferenceException("This script is supposed to be attached to a Sprite");

            game = Object.Game as Game;
            if (game == null) throw new NullReferenceException("Game is null");

            ball = game.ObjectList.Find(0) as IObject2D;
            if (ball == null) throw new NullReferenceException("Ball is null");
        }

        public override void Update()
        {
            float dt = game.UpdateDeltaTime;
            float ballCenterY = ball.Position.Y + ball.Scale.Y / 2;
            float platformCenterY = platform.Position.Y + platform.Scale.Y / 2;

            if (ballCenterY > platformCenterY)
            {
                platform.Position += new Vector2(0, aiMovementSpeed * dt);
            }
            else if (ballCenterY < platformCenterY)
            {
                platform.Position -= new Vector2(0, aiMovementSpeed * dt);
            }

            platform.Position = new Vector2(platform.Position.X, Math.Clamp(platform.Position.Y, 0, 1 - platform.Scale.Y));
        }
    }
}
