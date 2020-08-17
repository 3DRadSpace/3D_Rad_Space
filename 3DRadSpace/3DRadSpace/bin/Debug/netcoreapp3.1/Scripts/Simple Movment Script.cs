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
    Camera _ourCamera; //*insert ussr athemn
    public void Start()
    {
        _ourCamera = (Camera)Main.GameObjects[0];
    }
    public void Run(MouseState mouse, KeyboardState keyboard, GameTime time)
    {
        if(keyboard.IsKeyDown(Keys.Up)) _ourCamera.Position.Z += 1;
        if(keyboard.IsKeyDown(Keys.Down)) _ourCamera.Position.Z -= 1;
        if(keyboard.IsKeyDown(Keys.Right)) _ourCamera.Position.X -= 1;
        if(keyboard.IsKeyDown(Keys.Left)) _ourCamera.Position.X += 1;
        if(keyboard.IsKeyDown(Keys.Q)) _ourCamera.Position.Y += 1;
        if(keyboard.IsKeyDown(Keys.E)) _ourCamera.Position.Y -= 1;
        _ourCamera.CameraTarget = _ourCamera.Position + new Vector3(0,0,1);
    }
    public void Draw(SpriteBatch batch,Matrix? view, Matrix? projection)
    {
    
    }
    public void End()
    {

    }
}