using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Provides a implementation of C++ std::... functions and classes that are needed.
    /// </summary>
    public static class std
    {
        public static double CopySign(double one,double two)
        {
            return Math.Abs(one) * Sgn(two);
        }
        public static float CopySign_f(float one,float two)
        {
            return (float)Math.Abs(one) * Sgn_f(two);
        }
        /// <summary>
        /// Signum (sign) function. 
        /// Drivate of the f(x) = |x| .
        /// </summary>
        /// <param name="x">Parameter</param>
        /// <returns></returns>
        public static double Sgn(double x)
        {
            if (x == 0) return 0;
            if (x > 0) return 1;
            else return -1;
        }
        public static float Sgn_f(float x)
        {
            if (x == 0) return 0;
            if (x > 0) return 1;
            else return -1;
        }
    }
}
