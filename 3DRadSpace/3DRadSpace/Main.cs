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

using ButtonState = Microsoft.Xna.Framework.Input.ButtonState;

namespace _3DRadSpace
{
    public partial class Main : Game
    {
        //MG specific vars
        GraphicsDeviceManager _graphics;
        SpriteBatch _spritebatch;

        Camera Camera;
        float Zoom = 5;
        Vector2 camera_rotation;
        Vector3 _cursor = Vector3.Zero;
        Matrix MView, MProjection;

        Form MainWindow = null;
        string LoadedFIle = null;
        bool Saved = true;

        public Main(string file)
        {
            LoadedFIle = file;
            _graphics = new GraphicsDeviceManager(this);
            Camera = new Camera(null, true, Vector3.One * 5, Vector3.Zero, Vector3.Up, MathHelper.ToRadians(65));
            Camera.LookAtLocation = true;
            if (file != null)
            {
                //todo: load file
            }
        }
        BasicEffect basic_shader;

        protected override void Initialize()
        {
            IsMouseVisible = true;
            Window.Title = "3DRadSpace v0.1.0 alpha";
            Window.AllowUserResizing = true;

            MainWindow = Control.FromHandle(Window.Handle) as Form;
            InitializeComponents();
            basic_shader = new BasicEffect(GraphicsDevice);

            CurrentProject.Resolution = new Vector2(_graphics.PreferredBackBufferWidth, _graphics.PreferredBackBufferHeight);

            base.Initialize();
        }
        protected override void LoadContent()
        {
            _spritebatch = new SpriteBatch(GraphicsDevice);
            InitializeAxis();

            Content.RootDirectory = "EngineData";
            Camera.CameraModel = Content.Load<Model>("Editor\\Models\\Camera\\Camera");

            base.LoadContent();
        }

        ButtonState _lrb = ButtonState.Released;
        bool _3dviewfocus = true;

        bool _3DMode = true;

        protected override void Update(GameTime gameTime)
        {
            float dt = (float)gameTime.ElapsedGameTime.TotalSeconds;

            MouseState mouse = Mouse.GetState();
            KeyboardState keyboard = Keyboard.GetState();

            if(_3DMode)
            {
                if(Form.ActiveForm == MainWindow && _3dviewfocus && mouse.X >= 150 && mouse.Y >= 50)
                {
                    Zoom = (mouse.ScrollWheelValue * 0.01f) + 5;
                    if(mouse.LeftButton == ButtonState.Pressed)
                    {
                        Mouse.SetPosition(_graphics.PreferredBackBufferWidth / 2, _graphics.PreferredBackBufferHeight / 2);
                        float dx = mouse.X - (_graphics.PreferredBackBufferWidth / 2);
                        float dy = mouse.Y - (_graphics.PreferredBackBufferHeight / 2);

                        camera_rotation += new Vector2(dx * dt * dt, -dy * dt * dt);

                        IsMouseVisible = false;
                    }
                    else IsMouseVisible = true;

                    if(mouse.RightButton == ButtonState.Pressed && _lrb != mouse.RightButton)
                    {
                        
                    }
                    _lrb = mouse.RightButton;
                }
                Camera.Target = _cursor;

                float yangle = MathHelper.Clamp(camera_rotation.Y, -MathHelper.PiOver2 + 0.0001f, MathHelper.PiOver2 - 0.0001f);

                Camera.Position = Vector3.Transform(Vector3.UnitZ, Quaternion.CreateFromYawPitchRoll(camera_rotation.X, 0, 0) * Quaternion.CreateFromYawPitchRoll(0, yangle, 0));

                Camera.Position *= Zoom;
            }
            else
            {

            }
            base.Update(gameTime);
        }
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Black);

            GraphicsDevice.BlendFactor = new Color(255, 255, 255, 255);
            GraphicsDevice.BlendState = BlendState.Opaque;
            GraphicsDevice.DepthStencilState = DepthStencilState.Default;
            GraphicsDevice.RasterizerState = RasterizerState.CullCounterClockwise;
            for(int i =0; i < 16;i++)
            {
                GraphicsDevice.SamplerStates[i] = SamplerState.LinearWrap;
            }
            if(_3DMode)
            {
                DrawAxis();
                Camera.Draw(gameTime, null, ref MView, ref MProjection);

                int s = CurrentProject.GameObjects.Count;
                for(int i = 0; i < s; i++)
                {
                    CurrentProject.GameObjects[i].EditorDraw(gameTime, Camera.CameraFrustum, ref MView, ref MProjection);
                }
            }
            else
            {
                int l = CurrentProject.GameObjects.Count;
                for(int i = 0; i < l; i++)
                {
                    CurrentProject.GameObjects[i].Draw2D(gameTime,_spritebatch);
                }
            }
            base.Draw(gameTime);
        }
        protected override void UnloadContent()
        {
            base.UnloadContent();
        }
        VertexBuffer AxisModel;
        void InitializeAxis()
        {
            VertexPositionColor[] axis = new VertexPositionColor[12];
            axis[0] = new VertexPositionColor(Vector3.Zero, Color.Red);
            axis[1] = new VertexPositionColor(Vector3.UnitX * Camera.FarPlaneDistance, Color.Red);
            axis[2] = new VertexPositionColor(Vector3.Zero, Color.Green);
            axis[3] = new VertexPositionColor(Vector3.UnitY * Camera.FarPlaneDistance, Color.Green);
            axis[4] = new VertexPositionColor(Vector3.Zero, Color.Blue);
            axis[5] = new VertexPositionColor(Vector3.UnitZ * Camera.FarPlaneDistance, Color.Blue);
            axis[6] = new VertexPositionColor(Vector3.Zero, Color.White);
            axis[7] = new VertexPositionColor(-Vector3.UnitX * Camera.FarPlaneDistance, Color.White);
            axis[8] = new VertexPositionColor(Vector3.Zero, Color.White);
            axis[9] = new VertexPositionColor(-Vector3.UnitY * Camera.FarPlaneDistance, Color.White);
            axis[10] = new VertexPositionColor(Vector3.Zero, Color.White);
            axis[11] = new VertexPositionColor(-Vector3.UnitZ * Camera.FarPlaneDistance, Color.White);
            AxisModel = new VertexBuffer(GraphicsDevice, typeof(VertexPositionColor), 12, BufferUsage.None);
            AxisModel.SetData(axis);
        }
        void DrawAxis()
        {
            foreach (EffectPass pass in basic_shader.CurrentTechnique.Passes)
            {
                basic_shader.View = MView;
                basic_shader.Projection = MProjection;
                basic_shader.World = Matrix.Identity;
                basic_shader.VertexColorEnabled = true;
                pass.Apply();
                GraphicsDevice.SetVertexBuffer(AxisModel);
                GraphicsDevice.DrawPrimitives(PrimitiveType.LineList, 0, 6);
            }
        }
    }
}
