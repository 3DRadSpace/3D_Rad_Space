using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using System.Collections.Generic;
using System.IO;

namespace Lib3DRadSpace_DX
{
	/// <summary>
	/// Represents a skybox.
	/// </summary>
	public class Skybox : BaseGameObject
	{
		/// <summary>
		/// Represents the collection of textures making up the skybox
		/// </summary>
		public Texture2D[] Textures;
		/// <summary>
		/// Skybox constructor.
		/// </summary>
		/// <param name="name">Object name.</param>
		/// <param name="visible">Is visible?</param>
		/// <param name="skyboxfile">.skybox asset containing the paths</param>
		public Skybox(string name,bool visible,string skyboxfile)
		{
			Name = name;
			Visible = visible;
			Asset = skyboxfile;
		}
		IRenderer _linkedcamera;
		/// <summary>
		/// Finds a camera to link the skybox object to.
		/// </summary>
		public void FindLinkedCamera()
		{
			for(int i = 0; i < CurrentProject.GameObjects.Count; i++)
			{
				IGameObject obj = CurrentProject.GameObjects[i];
				if(obj is IRenderer rnd)
				{
					_linkedcamera = rnd;
					return;
				}
			}
		}
		/// <summary>
		/// Links a camera to the skybox object.
		/// </summary>
		/// <param name="cam"></param>
		public void LinkCamera(IRenderer cam)
        {
			_linkedcamera = cam;
        }
		/// <summary>
		/// Loads the skybox textures/
		/// </summary>
		/// <param name="content"></param>
		public override void Load(ContentManager content)
		{
			FindLinkedCamera();
			GraphicsDevice gd = CurrentProject.GraphicsDevice;
			Textures = new Texture2D[6];
			string[] skyb = File.ReadAllLines(content.RootDirectory+"\\"+Asset);

			string folder = Path.GetDirectoryName(content.RootDirectory + "\\"+Asset);
			for(int i = 0; i < 6; i++)
				Textures[i] = ContentHelper.LoadTextureFromFile(gd, folder + "\\"+ skyb[i]);

			if(_cube == null)
				_cube = content.Load<Model>("Skybox\\Skybox");
		}
		static Model _cube;

		/// <summary>
		/// Gets the World matrix of this skybox, in order to match the Camera object.
		/// </summary>
		public new Matrix World
		{
			get
			{
				return Matrix.CreateScale(_linkedcamera.FarPlaneDistance - 20) * Matrix.CreateTranslation(_linkedcamera.Position);
			}
		}
		/// <summary>
		/// 
		/// </summary>
		public Texture3D TextureBox
        {
			get
            {
				Texture3D t = new Texture3D(CurrentProject.GraphicsDevice, 1024, 1024, 1024, false, SurfaceFormat.Color);
				return t;
            }
        }
		/// <summary>
		/// Draws the skybox.
		/// </summary>
		/// <param name="time">Npt used/</param>
		/// <param name="frustrum">Not used. Skybox is always drawn.</param>
		/// <param name="view">View matrix</param>
		/// <param name="projection">Projection matrix</param>
		public override void Draw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
		{
			if(Visible) drawCube(view, projection);
		}
		/// <summary>
		/// Draws the skybox in the editor.
		/// </summary>
		/// <param name="time">Npt used/</param>
		/// <param name="frustrum">Not used. Skybox is always drawn.</param>
		/// <param name="view">View matrix</param>
		/// <param name="projection">Projection matrix</param>
		public override void EditorDraw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
        {
			drawCube(view, projection);
        }
        void drawCube(Matrix view,Matrix proj)
		{
			/*
			 *  THE PAIN WRITING THIS FUNCTION
			 *  THE CODE I USED FROM 0.0.6A WORKED FINE BEFORE, BUT NOT NOW WHEN USING A CUSTOM SKYBOX SHADER
			 *  Hope it wont break in the future. If it does, I'll cry for real...
			 */
			Shaders.SkyboxShader skybsh = CurrentProject.SkyboxShader;
			int[] table = {1,5,0,2,3,4 };
			float[] flipoffsetx = { 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f };
			float[] flipoffsety = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,0.0f };
			for(int i =0; i < 6;i++)
            {
				skybsh.FlipOffsetX = flipoffsetx[i];
				skybsh.FlipOffsetY = flipoffsety[i];
				skybsh.SkyboxTexure = Textures[table[i]];
				skybsh.DrawModelPart(_cube.Meshes[0].MeshParts[i], World, view, proj);
            }
		}
		/// <summary>
		/// Unloads the skybox from the memory.
		/// </summary>
		public override void Unload()
		{
			for(int i = 0; i < 6; i++) Textures[i].Dispose();
		}
		/// <summary>
		/// 
		/// </summary>
		/// <param name="buff"></param>
		/// <param name="position"></param>
		/// <param name="result"></param>
        public override void LoadF(byte[] buff, ref int position, out IGameObject result)
        {
			string name = ByteCodeParser.GetString(buff, ref position);
			bool visible = ByteCodeParser.GetBool(buff, ref position);
			string asset = ByteCodeParser.GetString(buff, ref position);
			result = new Skybox(name, visible, asset);
        }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="buff"></param>
        public override void SaveF(List<byte> buff)
        {
			ByteCodeParser.SetString(buff, Name);
			ByteCodeParser.SetBool(buff, Visible);
			ByteCodeParser.SetString(buff, Asset);
        }
    }
}
