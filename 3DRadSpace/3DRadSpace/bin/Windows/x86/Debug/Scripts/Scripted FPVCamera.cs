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
    Camera _fpvcam;
    TextPrint _textp;
    Vector2 CameraRotationCoords = new Vector2(0,0);
    float CameraRotationSpeed = 0.001f;
    public void Start()
    {
        _fpvcam = (Camera)_3DRadSpaceDll.Game.GameObjects[1];
        _textp = (TextPrint)_3DRadSpaceDll.Game.GameObjects[3];
    }
    public void Run(MouseState mouse, KeyboardState keyboard, GameTime time)
    {
        Mouse.SetPosition((int)Camera.ScreenSize.X / 2,(int) Camera.ScreenSize.Y / 2);
		//IsMouseVisible = false;
		CameraRotationCoords += new Vector2((mouse.X - (Camera.ScreenSize.X / 2)) * (-CameraRotationSpeed), (mouse.Y - (Camera.ScreenSize.Y / 2)) * CameraRotationSpeed);
		if (CameraRotationCoords.Y > (MathHelper.Pi - 0.1f)) CameraRotationCoords.Y = (MathHelper.Pi - 0.1f);
		if (CameraRotationCoords.Y < 0) CameraRotationCoords.Y = 0.1f;
        _fpvcam.CameraTarget = _fpvcam.Position + Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CameraRotationCoords.X, 0, CameraRotationCoords.Y));
    }
    public void Draw(SpriteBatch batch,Matrix? view, Matrix? projection)
    {
        _textp.Text = _fpvcam.CameraTarget+"";
    }
    public void End()
    {

    }
}