using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;

namespace Lib3DRadSpace_DX
{
	/// <summary>
	/// Represents the gravitational force vector.
	/// </summary>
	public class GForce : BaseGameObject
	{
		/// <summary>
		/// Defines the Gravitational constant, usually 9.81.
		/// </summary>
		public float GravitationalConstant;

		/// <summary>
		/// Defines the direction of gravity.
		/// </summary>
		public Vector3 Direction;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		/// <param name="enabled"></param>
		/// <param name="dir"></param>
		/// <param name="intensity"></param>
		public GForce(string name="GForce",bool enabled=true,Vector3? dir = null,float intensity=9.81f)
		{
			Vector3 realv = dir ?? Vector3.Up;
			Name = name;
			Enabled = enabled;
			Direction = realv;
			GravitationalConstant = intensity;
		}
		/// <summary>
		/// Draws a vector representing the gravity vector at the center of the world.
		/// </summary>
		/// <param name="time"></param>
		/// <param name="frustrum"></param>
		/// <param name="view"></param>
		/// <param name="projection"></param>
		public override void EditorDraw(GameTime time, BoundingFrustum frustrum, ref Matrix view, ref Matrix projection)
		{
			if(frustrum.Contains(Vector3.Zero) == ContainmentType.Contains)
            {
				//TODO: Draw vector
            }
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
			bool enabled = ByteCodeParser.GetBool(buff, ref position);
			Vector3 dir = ByteCodeParser.GetVector3(buff, ref position);
			float length = ByteCodeParser.GetFloat(buff, ref position);
			result = new GForce(name, enabled, dir, length);
        }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="buff"></param>
        public override void SaveF(List<byte> buff)
        {
			ByteCodeParser.SetString(buff, Name);
			ByteCodeParser.SetBool(buff, Enabled);
			ByteCodeParser.SetVector3(buff, Direction);
			ByteCodeParser.SetFloat(buff, GravitationalConstant);
        }
    }
}
