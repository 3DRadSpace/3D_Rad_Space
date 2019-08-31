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
        public static DiscordRichPresence discordRichPresence;
        Matrix View, Projection;
        public string OpenedFile = null;
        public static bool[] Settings;
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
            Settings = Settings_Load();
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
            if(OpenedFile != null)
            {
                Project.Save(OpenedFile);
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
            KeyboardState keyboard = Keyboard.GetState();
            if(Form.ActiveForm == GameWindow)
            {
                if (GetKeyShortcut(keyboard,Microsoft.Xna.Framework.Input.Keys.N))
                {
                    newProject(null, null);
                }
                if(GetKeyShortcut(keyboard,Microsoft.Xna.Framework.Input.Keys.O))
                {
                    openProject(null, null);
                }
                if(GetKeyShortcut(keyboard,Microsoft.Xna.Framework.Input.Keys.S))
                {
                    saveProject(null, null);
                }
                if(GetAltKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.S))
                {
                    saveProjectAs(null, null);
                }
                if(GetKeyShortcut(keyboard,Microsoft.Xna.Framework.Input.Keys.P))
                {
                    playProject(null, null);
                }
                if(GetKeyShortcut(keyboard,Microsoft.Xna.Framework.Input.Keys.A))
                {
                    addObject(null, null);
                }
            }
            base.Update(gameTime);
        }
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);
            Editor_View.Draw(null,out View, out Projection);
            _3DRadSpaceDll.Game.DrawModel(Axis, Matrix.CreateTranslation(0, 1, 0), View, Projection);
            for(int i =0; i < _3DRadSpaceDll.Game.GameObjects.Count;i++)
            {
                object gameObject = _3DRadSpaceDll.Game.GameObjects[i];
                if(gameObject is Camera c)
                {
                    c.EditorDraw(null,View, Projection);
                }
            }
            base.Draw(gameTime);
        }
        public void ApplyProjectType()
        {
            if(Project.type == ProjectType.ScriptOnly)
            {
                Program.ProjectTypeScript = true;
                Exit();
            }
        }
        private bool[] Settings_Load()
        {
            string appd = Environment.ExpandEnvironmentVariables("%AppData%\\3DRadSpace");
            if (!File.Exists(appd + "\\Config.cfg")) return new[] { true, true, true };
            string[] split = File.ReadAllText(appd + "\\Config.cfg").Split(' ');
            bool[] result = { Convert.ToBoolean(split[0]), Convert.ToBoolean(split[1]), Convert.ToBoolean(split[2]) };
            return result;
        }
        bool GetKeyShortcut(KeyboardState keyboard,Microsoft.Xna.Framework.Input.Keys key)
        {
            if(keyboard.IsKeyDown(key) && (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.LeftControl) || keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.RightControl)))
            {
                return true;
            }
            return false;
        }
        bool GetAltKeyShortcut(KeyboardState keyboard, Microsoft.Xna.Framework.Input.Keys key)
        {
            if (keyboard.IsKeyDown(key) && (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.LeftControl) || keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.RightControl))
            &&    (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.LeftAlt) || keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.RightAlt)))
            {
                return true;
            }
            return false;
        }
    }
}
