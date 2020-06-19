using _3DRadSpaceDll;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Media;
using System;

class Script
{
    Skinmesh _ourmesh;
    Camera c;
    public void Start()
    {
        _ourmesh = (Skinmesh)_3DRadSpaceDll.Game.GameObjects[0];
        c = (Camera)_3DRadSpaceDll.Game.GameObjects[2];
    }
    public void Run(MouseState mouse, KeyboardState keyboard, GameTime time)
    {
        if(keyboard.IsKeyDown(Keys.Up)) _ourmesh.Position.Z += 1;
        if(keyboard.IsKeyDown(Keys.Down)) _ourmesh.Position.Z -= 1;
        if(keyboard.IsKeyDown(Keys.Right)) _ourmesh.Position.X -= 1;
        if(keyboard.IsKeyDown(Keys.Left)) _ourmesh.Position.X += 1;
        c.Update(mouse,keyboard,time);
    }
    public void Draw(SpriteBatch batch,Matrix? view, Matrix? projection)
    {
    
    }
    public void End()
    {

    }
}