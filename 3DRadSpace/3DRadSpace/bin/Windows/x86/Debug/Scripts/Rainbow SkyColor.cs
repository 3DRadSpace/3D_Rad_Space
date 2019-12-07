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
    SkyColor ourSky; //I have achieved communism
    public void Start()
    {
        ourSky = (SkyColor)_3DRadSpaceDll.Game.FindObject(0);
    }
    public void Run(MouseState mouse, KeyboardState keyboard, GameTime time)
    {
        
    }
    public void Draw(SpriteBatch batch,Matrix? view, Matrix? projection)
    {
        if(ourSky.Color.R < 255)
        {
            ourSky.Color.R += 1;
            return;
        }
        else ourSky.Color.R =0;

        if(ourSky.Color.G < 255)
        {
            ourSky.Color.G += 1;
            return;
        }
        else ourSky.Color.G =0;

        if(ourSky.Color.B < 255)
        {
            ourSky.Color.B += 1;
            return;
        }
        else ourSky.Color.B =0;

        _3DRadSpaceDll.Game.GameObjects[0] = ourSky;
    }
    public void End()
    {

    }
}