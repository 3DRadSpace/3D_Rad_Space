using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Lib3DRadSpace_DX;
using System.IO;

namespace _3DRadSpace_Player_DX
{
    public class Game1 : Game
    {
        private GraphicsDeviceManager _graphics;
        private SpriteBatch _spriteBatch;

        Matrix matView, matProjection;

        public Game1()
        {
            _graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            IsMouseVisible = true;
            string[] data = File.ReadAllLines(@"Config.cfg"); //read the compiler project stats
            CurrentProject.Open(data[0]);
            //TODO: write resolution settings and stuff.

            //TODO: replace this with executable metadata.
        }

        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            base.Initialize();
        }

        protected override void LoadContent()
        {
            _spriteBatch = new SpriteBatch(GraphicsDevice);

            for(int i = 0; i < CurrentProject.GameObjects.Count; i++)
            {
                CurrentProject.GameObjects[i].Load(Content);
            }

            // TODO: use this.Content to load your game content here
        }

        protected override void Update(GameTime gameTime)
        {
            MouseState mouse = Mouse.GetState();
            KeyboardState keyboard = Keyboard.GetState();
            for(int i = 0; i < CurrentProject.GameObjects.Count; i++)
            {
                CurrentProject.GameObjects[i].Update(ref mouse, ref keyboard, gameTime);
            }

            // TODO: Add your update logic here

            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            BoundingFrustum fr = new BoundingFrustum(matView * matProjection);

            //TO DO: Implement 2D/3D drawing order.
            for(int i = 0; i < CurrentProject.GameObjects.Count; i++)
            {
                CurrentProject.GameObjects[i].Draw(gameTime, fr, ref matView, ref matProjection);
            }
            // TODO: Add your drawing code here

            base.Draw(gameTime);
        }
    }
}
