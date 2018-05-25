using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Content;
using System.Windows.Forms;
using System.Net;
using System.IO;
using System.Diagnostics;
using System;
using _3DRadSpaceDll;

namespace _3DRadSpace
{
    public class Game1 : Game
    {
        static Vector3 CameraPos = new Vector3(10, 1, 3);
        Matrix world = Matrix.CreateTranslation(new Vector3(0, 0, 0));
        Matrix view = Matrix.CreateLookAt(CameraPos, new Vector3(0, 0, 0), Vector3.UnitY);
        Matrix projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45), 800f / 480f, 0.1f, 500f); //Last parameter is maximum view distance
        GraphicsDeviceManager graphics;
        Texture2D GUI1;
        SpriteBatch spriteBatch;
        Model Axis;
        SpriteFont Font;
        Model[] GameObjects = new Model[_3DRadSpaceGame.MAX_OBJECTS];
        public string[] ObjectsData = new string[_3DRadSpaceGame.MAX_OBJECTS];
        //Texture2D CurrentEdit; //ignore the warning, will be used later.
        Color skycolor = new Color(100, 100, 255);
        bool IsProjectSaved = true;
        static public bool Focus = true;
        public static NotifyIcon notifyIcon = new NotifyIcon()
        {
            Icon = System.Drawing.Icon.ExtractAssociatedIcon("Icon.ico"),
            Visible = true,
            Text = "3DRadSpace",
            Tag = "3DRadSpace",
        };
        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }
        protected override void Initialize()
        {
            UpdateV(false);
            // TODO: Add your initialization logic here
            base.IsMouseVisible = true;
            base.Window.Position = new Point(0, 0);
            graphics.PreferredBackBufferHeight = Screen.PrimaryScreen.Bounds.Height - 75;
            graphics.PreferredBackBufferWidth = Screen.PrimaryScreen.Bounds.Width - 16;
            graphics.ApplyChanges();
            Window.Title = "3DRadSpace v1.0 Pre-Alpha release -Editor-";
            notifyIcon.BalloonTipClicked += NotifyIcon_BalloonTipClicked;
            base.Initialize();
            Form GameForm = Form.FromHandle(Window.Handle) as Form;
            GameForm.FormClosing += OnGameEditorClosing;
        }
        private void OnGameEditorClosing(object sender, System.EventArgs e)
        {
            string[] data = File.ReadAllLines(@"settings.data");
            if (data[1] == "True")
            {
                if (IsProjectSaved == false)
                {
                    DialogResult warn1 = MessageBox.Show("Project is not saved. Save the project?", "Warning", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
                    if (warn1 == DialogResult.Yes)
                    {
                        SaveFileDialog saveFile = new SaveFileDialog()
                        {
                            Filter = "3DRadSpace Project | *.3drsp | Text File | *.txt",
                            InitialDirectory = @"/Projects/",
                            Title = "Save a 3DRadSpace project...",
                            OverwritePrompt = true
                        };
                        saveFile.ShowDialog();
                        File.WriteAllLines(saveFile.FileName, ObjectsData);
                    }
                }
            }
        }
        private void NotifyIcon_BalloonTipClicked(object sender, System.EventArgs e)
        {
           ///Things to do later here.
        }
        protected override void LoadContent()
        {
           spriteBatch = new SpriteBatch(GraphicsDevice);
            Axis = Content.Load<Model>("Axis");
            GUI1 = Content.Load<Texture2D>("Button");
            Font = Content.Load<SpriteFont>("Font");
         }
        protected override void UnloadContent()
        {
        }
        protected override void Update(GameTime gameTime)
        {

            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == Microsoft.Xna.Framework.Input.ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Microsoft.Xna.Framework.Input.Keys.Escape))
                Exit();
            KeyboardState keyboard = Keyboard.GetState();
            MouseState mouse = Mouse.GetState();
            if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.Up)) CameraPos.X += 1;
            if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.Down)) CameraPos.X -= 1;
            if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.Left)) CameraPos.Z -= 1;
            if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.Right)) CameraPos.Z += 1;
            if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.E)) CameraPos.Y += 1;
            if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.Q)) CameraPos.Y -= 1;
            if (_3DRadSpace_EditorClass.DotInSquare(new Vector2(mouse.X, mouse.Y), new Vector2(3, 2), new Vector2(30, 18)))
            {
                if (mouse.LeftButton == Microsoft.Xna.Framework.Input.ButtonState.Pressed)
                {
                    if (Focus == true)
                    {
                        Focus = false;
                        FileMenuStrip strip1 = new FileMenuStrip();
                        strip1.ShowDialog();
                        if (strip1.StripResult != null)
                        {
                            if (strip1.StripResult.Split(' ')[0] == "1")
                            {
                                ResetObjects();
                                skycolor = new Color(100, 100, 255);
                            }
                            if (strip1.StripResult.Split(' ')[0] == "2")
                            {
                                ResetObjects();
                                skycolor = new Color(100, 100, 255);
                                string path = "";
                                for (int i = 1; i < strip1.StripResult.Split(' ').Length; i++)
                                {
                                    path += strip1.StripResult.Split(' ')[i] + " ";
                                }
                                if (string.IsNullOrWhiteSpace(path) != true)
                                {
                                    string[] file = File.ReadAllLines(path);
                                    for (int i = 0;i < file.Length; i++)
                                    {
                                        if (string.IsNullOrWhiteSpace(file[i]) != true)
                                        {
                                            ObjectsData[i] = file[i];
                                        }
                                    }
                                }
                            }
                            if (strip1.StripResult.Split(' ')[0] == "3")
                            {
                                string path = ""; 
                                for (int i = 1; i < strip1.StripResult.Split(' ').Length; i++)
                                {
                                    path += strip1.StripResult.Split(' ')[i] + " ";
                                }
                                if(string.IsNullOrWhiteSpace(path) != true)
                                {
                                    File.WriteAllLines(path, ObjectsData);
                                }
                            }
                        }
                        strip1.StripResult = null;
                    }
                }
            }
            if (_3DRadSpace_EditorClass.DotInSquare(new Vector2(mouse.X, mouse.Y), new Vector2(40, 2), new Vector2(80, 18)))
            {
                if (mouse.LeftButton == Microsoft.Xna.Framework.Input.ButtonState.Pressed)
                {
                    if (Focus == true)
                    {
                        Focus = false;
                        EditMenuStrip strip2 = new EditMenuStrip();
                        strip2.ShowDialog();
                        string obj = File.ReadAllText(@"lastobj.data");
                        if (obj.Split(' ')[0] != null)
                        {
                            for (int i = 0; i < 300; i++)
                            {
                                if(ObjectsData[i] == null)
                                {
                                    ObjectsData[i] = obj;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (_3DRadSpace_EditorClass.DotInSquare(new Vector2(mouse.X, mouse.Y), new Vector2(90, 2), new Vector2(140, 18)))
            {
                if (mouse.LeftButton == Microsoft.Xna.Framework.Input.ButtonState.Pressed)
                {
                    if (Focus == true)
                    {
                        Focus = false;
                        OptionsMenuStrip strip3 = new OptionsMenuStrip();
                        strip3.ShowDialog();
                    }
                }
            }
            if (_3DRadSpace_EditorClass.DotInSquare(new Vector2(mouse.X, mouse.Y), new Vector2(150, 2), new Vector2(170, 18)))
            {
                if (mouse.LeftButton == Microsoft.Xna.Framework.Input.ButtonState.Pressed)
                {
                    if (Focus == true)
                    {
                        Focus = false;
                        HelpMenuStrip strip4 = new HelpMenuStrip();
                        strip4.ShowDialog();
                    }
                }
            }
            
            base.Update(gameTime);
        }
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(skycolor);
            DrawModel(Axis, world,view, projection);
            view = Matrix.CreateLookAt(CameraPos, new Vector3(0, 0, 0), Vector3.UnitY);
            for(int i=0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
                if (ObjectsData[i] != null)
                    CreateObject(ObjectsData[i].Split(' '));
            }
            spriteBatch.Begin(); //rlly
            spriteBatch.Draw(GUI1, new Rectangle(0, 0, Screen.PrimaryScreen.Bounds.Width, 25),Color.White);
            spriteBatch.DrawString(Font, "File",new Vector2(3, 2), Color.White);
            spriteBatch.DrawString(Font, "Edit", new Vector2(40, 2), Color.White);
            spriteBatch.DrawString(Font, "Options", new Vector2(80, 2), Color.White);
            spriteBatch.DrawString(Font, "Help", new Vector2(145, 2), Color.White);
            spriteBatch.End();
            spriteBatch.GraphicsDevice.RasterizerState = RasterizerState.CullCounterClockwise;
            spriteBatch.GraphicsDevice.BlendState = BlendState.Opaque;
            spriteBatch.GraphicsDevice.DepthStencilState = DepthStencilState.Default;
            base.Draw(gameTime);
        }
        /// <summary>
        /// Finds a update for 3DRadSpace
        /// </summary>
        public static void UpdateV(bool forced)
        {
            string[]Setting = { "True", "True" };
            try
            {
                Setting = File.ReadAllLines(@"settings.data");
            }
            catch (FileNotFoundException)
            {
                File.WriteAllLines(@"settings.data",Setting);
            }
            if (Setting[0] == "True" || forced == true)
            {
                WebClient vchecker = new WebClient();
                vchecker.DownloadFile("https://drive.google.com/uc?export=download&id=0B9yRO5eZEvTjeHhPa05OZDRxUmM", @"update.data");
                string Update = File.ReadAllText(@"update.data");
                string[] LastVersion = Update.Split(' ');
                if (LastVersion[0] != "1" || LastVersion[1] != "0" || LastVersion[2] != "0")
                {
                    DialogResult UpdateQ = MessageBox.Show("A update is avalable for 3DRadSpace. Version" + LastVersion[0] + " " + LastVersion[1] + " " + LastVersion[2] + " \r\n Do you want to download it?", "Information", MessageBoxButtons.YesNo, MessageBoxIcon.Information);
                    if (UpdateQ == DialogResult.Yes)
                    {
                        vchecker.DownloadFile("https://drive.google.com/uc?export=download&id=0B9yRO5eZEvTjSVhCZndjSGRUcVE", @"3DRadSpace_Installer.exe");
                        Process.Start(@"3DRadSpace_Installer.exe");
                        MessageBox.Show("To apply the update, manually restart the application.", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    else
                    {
                        MessageBox.Show("You can update 3DRadSpace from the official website", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
                else
                {
                    MessageBox.Show("No new updates", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
        }
        /// <summary>
        /// Draws a model.
        /// </summary>
        /// <param name="model">Model that will be drawn</param>
        /// <param name="world">Position & Rotation Matrix</param>
        /// <param name="view">Camera matrix.</param>
        /// <param name="projection">Other camera matrix.</param>
        void DrawModel(Model model, Matrix world, Matrix view, Matrix projection)
        {
            foreach (ModelMesh mesh in model.Meshes)
            {
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.World = world;
                    effect.View = view;
                    effect.Projection = projection;
                }
                mesh.Draw();
            }
        }
        /// <summary>
        /// Creates an object that has been loaded to the editor.
        /// </summary>
        /// <param name="ObjectData"></param>
       public void CreateObject(string[] ObjectData)
        {
            for (int i = 0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
                if (ObjectsData[i] == null)
                {
                    if (ObjectData[0] == "Camera")
                    {
                        Matrix objpos = Matrix.CreateTranslation(new Vector3(Convert.ToSingle(ObjectData[3]), Convert.ToSingle(ObjectData[4]), Convert.ToSingle(ObjectData[5])));
                        Matrix rotation = Matrix.CreateFromYawPitchRoll(Deg2Rad(Convert.ToSingle(ObjectData[6])), Deg2Rad(Convert.ToSingle(ObjectData[7])), Deg2Rad(Convert.ToSingle(ObjectData[8])));
                        objpos *= rotation;
                        GameObjects[i] = Content.Load<Model>("Camera");
                        DrawModel(GameObjects[i], objpos, view, projection);
                        break;
                    }
                    if(ObjectData[0] == "SkyColor")
                    {
                        skycolor.R = Convert.ToByte(Convert.ToInt16(ObjectData[3]));
                        skycolor.G = Convert.ToByte(Convert.ToInt16(ObjectData[4]));
                        skycolor.B = Convert.ToByte(Convert.ToInt16(ObjectData[5]));
                        break;
                    }
                }
            }
        }
        /// <summary>
        /// Converts degrees to radians.
        /// </summary>
        /// <param name="rad">Degrees to convert.</param>
        /// <returns></returns>
        float Deg2Rad(float rad)
        {
            return rad * 3.141592f / 180;
        }
        /// <summary>
        /// Deletes all the objects in the editor.
        /// </summary>
        void ResetObjects()
        {
            for (int i = 0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
                ObjectsData[i] = null;
            }
        }
    }
}
