using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Project class for reading and saving projects.
    /// </summary>
    public class Project
    {
        /// <summary>
        /// Project name
        /// </summary>
        public string Name;
        /// <summary>
        /// If the editor allows the project to be edited.
        /// </summary>
        public bool Writable;
        /// <summary>
        /// Opens a project
        /// </summary>
        /// <param name="filename">File name</param>
        public void Open(string filename)
        {
            byte[] FileBuffer = File.ReadAllBytes(filename);
            if(CheckFormat(FileBuffer) == false) throw new FormatException("The opened file is not a 3DRadSpace project.");
            
        }
        bool CheckFormat(byte[] input)
        {
            string magic = "3DRSP";
            for(int i =0; i < magic.Length;i++)
            {
                if (input[i] != (byte)magic[i]) return false;
            }
            return true;
        }
    }
}
