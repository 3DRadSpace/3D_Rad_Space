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
    public Script() 
    {
        
    }
    SkyColor ourSky;
    public void Start()
    {
        ourSky = _3DRadSpaceDll.Game.GameObjects[0] as SkyColor;
    }
    public void Run(MouseState mouse, KeyboardState keyboard, GameTime time)
    {

    }
    public void Draw(SpriteBatch batch,Matrix? view, Matrix? projection)
    {
        Color a = ourSky.Color;
        a.R += 1;
        ourSky.Color = a;
    }
    public void End()
    {

    }
}