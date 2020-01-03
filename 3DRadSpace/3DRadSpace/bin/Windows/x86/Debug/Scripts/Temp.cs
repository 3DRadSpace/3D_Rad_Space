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
    SkyColor ourSky;
    public void Start()
    {
        ourSky = (SkyColor)_3DRadSpaceDll.Game.FindObject(0);
    }
    public void Run(MouseState mouse, KeyboardState keyboard, GameTime time)
    {
        ourSky.Color= new Color(ourSky.Color.R+1,0,0);
    }
    public void Draw(SpriteBatch batch,Matrix? view, Matrix? projection)
    {
    
    }
    public void End()
    {

    }
}