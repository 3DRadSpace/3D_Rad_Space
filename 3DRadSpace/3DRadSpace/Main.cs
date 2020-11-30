using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.Windows.Forms;
using Lib3DRadSpace_DX;

namespace _3DRadSpace
{
    public partial class Main : Game
    {
        //MG specific vars
        GraphicsDeviceManager _graphics;
        SpriteBatch _spritebatch;

        Camera Camera;
        Matrix MView, MProjection;

        Form MainWindow = null;

        public Main(string file)
        {
            _graphics = new GraphicsDeviceManager(this);
            Camera = new Camera(null, true, Vector3.One * 5, new Vector3(MathHelper.Pi / 2, 0, 0), Vector3.Up, new Vector2(800, 600), MathHelper.ToRadians(65));
            if(file != null)
            {
                //todo: load file
            }
        }

        protected override void Initialize()
        {
            IsMouseVisible = true;
            Window.Title = "3DRadSpace v0.1.0";
            Window.AllowUserResizing = true;
            CurrentProject.GameObjects = new List<BaseGameObject>(300);

            MainWindow = Control.FromHandle(Window.Handle) as Form;
            InitializeComponents();

            base.Initialize();
        }
        protected override void LoadContent()
        {
            _spritebatch = new SpriteBatch(GraphicsDevice);
            base.LoadContent();
        }
        protected override void Update(GameTime gameTime)
        {
            MouseState mouse = Mouse.GetState();
            KeyboardState keyboard = Keyboard.GetState();
            for(int i =0; i < CurrentProject.GameObjects.Count;i++)
            {
                CurrentProject.GameObjects[i].Update(ref mouse, ref keyboard, gameTime);
            }
            base.Update(gameTime);
        }
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Black);
            MView = Camera.View;
            MProjection = Camera.Projection;
            for(int i =0; i < CurrentProject.GameObjects.Count;i++)
            {
                CurrentProject.GameObjects[i].EditorDraw(gameTime, Camera.CameraFrustum, ref MView, ref MProjection);
            }
            base.Draw(gameTime);
        }
        protected override void UnloadContent()
        {
            base.UnloadContent();
        }
    }
}
