using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.IO;
using _3DRadSpaceDll;

namespace _3DRadSpace_Player
{
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        string[] Settings;
        Color ClearColor = Color.Black;
        Matrix view, projection;
        public Game1()
        {
            try { Settings = File.ReadAllLines(@"GameConfig.cfg"); }
            catch (FileNotFoundException) { }
            finally
            {
                graphics = new GraphicsDeviceManager(this);
                Window.Title = Settings[0];
                Content.RootDirectory = Settings[1];
            }
            try
            {
                _3DRadSpaceDll.Game.GameObjects = Project.Open(Settings[2]);
            }
            catch(FileNotFoundException)
            {
            }
        }
        protected override void Initialize()
        {
            base.Initialize();
        }
        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);
            for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
            {
                if (_3DRadSpaceDll.Game.GameObjects[i] is Camera c) c.Load(null);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Script script) script.Load(null);
            }
        }
        protected override void UnloadContent()
        {
            for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
            {
                if (_3DRadSpaceDll.Game.GameObjects[i] is Script script) script.End();
            }
        }
        protected override void Update(GameTime gameTime)
        {
            MouseState mouse = Mouse.GetState();
            KeyboardState keyboard = Keyboard.GetState();
            for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
            {
                if (_3DRadSpaceDll.Game.GameObjects[i] is Camera c) c.Update(mouse, keyboard, gameTime);
                if (_3DRadSpaceDll.Game.GameObjects[i] is Script s) s.Update(mouse, keyboard, gameTime);
            }
            base.Update(gameTime);
        }
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(ClearColor);
            for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
            {
                if (_3DRadSpaceDll.Game.GameObjects[i] is Camera c) c.Draw(null,out view,out projection);
                if (_3DRadSpaceDll.Game.GameObjects[i] is SkyColor s) ClearColor = s.Color;
                if (_3DRadSpaceDll.Game.GameObjects[i] is Skinmesh skinmesh) skinmesh.Draw(null, view, projection);
            }
            base.Draw(gameTime);
        }
    }
}
