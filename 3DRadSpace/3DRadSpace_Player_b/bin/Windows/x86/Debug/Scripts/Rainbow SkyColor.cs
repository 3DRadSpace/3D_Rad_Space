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
    void RGBFade(ref byte r,ref byte g,ref byte b)
    {
        if(r > 0 && b == 0)
        {
            r--;
            g++;
        }
        if(g > 0 && r == 0)
        {
            g--;
            b++;
        }
        if(b > 0 && g == 0)
        {
            r++;
            b--;
        } 
    }
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
        byte R,G,B;
        R = ourSky.Color.R;
        G = ourSky.Color.G;
        B = ourSky.Color.B;
        RGBFade(ref R,ref G,ref B);
        ourSky.Color.R = R;
        ourSky.Color.G = G;
        ourSky.Color.B = B;
    }
    public void End()
    {

    }
}