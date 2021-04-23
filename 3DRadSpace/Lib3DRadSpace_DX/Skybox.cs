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
		/// Loads the skybox textures/
		/// </summary>
		/// <param name="content"></param>
		public override void Load(ContentManager content)
		{
			FindLinkedCamera();
			GraphicsDevice gd = CurrentProject.GraphicsDevice;
			Textures = new Texture2D[6];
			string[] skyb = File.ReadAllLines(Asset);

			for(int i = 0; i < 6; i++)
				Textures[i] = ContentHelper.LoadTextureFromFile(gd, skyb[i]);

			if(_cube == null)
				_cube = content.Load<Model>("Skybox\\Cube");
		}
		static Model _cube;

		/// <summary>
		/// Gets the World matrix of this skybox, in order to match the Camera object.
		/// </summary>
		public new Matrix World
		{
			get
			{
				return Matrix.CreateScale(_linkedcamera.FarPlaneDistance - 1) * Matrix.CreateTranslation(_linkedcamera.Position);
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
			drawCube(view, projection);
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
			Shaders.SkyboxShader skybsh = CurrentProject.SkyboxShader;
			for(int i =0; i < 6;i++)
            {
				skybsh.SkyboxTexure = Textures[i];
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
