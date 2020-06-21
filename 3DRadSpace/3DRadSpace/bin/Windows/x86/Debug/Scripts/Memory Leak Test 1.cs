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
    double a;
    TextPrint txtprnt = (TextPrint)_3DRadSpaceDll.Game.GameObjects[1];
    public void Start()
    {
        a = 0;
    }
    public void Run(MouseState mouse, KeyboardState keyboard, GameTime time)
    {
        a = Math.Sqrt(5);
    }
    public void Draw(SpriteBatch batch,Matrix? view, Matrix? projection)
    {
        txtprnt.Text = a+"";
    }
    public void End()
    {

    }
}