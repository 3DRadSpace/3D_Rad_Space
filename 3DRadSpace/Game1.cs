using _3DRadSpaceDll;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Threading;
using System.Windows.Forms;

#pragma warning disable IDE0044

namespace _3DRadSpace
{
    public class Game1 : Game 
    {
        //Vector2 rotatecamoffset;
        static Vector3 LookAt = new Vector3(0, 0, 0);
        static Vector3 CameraPos = new Vector3(10, 1, 3);
        Matrix world = Matrix.CreateTranslation(new Vector3(0, 0, 0));
        Matrix view = Matrix.CreateLookAt(CameraPos,LookAt, Vector3.UnitY);
        Matrix projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45), 800f / 480f, 0.1f, 500f); //Last parameter is maximum view distance
        GraphicsDeviceManager graphics;
        Texture2D GUI1;
        SpriteBatch spriteBatch;
        Model Axis;
        SpriteFont Font;
        Model[] GameObjects = new Model[_3DRadSpaceGame.MAX_OBJECTS];
        public string[] ObjectsData = new string[_3DRadSpaceGame.MAX_OBJECTS];
        Texture2D[] GameSprites = new Texture2D[_3DRadSpaceGame.MAX_OBJECTS];
        Color skycolor = new Color(100, 100, 255);
        bool IsProjectSaved = true, _3D_OR_2D_MODE = false;
        static public bool Focus = true;
        Texture2D objimg;
        BoundingSphere[] boundingSpheres = new BoundingSphere[_3DRadSpaceGame.MAX_OBJECTS];
        int selectedobj = -1;
        ListBox ObjectsBox = new ListBox();
        MenuStrip ToolsStrip = new MenuStrip();
        Vector3 TotalCameraDir = new Vector3(0, 0, 0);
        Vector3 cameraDirection = new Vector3(-0.5f, 0, -0.5f);
        Vector3 cameraUp;
        float CameraZoom = 1f;
        float Movspeed = 0.5f;

         MouseState prevMouseState;


        public string ProjectPath = "";

        public static string LastObj = "";

            ToolStripMenuItem fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem newProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem openProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem saveProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem saveProjectAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem PlayProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem compileProjectsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem addAObjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem addAAddonToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem installResourcesIntoProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem checkForUpdatesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem settingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem officialWebsiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ToolStripMenuItem reportABugToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        ToolStripMenuItem documentationStripMenuItem = new ToolStripMenuItem();
        public static NotifyIcon notifyIcon = new NotifyIcon()
        {
            Icon = System.Drawing.Icon.ExtractAssociatedIcon("Icon.ico"),
            Visible = true,
            Text = "3DRadSpace",
            Tag = "3DRadSpace v0.1 pre-alpha",
        };
        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }
        protected override void Initialize()
        {
            prevMouseState = Mouse.GetState();
            UpdateV(false);
            // TODO: Add your initialization logic here
            IsMouseVisible = true;
            Window.Position = new Point(0, 0);
            graphics.PreferredBackBufferHeight = Screen.PrimaryScreen.Bounds.Height - 75;
            graphics.PreferredBackBufferWidth = Screen.PrimaryScreen.Bounds.Width - 16;
            graphics.ApplyChanges();
            Window.Title = "3DRadSpace v0.1 Pre-Alpha release -Editor-";
            notifyIcon.BalloonTipClicked += NotifyIcon_BalloonTipClicked;
            Form gameform = Control.FromHandle(Window.Handle) as Form;
            gameform.AllowDrop = true;
            gameform.FormClosing += new FormClosingEventHandler(OnGameEditorClosing);
            gameform.DragDrop += new DragEventHandler(DragDropProject);
            gameform.DragEnter += new DragEventHandler(DragEnter);
            ObjectsBox.Location = new System.Drawing.Point(0,25);
            ObjectsBox.Height = graphics.PreferredBackBufferHeight;
            ObjectsBox.Width = 150;
            ObjectsBox.DoubleClick += new EventHandler(EditObjectFromList);
            
            gameform.Controls.Add(ObjectsBox);

            fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            newProjectToolStripMenuItem,
            openProjectToolStripMenuItem,
            saveProjectToolStripMenuItem,
            saveProjectAsToolStripMenuItem,
            PlayProjectToolStripMenuItem,
            compileProjectsToolStripMenuItem,
            exitToolStripMenuItem});
            fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            fileToolStripMenuItem.Size = new System.Drawing.Size(35, 20);
            fileToolStripMenuItem.Text = "File";
            // 
            // newProjectToolStripMenuItem
            // 
            newProjectToolStripMenuItem.Name = "newProjectToolStripMenuItem";
            newProjectToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            newProjectToolStripMenuItem.Text = "New Project";
            newProjectToolStripMenuItem.Click += new EventHandler(NewProjectEvent);
            // 
            // openProjectToolStripMenuItem
            // 
            openProjectToolStripMenuItem.Name = "openProjectToolStripMenuItem";
            openProjectToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            openProjectToolStripMenuItem.Text = "Open Project";
            openProjectToolStripMenuItem.Click += new EventHandler(OpenProjectEvent);
            // 
            // saveProjectToolStripMenuItem
            // 
            saveProjectToolStripMenuItem.Name = "saveProjectToolStripMenuItem";
            saveProjectToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            saveProjectToolStripMenuItem.Text = "Save Project";
            saveProjectToolStripMenuItem.Click += new EventHandler(SaveProject);
            // 
            // saveProjectAsToolStripMenuItem
            // 
            saveProjectAsToolStripMenuItem.Name = "saveProjectAsToolStripMenuItem";
            saveProjectAsToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            saveProjectAsToolStripMenuItem.Text = "Save Project As";
            saveProjectAsToolStripMenuItem.Click += new EventHandler(SaveProjectAs);
            // 
            // saveProjectAsToolStripMenuItem
            // 
            PlayProjectToolStripMenuItem.Name = "PlayProjectToolStripMenuItem";
            PlayProjectToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            PlayProjectToolStripMenuItem.Text = "Play Project";
            PlayProjectToolStripMenuItem.Click += new EventHandler(PlayProject);
            // 
            // compileProjectsToolStripMenuItem
            // 
            compileProjectsToolStripMenuItem.Name = "compileProjectsToolStripMenuItem";
            compileProjectsToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            compileProjectsToolStripMenuItem.Text = "Compile Project(s)";
            compileProjectsToolStripMenuItem.Click += new EventHandler(CompileProject);
            // 
            // exitToolStripMenuItem
            // 
            exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            exitToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            exitToolStripMenuItem.Text = "Exit";
            exitToolStripMenuItem.Click += new EventHandler(Exit);
            // 
            // editToolStripMenuItem
            // 
            editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            addAObjectToolStripMenuItem,
            addAAddonToolStripMenuItem,
            installResourcesIntoProjectToolStripMenuItem});
            editToolStripMenuItem.Name = "editToolStripMenuItem";
            editToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            editToolStripMenuItem.Text = "Edit";
            // 
            // addAObjectToolStripMenuItem
            // 
            addAObjectToolStripMenuItem.Name = "addAObjectToolStripMenuItem";
            addAObjectToolStripMenuItem.Size = new System.Drawing.Size(211, 22);
            addAObjectToolStripMenuItem.Text = "Add a object";
            addAObjectToolStripMenuItem.Click += new EventHandler(AddObject);
            // 
            // addAAddonToolStripMenuItem
            // 
            addAAddonToolStripMenuItem.Name = "addAAddonToolStripMenuItem";
            addAAddonToolStripMenuItem.Size = new System.Drawing.Size(211, 22);
            addAAddonToolStripMenuItem.Text = "Add a Addon";
            addAAddonToolStripMenuItem.Click += new EventHandler(AddAddon);
            // 
            // installResourcesIntoProjectToolStripMenuItem
            // 
            installResourcesIntoProjectToolStripMenuItem.Name = "installResourcesIntoProjectToolStripMenuItem";
            installResourcesIntoProjectToolStripMenuItem.Size = new System.Drawing.Size(211, 22);
            installResourcesIntoProjectToolStripMenuItem.Text = "Install resources into project";
            installResourcesIntoProjectToolStripMenuItem.Click += new EventHandler(InstallResource);
            // 
            // optionsToolStripMenuItem
            // 
            optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            checkForUpdatesToolStripMenuItem,
            settingsToolStripMenuItem});
            optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            optionsToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            optionsToolStripMenuItem.Text = "Options";
            // 
            // checkForUpdatesToolStripMenuItem
            // 
            checkForUpdatesToolStripMenuItem.Name = "checkForUpdatesToolStripMenuItem";
            checkForUpdatesToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            checkForUpdatesToolStripMenuItem.Text = "Check for updates";
            checkForUpdatesToolStripMenuItem.Click += new EventHandler(UpdateEvent);
            // 
            // settingsToolStripMenuItem
            // 
            settingsToolStripMenuItem.Name = "settingsToolStripMenuItem";
            settingsToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            settingsToolStripMenuItem.Text = "Settings";
            settingsToolStripMenuItem.Click += new EventHandler(Settings);
            // 
            // helpToolStripMenuItem
            // 
            helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            aboutToolStripMenuItem,
            documentationStripMenuItem,
            officialWebsiteToolStripMenuItem,
            reportABugToolStripMenuItem});
            helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            helpToolStripMenuItem.Size = new System.Drawing.Size(40, 20);
            helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            aboutToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            aboutToolStripMenuItem.Text = "About";
            aboutToolStripMenuItem.Click += new EventHandler(About);
            //
            // documentationStripMenuItem
            //
            documentationStripMenuItem.Name = "documentationStripMenuItem";
            documentationStripMenuItem.Size = new System.Drawing.Size(180, 22);
            documentationStripMenuItem.Text = "Documentation";
            documentationStripMenuItem.Click += new EventHandler(HelpFiles);
            // 
            // officialWebsiteToolStripMenuItem
            // 
            officialWebsiteToolStripMenuItem.Name = "officialWebsiteToolStripMenuItem";
            officialWebsiteToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            officialWebsiteToolStripMenuItem.Text = "Official Website";
            officialWebsiteToolStripMenuItem.Click += new EventHandler(Website);
            // 
            // reportABugToolStripMenuItem
            // 
            reportABugToolStripMenuItem.Name = "reportABugToolStripMenuItem";
            reportABugToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            reportABugToolStripMenuItem.Text = "Report a bug";
            reportABugToolStripMenuItem.Click += new EventHandler(ReportBug);

            ToolsStrip.Items.AddRange(new ToolStripItem[] {
            fileToolStripMenuItem,
            editToolStripMenuItem,
            optionsToolStripMenuItem,
            helpToolStripMenuItem});
            gameform.Controls.Add(ToolsStrip);


            cameraDirection = LookAt - CameraPos;

            cameraDirection.Normalize();

            cameraUp = Vector3.Up;

            base.Initialize();
        }

        private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        private void OnGameEditorClosing(object sender, FormClosingEventArgs e)
        {
            string[] data = File.ReadAllLines(@"settings.data");
            if (data[1] == "True")
            {
                if (IsProjectSaved == false)
                {
                    DialogResult warn1 = System.Windows.Forms.MessageBox.Show("Project is not saved. Save the project?", "Warning", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Warning);
                    if (warn1 == DialogResult.Yes)
                    {
                        SaveProject(null, null);
                    }
                    else if (warn1 == DialogResult.Cancel)
                    {
                        e.Cancel = true;
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
            objimg = Content.Load<Texture2D>("objimg");
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
            if (_3DRadSpace_EditorClass.DotInSquare(new Vector2(mouse.X, mouse.Y),
                new Vector2(150, 25), new Vector2(graphics.PreferredBackBufferWidth, graphics.PreferredBackBufferHeight)
                ))
            {

                if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.W)) CameraPos += cameraDirection * Movspeed;
                if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.S)) CameraPos -= cameraDirection * Movspeed;
                if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.A)) CameraPos += Vector3.Cross(cameraUp, cameraDirection) * Movspeed;
                if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.D)) CameraPos -= Vector3.Cross(cameraUp, cameraDirection) * Movspeed;
                if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.E)) CameraPos.Y += 1;
                if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.Q)) CameraPos.Y -= 1;
                
                if (mouse.RightButton == Microsoft.Xna.Framework.Input.ButtonState.Pressed)
                {
                    Ray objectfinder = GetMouseRay(new Vector2(mouse.X, mouse.Y), GraphicsDevice.Viewport, view, projection);
                    for (int i = 0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
                    {
                        if (objectfinder.Intersects(boundingSpheres[i]) != null)
                        {
                            selectedobj = i;
                            world = Matrix.CreateTranslation(boundingSpheres[i].Center);
                            break;
                        }
                        else
                        {
                            world = Matrix.CreateTranslation(0, 0, 0);
                            selectedobj = -1;
                        }
                    }
                }
                if (selectedobj != -1)
                {
                    if (keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.Enter) == true)
                    {
                        EditObject(selectedobj);
                    }
                }
                if (mouse.RightButton == Microsoft.Xna.Framework.Input.ButtonState.Pressed)
                {
                    //set the mouse to the center
                    Mouse.SetPosition(graphics.PreferredBackBufferWidth / 2, graphics.PreferredBackBufferHeight / 2);
                    //Get the distance from the center of the game-screen
                    Vector2 Offset = new Vector2((graphics.PreferredBackBufferWidth / 2 - mouse.X), graphics.PreferredBackBufferHeight / 2 - mouse.Y);
                    //File.AppendAllText("MouseDebug.log", Offset.X + " " + Offset.Y + " \n");

                    //it kinda works please don't kill me :c
                    //NOTE: Works fine when you hold. (NO IT DOESNT)

                    TotalCameraDir.X += Offset.Y / 200; 
                    TotalCameraDir.Z += Offset.X / 200;

                    cameraDirection.X = (float)Math.Cos(TotalCameraDir.X) * CameraZoom;
                    cameraDirection.Z = (float)Math.Sin(TotalCameraDir.X) * CameraZoom;
                }
            }
            if(keyboard.IsKeyDown(Microsoft.Xna.Framework.Input.Keys.Delete))
            {
                int a = ObjectsBox.SelectedIndex;
                if(a != -1)
                {
                    if (ObjectsData[a] != null)
                    {
                        if (ObjectsData[a].Split(' ')[0] == "SkyColor") skycolor = new Color(100, 100, 255);
                        if (ObjectsData[a].Split(' ')[0] == "Fog") FogEnabled = false;
                    }
                    ObjectsData[a] = null;
                    for (int i =a; i < _3DRadSpaceGame.MAX_OBJECTS -1 ;i++)
                    {
                        ObjectsData[i] = ObjectsData[i + 1];
                    }
                    ObjectsBoxItems();
                }
            }
            base.Update(gameTime);
        }
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(skycolor);
            DrawModel(Axis, world,view, projection);
            spriteBatch.Begin();
            view = Matrix.CreateLookAt(CameraPos + cameraDirection,CameraPos , Vector3.UnitY);
            for(int i=0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
                if (ObjectsData[i] != null)
                    CreateObject(ObjectsData[i].Split(' '));
            }
            spriteBatch.DrawString(Font, "Cam_Dir: (" + cameraDirection.X + "," + cameraDirection.Y + "," + cameraDirection.Z + ")", new Vector2(200, graphics.PreferredBackBufferHeight - 20), Color.Black); ;
            spriteBatch.End();
            spriteBatch.GraphicsDevice.RasterizerState = RasterizerState.CullCounterClockwise;
            spriteBatch.GraphicsDevice.BlendState = BlendState.Opaque;
            spriteBatch.GraphicsDevice.DepthStencilState = DepthStencilState.Default;
            spriteBatch.GraphicsDevice.SamplerStates[0] = SamplerState.LinearWrap;
            base.Draw(gameTime);
        }
        Vector2 ShitFunctionThatCalculatesTheGoddamnCameraRotation(Vector2 a)
        {
            return a;     
        }
        /// <summary>
        /// Finds a update for 3DRadSpace
        /// </summary>
        public static void UpdateV(bool forced)
        {
            string[] Setting = { "True", "True" };
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
                    DialogResult UpdateQ = System.Windows.Forms.MessageBox.Show("A update is avalable for 3DRadSpace. Version" + LastVersion[0] + " " + LastVersion[1] + " " + LastVersion[2] + " \r\n Do you want to download it?", "Information", MessageBoxButtons.YesNo, MessageBoxIcon.Information);
                    if (UpdateQ == DialogResult.Yes)
                    {
                        vchecker.DownloadFile("https://drive.google.com/uc?export=download&id=0B9yRO5eZEvTjSVhCZndjSGRUcVE", @"3DRadSpace_Installer.exe");
                        Process.Start(@"3DRadSpace_Installer.exe");
                        notifyIcon.ShowBalloonTip(1000, "3DRadSpace is updating, so the application will close until the update is done.", "Update", ToolTipIcon.Info);
                        Thread.Sleep(1100);
                        Application.Exit();
                    }
                    else
                    {
                        System.Windows.Forms.MessageBox.Show("You can update 3DRadSpace from the official website", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
                else
                {
                    System.Windows.Forms.MessageBox.Show("No new updates", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
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
                    effect.FogEnabled = FogEnabled;
                    effect.FogColor = FogColor;
                    effect.FogStart = StartDistance;
                    effect.FogEnd = EndDistance;
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
                        if (_3D_OR_2D_MODE == false)
                        {
                            Matrix objpos = Matrix.CreateTranslation(new Vector3(Convert.ToSingle(ObjectData[3]), Convert.ToSingle(ObjectData[4]), Convert.ToSingle(ObjectData[5])));
                            Matrix rotation = Matrix.CreateFromYawPitchRoll(Deg2Rad(Convert.ToSingle(ObjectData[7])), Deg2Rad(Convert.ToSingle(ObjectData[6])), Deg2Rad(Convert.ToSingle(ObjectData[8])));
                            objpos = rotation * objpos;

                            GameObjects[i - 1] = Content.Load<Model>("Camera");
                            DrawModel(GameObjects[i - 1], objpos, view, projection);
                            boundingSpheres[i - 1] = new BoundingSphere(new Vector3(Convert.ToSingle(ObjectData[3]), Convert.ToSingle(ObjectData[4]), Convert.ToSingle(ObjectData[5])), 1.5f);
                            break;
                        }
                    }
                    if(ObjectData[0] == "SkyColor")
                    {
                        skycolor.R = Convert.ToByte(Convert.ToInt16(ObjectData[3]));
                        skycolor.G = Convert.ToByte(Convert.ToInt16(ObjectData[4]));
                        skycolor.B = Convert.ToByte(Convert.ToInt16(ObjectData[5]));
                        break;
                    }
                    if (ObjectData[0] == "TextPrint")
                    {
                        string text = "";
                        for (int j = 8; j < ObjectData.Length; j++)
                        {
                            text += ObjectData[j]+" ";
                        }
                        spriteBatch.DrawString(Font,text,new Vector2(150+Convert.ToSingle(ObjectData[3]), 25+Convert.ToSingle(ObjectData[4])), new Color(Convert.ToInt32(ObjectData[5]), Convert.ToInt32(ObjectData[6]), Convert.ToInt32(ObjectData[7])));
                        break;
                    }
                    if (ObjectData[0] == "Sprite")
                    {
                        break;
                    }
                    if (ObjectData[0] == "Fog")
                    {
                        FogEnabled = Convert.ToBoolean(ObjectData[2]);
                        StartDistance = Convert.ToSingle(ObjectData[3]);
                        EndDistance = Convert.ToSingle(ObjectData[4]);
                       FogColor = new Vector3(
                            Convert.ToSingle(ObjectData[5]),
                            Convert.ToSingle(ObjectData[6]),
                            Convert.ToSingle(ObjectData[7])
                            );
                        break;
                    }
                        if (ObjectData[0] == "Skinmesh")
                        {
                        if (GameObjects[i] == null)
                        {
                            string res = "";
                            for (int j = 10; j < ObjectData.Length; j++)
                            {
                                res += ObjectData[j];
                                if (j != ObjectData.Length - 1) res += " ";
                            }
                            try
                            {
                                GameObjects[i] = Content.Load<Model>(res);
                            }
                            catch
                            {
                                GameObjects[i] = Content.Load<Model>("Error");
                                System.Windows.Forms.MessageBox.Show("Model [" + res + "] wasn't found in the Content folder. Make sure the model is in .xnb format", "Model Loading error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            }
                        }
                        else
                        {
                            DrawModel(GameObjects[i],Matrix.CreateFromYawPitchRoll(Convert.ToSingle(ObjectData[7]),
                                Convert.ToSingle(ObjectData[7]),Convert.ToSingle(ObjectData[8])) 
                                * Matrix.CreateTranslation(Convert.ToSingle(ObjectData[3]),
                                  Convert.ToSingle(ObjectData[4]),
                                  Convert.ToSingle(ObjectData[5])), view, projection);
                        }
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
            skycolor = new Color(100, 100, 255);
            ObjectsBoxItems();
        }
        public static Ray GetMouseRay(Vector2 mousePosition, Viewport viewport,Matrix view,Matrix projection)
        {
            Vector3 nearPoint = new Vector3(mousePosition, 0);
            Vector3 farPoint = new Vector3(mousePosition, 1);
            nearPoint = viewport.Unproject(nearPoint,projection ,view , Matrix.Identity);
            farPoint = viewport.Unproject(farPoint, projection,view , Matrix.Identity);
            Vector3 direction = farPoint - nearPoint;
            direction.Normalize();
            return new Ray(nearPoint, direction);
        }
        void EditObject(int id)
        {
            if (ObjectsData[id] != null)
            {
                string[] objdata = ObjectsData[id].Split(' ');
                bool edit = false;
                if (objdata[0] == "Camera")
                {
                    Camera editcamera = new Camera();
                    editcamera.textBox1.Text = objdata[1];
                    editcamera.checkBox1.Checked = Convert.ToBoolean(objdata[2]);
                    editcamera.textBox2.Text = objdata[3];
                    editcamera.textBox3.Text = objdata[4];
                    editcamera.textBox4.Text = objdata[5];
                    editcamera.textBox5.Text = objdata[6];
                    editcamera.textBox6.Text = objdata[7];
                    editcamera.textBox7.Text = objdata[8];
                    editcamera.numericUpDown1.Value = Convert.ToDecimal(objdata[9]);
                    for(int i =0; i < objdata.Length - 9; i++)
                    {
                        editcamera.OBJR += objdata[9 + i] + " ";
                    }
                    if (editcamera.ShowDialog() == DialogResult.OK) edit = true;
                }
                if(objdata[0] == "SkyColor")
                {
                    Skycolor editskycolor = new Skycolor();
                    editskycolor.textBox1.Text = objdata[1];
                    editskycolor.checkBox1.Checked = Convert.ToBoolean(objdata[2]);
                    editskycolor.textBox2.Text = objdata[3];
                    editskycolor.textBox3.Text = objdata[4];
                    editskycolor.textBox4.Text = objdata[5];
                    if (editskycolor.ShowDialog() == DialogResult.OK) edit = true;
                }
                if(objdata[0] == "EOL")
                {
                    EOL eol = new EOL();
                    eol.textBox1.Text = objdata[1];
                    eol.checkBox1.Checked = Convert.ToBoolean(objdata[2]);
                    eol.type = Convert.ToInt32(objdata[3]);
                    eol.SelectType();
                    eol.textBox2.Text = objdata[4];
                    eol.textBox3.Text = objdata[5];
                    eol.textBox4.Text = objdata[6];
                    eol.textBox7.Text = objdata[7];
                    eol.textBox6.Text = objdata[8];
                    eol.textBox5.Text = objdata[9];
                    if (eol.ShowDialog() == DialogResult.OK) edit = true;
                }
                if (objdata[0] == "Skinmesh")
                {
                    Skinmesh skinmesh = new Skinmesh();
                    skinmesh.textBox1.Text = objdata[1];
                    skinmesh.checkBox1.Checked = Convert.ToBoolean(objdata[2]);
                    skinmesh.textBox2.Text = objdata[3];
                    skinmesh.textBox3.Text = objdata[4];
                    skinmesh.textBox4.Text = objdata[5];
                    skinmesh.textBox5.Text = objdata[6];
                    skinmesh.textBox6.Text = objdata[7];
                    skinmesh.textBox7.Text = objdata[8];
                    skinmesh.domainUpDown1.SelectedIndex = Convert.ToInt32(objdata[9]);
                    skinmesh.textBox8.Text = "";
                    for (int i = 10; i < objdata.Length; i++)
                    {
                        skinmesh.textBox8.Text += objdata[i] + " ";
                    }
                    if (skinmesh.ShowDialog() == DialogResult.OK) edit = true;
                }
                if(objdata[0] == "TextPrint")
                {
                    TextPrint textPrint = new TextPrint();
                    textPrint.textBox1.Text = objdata[1];
                    textPrint.textBox2.Text = "";
                    textPrint.checkBox1.Checked = Convert.ToBoolean(objdata[2]);
                    textPrint.textBox3.Text = objdata[3];
                    textPrint.textBox4.Text = objdata[4];
                    textPrint.Colour = System.Drawing.Color.FromArgb(Convert.ToInt16(objdata[5]),
                        Convert.ToInt16(objdata[6]), Convert.ToInt16(objdata[7]));
                    for (int i = 8; i < objdata.Length; i++)
                    {
                        textPrint.textBox2.Text += objdata[i] + " ";
                    }
                    if (textPrint.ShowDialog() == DialogResult.OK) edit = true;
                }
                if (objdata[0] == "Fog")
                {
                    Fog fog = new Fog();
                    fog.textBox1.Text = objdata[1];
                    fog.checkBox1.Checked = Convert.ToBoolean(objdata[2]);
                    fog.textBox2.Text = objdata[3];
                    fog.textBox3.Text = objdata[4];
                    fog.textBox4.Text = objdata[5];
                    fog.textBox5.Text = objdata[6];
                    fog.textBox6.Text = objdata[7];
                    if (fog.ShowDialog() == DialogResult.OK) edit = true;
                }
                if(edit)
                {
                    ObjectsData[id] = LastObj;
                    LastObj = "";
                }
                ObjectsBoxItems();
            }
        }
        public void ObjectsBoxItems()
        {
            ObjectsBox.Items.Clear();
            for(int i =0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
                if (ObjectsData[i] != null)
                {
                    ObjectsBox.Items.Add(ObjectsData[i].Split(' ')[1]);
                }
            }
        }
        void NewProjectEvent(object sender,EventArgs e)
        {
            IsProjectSaved = false;
            ProjectPath = "";
            ResetObjects();
        }
        void OpenProjectEvent(object sender,EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
                Filter = "3DRadSpace Project (*.3drsp)|*.3drsp|Text File (*.txt)|*.txt",
                Title = "Open a 3DRadSpace Project",
                Multiselect = false
            };
            DialogResult res = openFile.ShowDialog();
            if(res == DialogResult.OK)
            {
                if(File.Exists(openFile.FileName))
                {
                    ResetObjects();
                    string[] file = File.ReadAllLines(openFile.FileName);
                    for(int i =0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
                    {
                        if (!string.IsNullOrEmpty(file[i])) ObjectsData[i] = file[i];
                        else break;
                    }
                    IsProjectSaved = true;
                    ProjectPath = openFile.FileName;
                    ObjectsBoxItems();
                }
            }
        }
        void SaveProject(object sender, EventArgs e)
        {
            if (ProjectPath == "")
            {
                SaveProjectAs(sender, e);
            }
            else
            {
                File.WriteAllLines(ProjectPath, ObjectsData);
                IsProjectSaved = true;
            }
        }
        void SaveProjectAs(object sender, EventArgs e)
        {
            SaveFileDialog saveFile = new SaveFileDialog()
            {
                Filter = "3DRadSpace Project (*.3drsp)|*.3drsp|Text File (*.txt)|*.txt",
                Title = "Save a 3DRadSpace Project",
                OverwritePrompt = true
            };
            DialogResult result = saveFile.ShowDialog();
            if (result == DialogResult.OK)
            {
                File.WriteAllLines(saveFile.FileName, ObjectsData);
                IsProjectSaved = true;
                ProjectPath = saveFile.FileName;
            }
        }
        void PlayProject(object sender,EventArgs e)
        {
            SaveProject(null, null);
            PlayTestingLauncher.ProjectPath = this.ProjectPath;
            PlayTestingLauncher playTesting = new PlayTestingLauncher();
            playTesting.ShowDialog();
        }
        void CompileProject(object sender,EventArgs e)
        {
            _3DRadSpaceCompiler comp = new _3DRadSpaceCompiler();
            comp.ShowDialog();
        }
        void Exit(object sender,EventArgs e)
        {
            Application.Exit();
        }
        void AddObject(object sender,EventArgs e)
        {
            ObjectsList objectsList = new ObjectsList();
            DialogResult result = objectsList.ShowDialog();
            for(int i =0; i < _3DRadSpaceGame.MAX_OBJECTS; i ++)
            {
                if(ObjectsData[i] == null)
                {
                    if(LastObj != "" && result == DialogResult.OK) ObjectsData[i] = LastObj;
                    break;
                }
            }
            ObjectsBoxItems();
            IsProjectSaved = false;
        }
        void AddAddon(object sender,EventArgs e)
        {
            OpenFileDialog AddonDialog = new OpenFileDialog()
            {
                Filter = "3DRadSpace Project (*.3drsp)|*.3drsp|Text File (*.txt)|*.txt",
                Title = "Install a addon into your project...",
                Multiselect = false,
            };
            if(AddonDialog.ShowDialog() == DialogResult.OK)
            {
                int j = 0;
                string[] file = File.ReadAllLines(AddonDialog.FileName);
                for(int i =0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
                {
                    if(ObjectsData[i] == null)
                    {
                        if (!string.IsNullOrEmpty(file[j]))
                        {
                            ObjectsData[i] = file[j];
                            j++;
                        }
                    }
                }
                IsProjectSaved = false;
                ObjectsBoxItems();
            }
        }
        void InstallResource(object sender,EventArgs e)
        {

        }
        void UpdateEvent(object sender, EventArgs e)
        {
            notifyIcon.BalloonTipText = "The application will freeze for a little while...";
            notifyIcon.BalloonTipTitle = "Looking for updates...";
            notifyIcon.BalloonTipIcon = ToolTipIcon.Info;
            notifyIcon.ShowBalloonTip(2000);
            UpdateV(true);
        }
        void Settings(object sender, EventArgs e)
        {
            OptionsDialog options = new OptionsDialog();
            options.ShowDialog();
        }
        void About(object sender,EventArgs e)
        {
            AboutWindow about = new AboutWindow();
            about.ShowDialog();
        }
        void Website(object sender,EventArgs e)
        {
            Process.Start("https://3dradspace.000webhostapp.com");
        }
        void ReportBug(object sender,EventArgs e)
        {
            Process.Start("https://3dradspace.000webhostapp.com/Report-a-bug/");
        }
        void EditObjectFromList(object sender,EventArgs e)
        {
           if(ObjectsBox.SelectedIndex >= 0) EditObject(ObjectsBox.SelectedIndex);
        }
        void HelpFiles(object sender,EventArgs e)
        {
            
        }
        void DragDropProject(object sender, DragEventArgs e)
        {
            string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
            string[] file = File.ReadAllLines(files[0]);
            string[] pathdata = files[0].Split('.');

            string ext = pathdata[pathdata.Length-1]; 
            if (ext != "3drsp" && ext != "txt")
            {
                System.Windows.Forms.MessageBox.Show("Invaild file dropped!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            ResetObjects();
            for (int i = 0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
                if (!string.IsNullOrEmpty(file[i])) ObjectsData[i] = file[i];
                else break;
            }
            IsProjectSaved = true;
            ProjectPath = files[0];
            ObjectsBoxItems();
        }
        void DragEnter(object sender,DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effect = DragDropEffects.Copy;
            }
        }
        Vector3 FogColor = new Vector3(255, 255, 255);
        bool FogEnabled = false;
        float StartDistance = 250;
        float EndDistance = 250;
    }
}
