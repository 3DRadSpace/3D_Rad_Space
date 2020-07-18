using _3DRadSpaceDll;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Runtime.InteropServices;
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

		//Possible skybox fix
		//SamplerState ss = new SamplerState() { AddressU = TextureAddressMode.Wrap, AddressV = TextureAddressMode.Wrap};
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
			Window.Title = "3DRadSpace - Editor v0.0.6 alpha";
			GameWindow.WindowState = FormWindowState.Maximized;
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
			Camera.model = Content.Load<Model>("Camera/camera");
			Camera.ScreenSize = new Vector2(graphics.PreferredBackBufferWidth, graphics.PreferredBackBufferHeight);
			Axis = Content.Load<Model>("Axis");
			D_Font = Content.Load<SpriteFont>("Font");
			EventOnLocation.LoadModels(Content);
			SoundSource.ModelMarker = Content.Load<Model>("SoundEffect_Model");
		}

		protected override void UnloadContent()
		{

		}
		Vector3 _3dcursor_loc = Vector3.Zero;
		int selected_object_index = -1;

		protected override void Update(GameTime gameTime)
		{
			if (Form.ActiveForm == GameWindow)
			{
				KeyboardState keyboard = Keyboard.GetState();
				MouseState mouse = Mouse.GetState();
				//keyboard shortcuts
				if (GetKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.N)) newProject(null, null);
				if (GetKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.O)) openProject(null, null);
				if (GetKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.S)) saveProject(null, null);
				if (GetAltKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.S)) saveProjectAs(null, null);
				if (GetKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.P)) playProject(null, null);
				if (GetKeyShortcut(keyboard, Microsoft.Xna.Framework.Input.Keys.A)) addObject(null, null);

				//camera movement

				if (mouse.LeftButton == Microsoft.Xna.Framework.Input.ButtonState.Pressed)
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
				Vector3 UnitV = Vector3.Transform(Vector3.UnitZ + Vector3.Up, Matrix.CreateFromYawPitchRoll(CameraRotationCoords.X, 0, CameraRotationCoords.Y));
				Editor_View.Position = _3dcursor_loc + (UnitV * ( mouse.ScrollWheelValue) * 0.01f);
				Editor_View.CameraTarget = _3dcursor_loc;
				//
				//
				//editing an object by double clicking in the editor
				// pls fix
				// I'm waiting for miracles to happen.
				//
				
				if(mouse.RightButton == Microsoft.Xna.Framework.Input.ButtonState.Pressed)
				{
					float d = float.MaxValue;
					Ray finder = GetMouseRay(new Vector2(mouse.X, mouse.Y), GraphicsDevice.Viewport, View, Projection);
					for(int i =0; i < _3DRadSpaceDll.Game.GameObjects.Count;i++)
					{
						GameObject o = _3DRadSpaceDll.Game.GameObjects[i];
						if(o is Skinmesh sk)
						{
							if (RayI(finder, sk.Model.Meshes[0].BoundingSphere, i,out float ?cdst))
							{
								Vector3? val = RayMeshCollision(finder, sk.Model, sk.TranslationMatrix);
								if (val == null) continue;
								if (_3dcursor_loc != null)
								{
									if (d > cdst)
									{
										d = (float)cdst;
										_3dcursor_loc = val.Value;
									}
								}
							}
						}
						if(o is Camera c)
						{
							if(RayI(finder, new BoundingSphere(c.Position, 2), i,out float? cdst))
							{
								if (d > cdst)
								{
									d = (float)cdst;
									_3dcursor_loc = c.Position;
								}
							}
						}
						if(o is EventOnLocation eol)
						{
							switch(eol.BoundingType)
							{
								case BoundingObject.Box:
									if(RayI(finder,eol.BoundingBox,i,out float? cdst))
									{
										if (d > cdst)
										{
											d = (float)cdst;
											_3dcursor_loc = eol.Position;
										}
									}
									break;
								case BoundingObject.Sphere:
									if (RayI(finder, eol.BoundingSphere, i, out float? cdsts))
									{
										if (d > cdsts)
										{
											d = (float)cdsts;
											_3dcursor_loc = eol.Position;
										}
									}
									break;
								default:break;
							}
						}
					}
				}
			}
			base.Update(gameTime);
		}
		protected override void Draw(GameTime gameTime)
		{
			GraphicsDevice.Clear(ClearColor);
			GraphicsDevice.BlendState = BlendState.AlphaBlend;
			GraphicsDevice.DepthStencilState = DepthStencilState.Default;
			GraphicsDevice.SamplerStates[0] = SamplerState.AnisotropicWrap;
			Editor_View.Draw( out View, out Projection);

			//Draws the axis: Rotating it 3/2*pi rad because the model is wrong lol
			_3DRadSpaceDll.Game.DrawModel(Axis,Matrix.CreateRotationY(MathHelper.Pi*1.5f)* Matrix.CreateTranslation(_3dcursor_loc), View, Projection,FogEnabled,FogColor,FogStart,FogEnd);
			
			for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
			{
				object gameObject = _3DRadSpaceDll.Game.GameObjects[i];
				if (gameObject is FPVCamera fc) fc.EditorDraw(null, View, Projection);
				else if (gameObject is Camera c) c.EditorDraw(null, View, Projection);
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
					if (FogEnabled)
					{
						sk.FogExists = FogEnabled;
						sk.FogColor = FogColor;
						sk.FogEnd = FogEnd;
						sk.FogStart = FogStart;
					}
					else
					{
						sk.FogExists = false;
						sk.FogEnabled = false;
					}
					sk.EditorDraw(null, View, Projection);
				}
				if (gameObject is Skybox sb)
				{
					GraphicsDevice.SamplerStates[0] = SamplerState.PointWrap;
					sb.EditorDraw(Editor_View.Position, View, Projection);
					GraphicsDevice.SamplerStates[0] = SamplerState.AnisotropicWrap;
				}
				if (gameObject is EventOnLocation eol) eol.EditorDraw(spriteBatch, View, Projection);
				if (gameObject is SoundSource ss) ss.EditorDraw(spriteBatch, View, Projection);
			}
			spriteBatch.Begin();
			spriteBatch.DrawString(D_Font, "CamRot: " + CameraRotationCoords+ " CamPos "+Editor_View.Position, new Vector2(170, graphics.PreferredBackBufferHeight - 50), Color.White);
			for (int i = 0; i < _3DRadSpaceDll.Game.GameObjects.Count; i++)
			{
				object gameObject = _3DRadSpaceDll.Game.GameObjects[i];
				if (gameObject is Sprite sp) sp.EditorDraw(spriteBatch, null, null);
				if (gameObject is TextPrint tp) tp.EditorDraw(spriteBatch, null, null);
			}
			spriteBatch.End();
			base.Draw(gameTime);
		}
		// maybe will find use in the future.
		//bool _first_use; <- currently disabled.
		private bool[] Settings_Load()
		{
			if(!Directory.Exists(Environment.ExpandEnvironmentVariables("%appdata%\\3DRadSpace")))
			{
				//_first_use = true;
				Directory.CreateDirectory(Environment.ExpandEnvironmentVariables("%appdata%\\3DRadSpace"));
			}
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
			bool[] result = { Convert.ToBoolean(split[0]), Convert.ToBoolean(split[1]), Convert.ToBoolean(split[2]) };
			CameraRotationSpeed = 0.001f * Convert.ToInt32(split[3],Main.CultureInfo);
			CameraSpeed = 0.1f * Convert.ToInt32(split[4],Main.CultureInfo);
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
		public static Ray GetMouseRay(Vector2 mousePosition, Viewport viewport, Matrix view, Matrix projection)
		{
			Vector3 nearPoint = new Vector3(mousePosition, 0);
			Vector3 farPoint = new Vector3(mousePosition, 1);
			nearPoint = viewport.Unproject(nearPoint, projection, view, Matrix.Identity);
			farPoint = viewport.Unproject(farPoint, projection, view, Matrix.Identity);
			Vector3 direction = farPoint - nearPoint;
			direction.Normalize();
			return new Ray(nearPoint, direction);
		}
		public bool RayI(Ray finder,BoundingBox obj, int i,out float? dist)
		{
			dist = finder.Intersects(obj);
			if (dist != null)
			{
				selected_object_index = i;
				_3dcursor_loc = GetBoxCenter(obj);
				return true;
			}
			else return false;
		}
		public bool RayI(Ray finder, BoundingSphere obj, int i,out float? dist)
		{
			dist = finder.Intersects(obj);
			if (dist != null)
			{
				selected_object_index = i;
				_3dcursor_loc = obj.Center;
				return true;
			}
			else return false;
		}
		public static Vector3 GetBoxCenter(BoundingBox box)
		{
			float x = MathHelper.Lerp(box.Min.X, box.Max.X, 0.5f);
			float y = MathHelper.Lerp(box.Min.Y, box.Max.Y, 0.5f);
			float z = MathHelper.Lerp(box.Min.Z, box.Max.Z, 0.5f);
			return new Vector3(x, y, z);
		}
		public static Vector3? RayMeshCollision(Ray r,Model m,Matrix translation)
		{
			for (int i =0; i < m.Meshes.Count;i++)
			{
				for(int j =0; j < m.Meshes[i].MeshParts.Count;j++)
				{
					VertexPosition[] tri_r = new VertexPosition[m.Meshes[i].MeshParts[j].VertexBuffer.VertexCount];
					m.Meshes[i].MeshParts[j].VertexBuffer.GetData(tri_r);
					
					for (int k = m.Meshes[i].MeshParts[j].VertexOffset;
						k < m.Meshes[i].MeshParts[j].VertexBuffer.VertexCount - 3;
						k += 3)
					{
						Triangle tri = new Triangle(tri_r[k].Position, tri_r[k + 1].Position, tri_r[k + 2].Position);
						if (MollerTrumboreIntersection(r, tri, out Vector3? intersection)) return intersection;
					}
				}
			}
			return null;
		}
		/// <summary>
		///  *insert prayer for this to work*
		/// </summary>
		/// <param name="r"></param>
		/// <param name="tri"></param>
		/// <param name="intersectionP"></param>
		/// <returns></returns>
		public static bool MollerTrumboreIntersection(Ray r,Triangle tri,out Vector3? intersectionP)
		{
			//Source : https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
			const float EPSILON = 0.0000001f;
			Vector3 vertex0 = tri.vertex0;
			Vector3 vertex1 = tri.vertex1;
			Vector3 vertex2 = tri.vertex2;
			Vector3 edge1, edge2, h, s, q;
			float a, f, u, v;
			edge1 = vertex1 - vertex0;
			edge2 = vertex2 - vertex0;
			h = Vector3.Cross(r.Direction,edge2); 
			a = Vector3.Dot(edge1,h);
			if (a > -EPSILON && a < EPSILON)
			{
				intersectionP = null;
				return false;    // This ray is parallel to this triangle.
			}
			f = 1.0f / a;
			s = r.Position - vertex0;
			u = f * Vector3.Dot(s,h);
			if (u < 0.0 || u > 1.0)
			{
				intersectionP = null;
				return false;
			}
			q = Vector3.Cross(s, edge1);
			v = f * Vector3.Dot( r.Direction,q);
			if (v < 0.0 || u + v > 1.0)
			{
				intersectionP = null;
				return false;
			}
			// At this stage we can compute t to find out where the intersection point is on the line.
			float t = f * Vector3.Dot(edge2, q);
			if (t > EPSILON) // ray intersection
			{
				intersectionP = r.Position + r.Direction * t;
				return true;
			}
			else // This means that there is a line intersection but not a ray intersection.
			{
				intersectionP = null;
				return false;
			}
		}
	}
	public struct Triangle
	{
		public Vector3 vertex0;
		public Vector3 vertex1;
		public Vector3 vertex2;
		public Triangle(Vector3 a,Vector3 b,Vector3 c)
		{
			vertex0 = a;
			vertex1 = b;
			vertex2 = c;
		}
	}
}
