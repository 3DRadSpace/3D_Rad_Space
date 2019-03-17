using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.IO;
using System;
using _3DRadSpaceDll;

namespace _3DRadSpacePlayer
{
    public class Game1 : Game
    {
        static Vector3 CamPos = new Vector3(0, 4, 4);
        Matrix view = Matrix.CreateLookAt(CamPos,Vector3.Zero,Vector3.UnitY);
        Matrix projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45), 800f / 480f, 0.1f, 500f);
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        string[] gamesettings = { @"Projects/default.3drsp",@"False",null };
        object[] Objects = new object[_3DRadSpaceGame.MAX_OBJECTS],project = new object[_3DRadSpaceGame.MAX_OBJECTS];
        public static Model Error;
        public Game1()
        {
            if(File.Exists(@"settings.data"))
            {
                gamesettings = File.ReadAllLines(@"settings.data");
                Window.Title = gamesettings[2];
            }
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            try
            {
                project[0] = new Camera("DefaultCamera",true,new Vector3(10,0,10),Vector3.Zero);
                project = File.ReadAllLines(gamesettings[0]);
            }
            catch (IOException e) {
                File.AppendAllText("log.txt", "Could not read the game main project:"+e.ToString());
            }
        }
        protected override void Initialize()
        {
            base.Initialize();
        }
        protected override void LoadContent()
        {
            Error = Content.Load<Model>("Error");
            spriteBatch = new SpriteBatch(GraphicsDevice);
            for(int i=0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
                string obj = project[i].ToString();
               switch (obj.Split(' ')[0])
                {
                    case "Camera":
                        {
                            Vector3 pos = new Vector3(Convert.ToSingle(obj.Split(' ')[3]), Convert.ToSingle(obj.Split(' ')[4]), Convert.ToSingle(obj.Split(' ')[5]));
                            Objects[i] = new Camera(
                                    obj.Split(' ')[1],
                                    Convert.ToBoolean(obj.Split(' ')[2]),
                                    pos,
                                    Vector3.Zero, //Vector3.Transform(pos, Matrix.CreateFromYawPitchRoll(MathHelper.ToRadians(Convert.ToSingle(obj.Split(' ')[7])),MathHelper.ToRadians( Convert.ToSingle(obj.Split(' ')[6])), MathHelper.ToRadians(Convert.ToSingle(obj.Split(' ')[8])))),
                                    MathHelper.ToRadians(Convert.ToSingle(obj.Split(' ')[9])),
                                    Convert.ToSingle(obj.Split(' ')[11])
                                );
                            break;
                        }
                    case "SkyColor":
                        {
                            Color color = new Color(Convert.ToUInt32(obj.Split(' ')[3]), Convert.ToUInt32(obj.Split(' ')[4]), Convert.ToUInt32(obj.Split(' ')[5]));
                            Objects[i] = new SkyColor(
                                    obj.Split(' ')[1],
                                    Convert.ToBoolean(obj.Split(' ')[2]),
                                    color
                                    );
                            break;
                        }
                    case "Skinmesh":
                        {
                            Vector3 pos = new Vector3(Convert.ToSingle(obj.Split(' ')[3]), Convert.ToSingle(obj.Split(' ')[4]), Convert.ToSingle(obj.Split(' ')[5]));
                            Vector3 rot = new Vector3(Convert.ToSingle(obj.Split(' ')[6]), Convert.ToSingle(obj.Split(' ')[7]), Convert.ToSingle(obj.Split(' ')[8]));
                            string res = "";
                            int length = obj.Split(' ').Length;
                            for(int j =10; j < length ;j++)
                            {
                                res += obj.Split(' ')[j];
                                if (j != length - 1) res += " ";
                            }
                            Objects[i] = new SkinMesh(obj.Split(' ')[1],
                                Convert.ToBoolean(obj.Split(' ')[2]),
                                res, pos, rot);
                            break;
                           
                        }
                    case "TextPrint":
                        {
                            Color clr = new Color(Convert.ToInt32(obj.Split(' ')[5]),
                                Convert.ToInt32(obj.Split(' ')[6])
                                , Convert.ToInt32(obj.Split(' ')[7])
                                );
                            string text = "";
                            for (int j = 8; j < obj.Split(' ').Length; j++)
                            {
                                text += obj.Split(' ')[j];
                            }
                            Vector3 loc = new Vector3(Convert.ToInt32(obj.Split(' ')[4]),
                               Convert.ToInt32(obj.Split(' ')[5]), 0);

                            Objects[i] = new TextPrint(obj.Split(' ')[1], Convert.ToBoolean(obj.Split(' ')[2]), Content, loc, text, clr);
                            break;
                        }
                    case "Fog":
                        {
                            Vector3 clr = new Vector3(Convert.ToInt32(obj.Split(' ')[3]),
                              Convert.ToInt32(obj.Split(' ')[4])
                                 , Convert.ToInt32(obj.Split(' ')[5])
                             );
                            Objects[i] = new Fog(obj.Split(' ')[1], Convert.ToBoolean(obj.Split(' ')[2])
                                , clr, Convert.ToSingle(obj.Split(' ')[6]), Convert.ToSingle(obj.Split(' ')[7]));
                            break;
                        }
                    default: break;
                }
                AllObjectsInitialize();
            }
        }
        protected override void UnloadContent()
        {
        }
        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
            Exit();
            AllObjectsUpdate();
            base.Update(gameTime);
        }
        protected override void Draw(GameTime gameTime)
        {
            AllObjectsDraw();
            spriteBatch.GraphicsDevice.RasterizerState = RasterizerState.CullClockwise;
            spriteBatch.GraphicsDevice.BlendState = BlendState.Opaque;
            spriteBatch.GraphicsDevice.DepthStencilState = DepthStencilState.Default;
            spriteBatch.GraphicsDevice.SamplerStates[0] = SamplerState.LinearWrap;
            base.Draw(gameTime);
        }
        
        public void DrawModel(Model model, Matrix world, Matrix view, Matrix projection)
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
                    effect.EnableDefaultLighting();
                }
                mesh.Draw();
            }
        }
        
        void AllObjectsUpdate()
        {
            for(int i = 0; i < _3DRadSpaceGame.MAX_OBJECTS;i++)
            {
                if (Objects[i] is Camera camera)
                {
                    if (camera.IsActive == true) camera.Update(ref view,ref projection);
                }
            }
        }
        void AllObjectsDraw()
        {
            spriteBatch.Begin();
            Color clr = Color.Black;
            for (int i = 0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
                if (Objects[i] is SkyColor skyc)
                {
                    if (skyc.IsActive) clr = skyc.Color;
                }
            }
            GraphicsDevice.Clear(clr);
            for (int i = 0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
                if (Objects[i] is SkinMesh mesh)
                {
                    mesh.Draw(view, projection);
                }
                if(Objects[i] is TextPrint text)
                {
                    text.Draw(spriteBatch);
                }
            }
            spriteBatch.End();
        }
        void AllObjectsInitialize()
        {
            for (int i = 0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
                if (Objects[i] is SkinMesh mesh)
                {
                    mesh.Initialize(Content);
                }
                if(Objects[i] is Fog fog)
                {
                    FogColor = fog.Pos;
                    FogEnabled = fog.IsActive;
                    StartDistance = fog.Start;
                    EndDistance = fog.End;
                }
            }
        }
        Vector3 FogColor = new Vector3(255, 255, 255);
        bool FogEnabled = false;
        float StartDistance = 250;
        float EndDistance = 250;
    }
}
