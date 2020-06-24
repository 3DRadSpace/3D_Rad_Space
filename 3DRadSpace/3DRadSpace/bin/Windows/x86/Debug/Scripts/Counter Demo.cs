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
    TextPrint txtprnt;
    Counter c;
    public void Start()
    {
        c = (Counter)_3DRadSpaceDll.Game.GameObjects[0];
        txtprnt = (TextPrint)_3DRadSpaceDll.Game.GameObjects[1];
    }
    public void Run(MouseState mouse, KeyboardState keyboard, GameTime time)
    {

    }
    public void Draw(SpriteBatch batch,Matrix? view, Matrix? projection)
    {
        txtprnt.Text = "Counter value: "+c.Value+" \n Press enter to increase.";
    }
    public void End()
    {

    }
}