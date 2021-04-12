using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace Lib3DRadSpace_DX
{
    static class ByteCodeParser
    {
        //GETTERS

        public static string GetString(byte[] buff,ref int pos)
        {
            string str = "";
            while(buff[pos] != 0)
            {
                str += (char)buff[pos];
                pos++;
            }
            return str;
        }
        public static float GetFloat(byte[] buff,ref int pos)
        {
            pos += sizeof(float);
            return BitConverter.ToSingle(buff, pos-sizeof(float));
        }
        public static int GetInt(byte[] buff,ref int pos)
        {
            pos += sizeof(int);
            return BitConverter.ToInt32(buff, pos-sizeof(int));
        }
        public static bool GetBool(byte[] buff,ref int pos)
        {
            pos += 1;
            return buff[pos - 1] > 0;
        }
        public static Vector3 GetVector3(byte[] buff,ref int pos)
        {
            pos += 3 * sizeof(float);
            return new Vector3(
                BitConverter.ToSingle(buff, pos-(3*sizeof(float))),
                BitConverter.ToSingle(buff, pos-(2*sizeof(float))),
                BitConverter.ToSingle(buff, pos- sizeof(float)));
        }
        public static Vector2 GetVector2(byte[] buff,ref int pos)
        {
            pos += 2 * sizeof(float);
            return new Vector2(
                BitConverter.ToSingle(buff, pos - (2*sizeof(float))),
                BitConverter.ToSingle(buff, pos - sizeof(float)));
        }
        public static Keys GetKey(byte[] buff,ref int pos)
        {
            pos += sizeof(byte);
            return (Keys)buff[pos - 1];
        }


        //SETTERS
        
        public static void SetString(List<byte> buff,string str)
        {
            int l = str.Length;
            for(int i =0; i < l;i++)
            {
                buff.Add((byte)str[i]);
            }
            buff.Add(0);
        }
        public static void SetInt(List<byte> buff, int num)
        {
            buff.AddRange(BitConverter.GetBytes(num));
        }
        public static void SetFloat(List<byte> buff, float flt)
        {
            buff.AddRange(BitConverter.GetBytes(flt));
        }
        public static void SetBool(List<byte> buff,bool b)
        {
            byte r = 0;
            if(b == true) r = 255;
            buff.Add(r);
        }
        public static void SetVector3(List<byte> buff,Vector3 v)
        {
            buff.AddRange(BitConverter.GetBytes(v.X));
            buff.AddRange(BitConverter.GetBytes(v.Y));
            buff.AddRange(BitConverter.GetBytes(v.Z));
        }
        public static void SetVector2(List<byte> buff, Vector2 v)
        {
            buff.AddRange(BitConverter.GetBytes(v.X));
            buff.AddRange(BitConverter.GetBytes(v.Y));
        }
        public static void SetKey(List<byte> buff,Keys k)
        {
            buff.Add((byte)k);
        }
    }
}
