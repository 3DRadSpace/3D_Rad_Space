using _3DRadSpaceDll;
using System;
using System.IO;
using System.Collections.Generic;
using System.Windows.Forms;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Content;

namespace _3DRadSpace
{
    public partial class Editor : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Form GameWindow;
        Camera Editor_View;
        Model Axis;
        DiscordRichPresence discordRichPresence;
        Matrix View, Projection;
        public static ProjectType TypeOfProject = ProjectType.ThreeDimensional;
        public string OpenedFile = null;
        bool[] Settings = Settings_Load();
        public Editor()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            GameWindow = (Form)Control.FromHandle(Window.Handle);
            InitializeComponent();
            toolStripStatusLabel1.Text = "Status: Ready";
            GameWindow_SizeChanged(GameWindow, null);
            discordRichPresence = new DiscordRichPresence();
            Editor_View = new Camera(null,true, new Vector3(5, 10, 5), new Vector3(0,0,0),Vector3.Up, MathHelper.ToRadians(75), 0.01f, 500f);
            _3DRadSpaceDll.Game.GameObjects = new List<object>();
        }
        protected override void Initialize()
        {
            Window.AllowUserResizing = true;
            Window.Title = "3DRadSpace - Editor v0.0.1";
            IsMouseVisible = true;
            if(Settings[0])
            {
                checkforUpdatesEvent(null, null);
            }
            base.Initialize();
        }
        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);
            Camera.model = Content.Load<Model>("Camera");
            Camera.ScreenSize = new Vector2(graphics.PreferredBackBufferWidth, graphics.PreferredBackBufferHeight);
            Axis = Content.Load<Model>("Axis");
        }

        protected override void UnloadContent()
        {
            
        }

        protected override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);
            Editor_View.Draw(null,out View, out Projection);
            _3DRadSpaceDll.Game.DrawModel(Axis, Matrix.CreateTranslation(0, 1, 0), View, Projection);
            base.Draw(gameTime);
        }
        public void ApplyProjectType()
        {
            if(TypeOfProject == ProjectType.ScriptOnly)
            {
                Exit();
            }
        }
        private static bool[] Settings_Load()
        {
            string appd = Environment.ExpandEnvironmentVariables("%AppData%\\3DRadSpace");
            if (!File.Exists(appd + "\\Config.cgf")) return new[] { true, true, true };
            string[] split = File.ReadAllText(appd + "\\Config.cgf").Split(' ');
            bool[] result = { Convert.ToBoolean(split[0]), Convert.ToBoolean(split[1]), Convert.ToBoolean(split[2]) };
            return result;
        }
    }
}
