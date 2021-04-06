using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// 
    /// </summary>
    public static class Maths
    {
        /// <summary>
        /// Scales the first vector with the second vector.
        /// </summary>
        /// <param name="a">First vector</param>
        /// <param name="b">Second vector</param>
        /// <returns></returns>
        public static Vector3 MultiplyScale(Vector3 a,Vector3 b)
        {
            return new Vector3(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
        }
        /// <summary>
        /// CopySign double floating precision implementation
        /// </summary>
        /// <param name="a">Magnitude number</param>
        /// <param name="b">Sign number</param>
        /// <returns></returns>
        public static double CopySign(double a, double b)
        {
            if(b < 0) return Math.Abs(a);
            else return -Math.Abs(a);
        }
        /// <summary>
        /// CopySign float implementation
        /// </summary>
        /// <param name="a">Magnitude number</param>
        /// <param name="b">Sign number</param>
        /// <returns></returns>
        public static float CopySign(float a, float b)
        {
            if(b < 0) return Math.Abs(a);
            else return -Math.Abs(a);
        }
        /// <summary>
        /// Signum (sign function) implementation.
        /// </summary>
        /// <param name="x"></param>
        /// <returns></returns>
        public static int Sgn(float x)
        {
            if(x > 0) return 1;
            if(x < 0) return -1;
            else return 0;
        }
    }
}
