using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.IO;
using _3DRadSpaceDll;

namespace _3DRadSpacePlayer
{
    public class Game1 : Game
    {
        static Vector3 CamPos = new Vector3(0, 0, 0);
        Matrix view = Matrix.CreateLookAt(CamPos,CamPos + new Vector3(0,0,1),Vector3.Up);
        Matrix projection = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(45), 800f / 480f, 0.1f, 500f);
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        string[] gamesettings = { @"Projects/default.3drsp",@"False" };
        string[] Objects = new string[300] ;
        Sprite[] sprites = new Sprite[100];
        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            try
            {
                Objects[0] = "Camera GENERIC_OBJECT 0 0 0 0 0 0 75 True";
                Objects = File.ReadAllLines(gamesettings[0]);
            }
            catch (IOException e) {
                File.AppendAllText("log.txt", "Could not read the game main project:"+e.ToString());
            }
        }
        protected override void Initialize()
        {
            for(int i=0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
                if(Objects[i].Split(' ')[0] == "Camera")
                {
                    //Things to do here if initialisation will be needed.
                }
            }
            base.Initialize();
        }
        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);
            for(int i=0; i < _3DRadSpaceGame.MAX_OBJECTS; i++)
            {
               
            }
        }
        protected override void UnloadContent()
        {
        }
        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
            Exit(); 
            base.Update(gameTime);
        }
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Black);
            for(int i =0; i < 300;i++)
            {
                if (Objects[i] != null)
                {
                    if (Objects[i].Split(' ')[0] == "Camera")
                    {
                        Camera.Update(Objects[i],ref view,ref projection);
                    }
                }
            }
            base.Draw(gameTime);
        }
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

    }
}
