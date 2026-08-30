using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using Engine3DRadSpace;
using Engine3DRadSpace.Objects;
using Engine3DRadSpace.Scripting;

namespace Pong
{
    public class PlayerPlatform : Script
    {
        IObject2D platform;
        Game game;

        Vector2 resolution;
        public override void Start()
        {
            platform = Object.Parent as IObject2D;
            if (platform == null) throw new NullReferenceException("This script is supposed to be attached to a Sprite");

            game = Object.Game as Game;
            if (game == null) throw new NullReferenceException("Game is null");

            var p = game.GraphicsDevice.GetResolution();
            resolution = new Vector2(p.X, p.Y);
        }

        public override void Update()
        {
            Vector2 newPos = new Vector2( 0, (float)game.Mouse.Position.Y / resolution.Y);
            newPos.Y = Math.Clamp(newPos.Y, 0, 1 - platform.Scale.Y);
            platform.Position = newPos;
        }
    }
}
