using System;
using Microsoft.Xna.Framework;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// 
    /// </summary>
    internal static class Maths
    {
        /// <summary>
        /// Scales the first vector with the second vector.
        /// </summary>
        /// <param name="a">First vector</param>
        /// <param name="b">Second vector</param>
        /// <returns></returns>
        internal static Vector3 MultiplyScale(Vector3 a,Vector3 b)
        {
            return new Vector3(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
        }
        /// <summary>
        /// CopySign double floating precision implementation
        /// </summary>
        /// <param name="a">Magnitude number</param>
        /// <param name="b">Sign number</param>
        /// <returns></returns>
        internal static double CopySign(double a, double b)
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
        internal static float CopySign(float a, float b)
        {
            if(b < 0) return Math.Abs(a);
            else return -Math.Abs(a);
        }
        /// <summary>
        /// Signum (sign function) implementation.
        /// </summary>
        /// <param name="x"></param>
        /// <returns></returns>
        internal static int Sgn(float x)
        {
            if(x > 0) return 1;
            if(x < 0) return -1;
            else return 0;
        }
        /// <summary>
        /// Converts a Quaternion to a Euler angle vector with radian angles.
        /// </summary>
        /// <param name="q"></param>
        /// <returns></returns>
        internal static Vector3 QuaternionToVector3(Quaternion q)
        {
            Vector3 angles;
            // roll (x-axis rotation)
            double sinr_cosp = 2 * (q.W * q.X + q.Y * q.Z);
            double cosr_cosp = 1 - 2 * (q.X * q.X + q.Y * q.Y);
            angles.X = (float)Math.Atan2(sinr_cosp, cosr_cosp);

            // pitch (y-axis rotation)
            double sinp = 2 * (q.W * q.Y - q.Z * q.X);
            if(Math.Abs(sinp) >= 1)
                angles.Y = (float)CopySign(MathHelper.Pi / 2, sinp); // use 90 degrees if out of range
            else
                angles.Y = (float)Math.Asin(sinp);

            // yaw (z-axis rotation)
            double siny_cosp = 2 * (q.W * q.Z + q.X * q.Y);
            double cosy_cosp = 1 - 2 * (q.Y * q.Y + q.Z * q.Z);
            angles.Z = (float)Math.Atan2(siny_cosp, cosy_cosp);

            return angles;
        }
    }
}
