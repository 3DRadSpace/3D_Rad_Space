using _3DRadSpaceDll;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Windows.Forms;

namespace _3DRadSpace
{
	public partial class Editor : Microsoft.Xna.Framework.Game
	{
		GraphicsDeviceManager graphics;
		SpriteBatch spriteBatch;
		Form GameWindow;
		Camera Editor_View;
		Model Axis;
		static DiscordRichPresence discordRichPresence;
		Matrix View, Projection;
		public string OpenedFile = null;
		static bool[] Settings;
		float CameraRotationSpeed = 0.001f;

		Vector2 CameraRotationCoords = new Vector2(-2.105f, 2.946f);
		float CameraSpeed = 0.1f;

		//SkyColor specific
		Color ClearColor = Color.Black;

		//Fog specifig
		Vector3 FogColor;
		float FogStart, FogEnd;
		bool FogEnabled = false;

		SpriteFont D_Font;

		public Editor()
		{
			graphics = new GraphicsDeviceManager(this);
			Content.RootDirectory = "Content";
			GameWindow = (Form)Control.FromHandle(Window.Handle);
			InitializeComponent();
			toolStripStatusLabel1.Text = "Status: Ready";
			GameWindow_SizeChanged(GameWindow, null);
			discordRichPresence = new DiscordRichPresence();
			Editor_View = new Camera(null, true, new Vector3(5, 10, 5), new Vector3(0, 0, 0), Vector3.Up, 75, 0.01f, 500f);
			_3DRadSpaceDll.Game.GameObjects = new List<GameObject>();
			Settings = Settings_Load();
		}
		protected override void Initialize()
		{
			Window.AllowUserResizing = true;
			Window.Title = "3DRadSpace - Editor v0.0.3 alpha";
			IsMouseVisible = true;
			if (Settings[0])
			{
				checkforUpdatesEvent(null, null);
			}
			if (OpenedFile != null)
			{
				_3DRadSpaceDll.Game.GameObjects = Project.Open(OpenedFile);
				LoadAllObjects();
				UpdateObjects();
			}
			Editor_View.CameraTarget = Editor_View.Position + Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CameraRotationCoords.X, 0, CameraRotationCoords.Y));
			base.Initialize();
		}
		protected override void LoadContent()
		{
			spriteBatch = new SpriteBatch(GraphicsDevice);
			Camera.model = Content.Load<Model>("Camera");
			Camera.ScreenSize = new Vector2(graphics.PreferredBackBufferWidth, graphics.PreferredBackBufferHeight);
			Axis = Content.Load<Model>("Axis");
			D_Font = Content.Load<SpriteFont>("Font");
		}

		protected override void UnloadContent()
		{

		}

		protected override void Update(GameTime gameTime)
		{
			KeyboardState keyboard = Keyboard.GetState();
			MouseState mouse = Mouse.GetState();
			if (Form.ActiveForm == GameWindow)
			{
				//keyboard shortcuts
				if (GetKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.N)) newProject(null, null);
				if (GetKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.O)) openProject(null, null);
				if (GetKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.S)) saveProject(null, null);
				if (GetAltKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.S)) saveProjectAs(null, null);
				if (GetKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.P)) playProject(null, null);
				if (GetKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.A)) addObject(null, null);

				if (Keyboard.GetState().IsKeyDown(Microsoft.Xna.Framework.Input.Keys.W)) Editor_View.Position +=  Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CameraRotationCoords.X, 0, CameraRotationCoords.Y)) * CameraSpeed;
				if (Keyboard.GetState().IsKeyDown(Microsoft.Xna.Framework.Input.Keys.S)) Editor_View.Position -= Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CameraRotationCoords.X, 0, CameraRotationCoords.Y)) * CameraSpeed;
				if (Keyboard.GetState().IsKeyDown(Microsoft.Xna.Framework.Input.Keys.A)) Editor_View.Position += Vector3.Cross(Editor_View.CameraRotation, Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CameraRotationCoords.X, 0, CameraRotationCoords.Y))) * CameraSpeed;
				if (Keyboard.GetState().IsKeyDown(Microsoft.Xna.Framework.Input.Keys.D)) Editor_View.Position -= Vector3.Cross(Editor_View.CameraRotation, Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CameraRotationCoords.X, 0, CameraRotationCoords.Y))) * CameraSpeed;

				if (mouse.RightButton == Microsoft.Xna.Framework.Input.ButtonState.Pressed)
				{
					if (mouse.X >= 150 && mouse.X <= graphics.PreferredBackBufferWidth &&
					   mouse.Y >= 25 && mouse.Y <= graphics.PreferredBackBufferHeight - 25)
					{
						Mouse.SetPosition(graphics.PreferredBackBufferWidth / 2, graphics.PreferredBackBufferHeight / 2);
						IsMouseVisible = false;
						CameraRotationCoords += new Vector2((mouse.X - (graphics.PreferredBackBufferWidth / 2)) * (-CameraRotationSpeed), (mouse.Y - (graphics.PreferredBackBufferHeight / 2)) * CameraRotationSpeed);
						if (CameraRotationCoords.Y > (MathHelper.Pi - 0.1f)) CameraRotationCoords.Y = (MathHelper.Pi - 0.1f);
						if (CameraRotationCoords.Y < 0) CameraRotationCoords.Y = 0.1f;
					}
				}
				else
				{
					IsMouseVisible = true;
				}
			 }
			Editor_View.CameraTarget = Editor_View.Position + Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CameraRotationCoords.X, 0, CameraRotationCoords.Y));
			base.Update(gameTime);
		}
		protected override void Draw(GameTime gameTime)
		{
			GraphicsDevice.Clear(ClearColor);
			GraphicsDevice.BlendState = BlendState.Opaque;
			GraphicsDevice.DepthStencilState = DepthStencilState.Default;
			GraphicsDevice.SamplerStates[0] = SamplerState.LinearWrap;
			Editor_View.Draw(null, out View, out Projection);

			//Draws the axis: Rotating it 3/2*pi rad because the model is wrong lol
			_3DRadSpaceDll.Game.DrawModel(Axis,Matrix.CreateRotationY(MathHelper.Pi*1.5f)* Matrix.CreateTranslation(0, 0, 0), View, Projection,FogEnabled,FogColor,FogStart,FogEnd);
			
			for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
			{
				object gameObject = _3DRadSpaceDll.Game.GameObjects[i];
				if (gameObject is Camera c) c.EditorDraw(null, View, Projection);
				if (gameObject is SkyColor s) ClearColor = s.Color;
				if(gameObject is Fog f)
				{
					FogEnabled = f.Enabled;
					FogColor = f.FogColor;
					FogStart = f.FogStart;
					FogEnd = f.FogEnd;
				}
				if(gameObject is Skinmesh sk)
				{
					sk.EditorDraw(null, View, Projection);
				}
				if (gameObject is Skybox sb) sb.EditorDraw(Editor_View.Position,View,Projection);
			}
			spriteBatch.Begin();
			spriteBatch.DrawString(D_Font, "CamRot: " + CameraRotationCoords, new Vector2(170, graphics.PreferredBackBufferHeight - 50), Color.White);
			for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
			{
				object gameObject = _3DRadSpaceDll.Game.GameObjects[i];
				if (gameObject is Sprite sp) sp.EditorDraw(spriteBatch, null, null);
				if (gameObject is TextPrint tp) tp.EditorDraw(spriteBatch, null, null);
			}
			spriteBatch.End();
			base.Draw(gameTime);
		}
		private bool[] Settings_Load()
		{
			IFormatProvider a = CultureInfo.CurrentCulture;
			string appd = Environment.ExpandEnvironmentVariables("%AppData%\\3DRadSpace");
			if (!File.Exists(appd + "\\Config.cfg"))
			{
				File.WriteAllText(appd + "\\Config.cfg","1 1 1 1");
				return new[] { true, true, true };
			}
			string[] split = File.ReadAllText(appd + "\\Config.cfg").Split(' ');
			if(split.Length != 5)
			{
				File.WriteAllText(appd + "\\Config.cfg", "1 1 1 1 1");
				return new[] { true, true, true };
			}
			bool[] result = { SafeConverter.BoolFromString(split[0]), SafeConverter.BoolFromString(split[1]), SafeConverter.BoolFromString(split[2]) };
			CameraRotationSpeed = 0.001f * SafeConverter.IntFromString(split[3]);
			CameraSpeed = 0.1f * SafeConverter.IntFromString(split[4]);
			return result;
		}
		bool GetKeyShortcut(KeyboardState keyboard, Microsoft.Xna.Framework.Input.Keys key)
		{
			if (keyboard.IsKeyDown(key) && (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.LeftControl) || keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.RightControl)))
			{
				return true;
			}
			return false;
		}
		bool GetAltKeyShortcut(KeyboardState keyboard, Microsoft.Xna.Framework.Input.Keys key)
		{
			if (keyboard.IsKeyDown(key) && (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.LeftControl) || keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.RightControl))
			&& (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.LeftAlt) || keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.RightAlt)))
			{
				return true;
			}
			return false;
		}
	}
}
