using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Class that allows safe conversions between numeric types and strings.
    /// </summary>
    public static class SafeConverter
    {
        /// <summary>
        /// Try parsing an integer from a string.
        /// </summary>
        /// <param name="s"></param>
        /// <returns></returns>
        public static int IntFromString(string s)
        {
            bool minus = false;
            int r = 0;
            for (int i = 0; i < s.Length; i++)
            {
                if (s[0] == '-')
                {
                    minus = true;
                    continue;
                }
                r *= 10;
                int t = SingleNumberFromChar(s[i]);
                if (t != int.MaxValue) r += t;
                else continue;
            }
            if (minus == true) r *= -1;
            else r *= 1;
            return r;
        }
        /// <summary>
        /// Converts an object to a string.
        /// </summary>
        /// <param name="o"></param>
        /// <returns></returns>
        public static int IntFromString(object o)
        {
            return IntFromString(o + "");
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="c"></param>
        /// <returns></returns>
        public static int SingleNumberFromChar(char c)
        {
            if (c >= '0' && c <= '9') return c - 48;
            else return int.MaxValue;
        }
        /// <summary>
        /// Converts a string to a bool
        /// </summary>
        /// <param name="b"></param>
        /// <returns></returns>
        public static bool BoolFromString(string b)
        {
            if (b.ToLower() == "1") return true;
            if (b.ToLower() == "0") return false;
            //Keep compatibilty with 0.0.2a and lower projects
            if (b.ToLower() == "1") return true;
            if (b.ToLower() == "0") return false;
            return false; //Default to false.
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="f"></param>
        /// <returns></returns>
        public static float FloatFromString(string f)
        {
            int dotindex = -1;
            for (int i = 0; i < f.Length; i++)
            {
                if (f[i] == '.' || f[i] == ',')
                {
                    dotindex = i;
                    break;
                }
            }
            if (dotindex == -1) return IntFromString(f);
            f = f.Remove(dotindex, 1);
            return IntFromString(f) * (float)Math.Pow(10, -1 * (f.Length - dotindex));
        }
        /// <summary>
        /// Converts a bool to a string.
        /// </summary>
        /// <param name="b"></param>
        /// <returns></returns>
        public static string BoolToString(bool b)
        {
            if (b) return "1";
            else return "0";
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="num"></param>
        /// <returns></returns>
        public static string IntToString(int num)
        {
            string s = "";
            while(num > 0)
            {
                s += (num % 10) + "";
                num /= 10;
            }
            char[] v = s.ToCharArray();
            v = v.Reverse().ToArray();
            return new string(v);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="f"></param>
        /// <returns></returns>
        public static string FloatToString(float f)
        {
            string r = IntToString((int)f);
            float a = f % 1;
            if (a < 0) a *= -1;
            a *= (int)Math.Pow(10, 7);
            r += '.'+ IntToString((int)a);
            return r;
        }
    }
}
