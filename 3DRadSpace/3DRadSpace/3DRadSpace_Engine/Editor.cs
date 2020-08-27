using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _3DRadSpaceDll;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using System.Windows.Forms;
using System.Threading;

namespace _3DRadSpace_Engine
{
    /// <summary>
    /// This part is doing the main drawing and updating logic. See `EditorWindow.cs` to see the WinForms verion.
    /// </summary>
    partial class Editor : Game
    {
        GraphicsDeviceManager _graphics;
        SpriteBatch _batch; 
        Form EditorWindow;
        DiscordRichPresence discord;
        Camera _editorCamera;
        public Editor()
        {
            _graphics = new GraphicsDeviceManager(this);
            IsMouseVisible = true;
            _editorCamera = new Camera();
            _editorCamera.RecalculateMatrices();
        }
        protected override void Initialize()
        {
            Window.Title = "3DRadSpace v0.1.0a";
            Window.AllowUserResizing = true;
            
            EditorWindow = (Form)Control.FromHandle(Window.Handle);
            InitializeComponent();
            EditorWindow.Location = new System.Drawing.Point(0, 0);
            EditorWindow.WindowState = FormWindowState.Maximized;
            discord = new DiscordRichPresence();
            base.Initialize();
        }
        protected override void LoadContent()
        {
            _batch = new SpriteBatch(GraphicsDevice);
            Content.RootDirectory = "Resources";
            base.LoadContent();
        }
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Black);
            GraphicsDevice.BlendState = BlendState.AlphaBlend;
            GraphicsDevice.DepthStencilState = DepthStencilState.Default;
            GraphicsDevice.SamplerStates[0] = SamplerState.AnisotropicWrap;
            _batch.Begin();
            _batch.End();
            base.Draw(gameTime);
        }
        protected override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }
        protected override void UnloadContent()
        {
            discord.Dispose();
            base.UnloadContent();
        }
    }
}
