using System;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.Windows.Forms;

using MessageBox = System.Windows.Forms.MessageBox;
using ButtonState = Microsoft.Xna.Framework.Input.ButtonState;

namespace _3DRadSpace
{
	class SkinmeshPreviewer : Game
	{
		GraphicsDeviceManager _graphics;

		string Model = null;
		string ContentRoot = "";
		Model LoadedModel = null;

		Matrix view = Matrix.CreateLookAt(Vector3.UnitZ * 2, Vector3.Zero, Vector3.Up);
		Matrix projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(65), 800f / 600f, 0.01f, 500f);

		Vector3 CameraDirection = Vector3.UnitZ;
		Vector2 CamScreenCoords;
		float Zoom;
		float ModelSize = 0;

		public bool Running;

		public SkinmeshPreviewer(string model,string contentroot)
		{
			ContentRoot = contentroot;
			Model = model;
			Running = true;
			_graphics = new GraphicsDeviceManager(this);
		}
		protected override void Initialize()
		{
			Window.Title = "3DRadSpace - Skinmesh previewer";
			Window.AllowUserResizing = true;
			IsMouseVisible = true;
			_graphics.PreferredBackBufferWidth = 800;
			_graphics.PreferredBackBufferHeight = 600;
			_graphics.ApplyChanges();
			base.Initialize();
		}
		protected override void LoadContent()
		{
			Content.RootDirectory = ContentRoot;
			try
			{
				LoadedModel = Content.Load<Model>(Model);
			}
			catch(ContentLoadException e)
			{
				DialogResult r = MessageBox.Show("Cannot load file " + Model + ". Exception details: \r\n" + e.Message, "Loading error", MessageBoxButtons.RetryCancel, MessageBoxIcon.Error); ;
				if(r == DialogResult.Retry)
					LoadContent();
				else Exit();
			}
			float mxdst = 0;
			for(int i =0; i < LoadedModel.Meshes.Count;i++)
			{
				float r = LoadedModel.Meshes[i].BoundingSphere.Radius;
				if(mxdst < r) mxdst = r;
			}
			ModelSize = mxdst + 2f;
		}
		protected override void Draw(GameTime gameTime)
		{
			GraphicsDevice.Clear(Color.Gray);
			LoadedModel.Draw(Matrix.Identity, view, projection);
			base.Draw(gameTime);
		}
		protected override void Update(GameTime gameTime)
		{
			float dt = (float)gameTime.ElapsedGameTime.TotalSeconds;
			MouseState mouse = Mouse.GetState();

			if(mouse.RightButton == ButtonState.Pressed)
			{
				int wx = Window.ClientBounds.Width/2;
				int wy = Window.ClientBounds.Height/2;
				Mouse.SetPosition(wx, wy);
				float dx = mouse.X - (wx);
				float dy = mouse.Y - (wy);
				CamScreenCoords += new Vector2(dx * dt * dt, dy * dt * dt);

				float diry = MathHelper.Clamp(CamScreenCoords.Y, -MathHelper.PiOver2 + 0.0001f, MathHelper.PiOver2 - 0.0001f);
				CameraDirection = Vector3.Transform(Vector3.UnitZ, Quaternion.CreateFromYawPitchRoll(CamScreenCoords.X, 0, 0) * Quaternion.CreateFromYawPitchRoll( 0, diry, 0));
			}

			Zoom = (mouse.ScrollWheelValue * -0.01f) + 3 + ModelSize;

			view = Matrix.CreateLookAt(CameraDirection * Zoom, Vector3.Zero, Vector3.Up);
		}
        protected override void EndRun()
        {
			Running = false;
			base.EndRun();
        }
    }
}
