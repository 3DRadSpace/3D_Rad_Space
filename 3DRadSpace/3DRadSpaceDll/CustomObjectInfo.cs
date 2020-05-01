using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Represents information and metadata about the custom object.
    /// </summary>
    [AttributeUsage(AttributeTargets.Class, Inherited = true, AllowMultiple = false)]
    public sealed class CustomObjectInfo : Attribute
    {
        /// <summary>
        /// Constructor of the CustomObjectInfo class.
        /// </summary>
        /// <param name="name">editor name</param>
        /// <param name="creator">author name</param>
        /// <param name="v">version</param>
        public CustomObjectInfo(string name,string creator,float v)
        {
            EditorName = name;
            Author = creator;
            Version = v;
        }
        /// <summary>
        /// Represents the author or the object.
        /// </summary>
        public string Author { get; set; }
        /// <summary>
        /// Represents the version of the object assembly.
        /// </summary>
        public float Version { get; set; }
        /// <summary>
        /// Represents the common name used in the editor.
        /// </summary>
        public string EditorName { get; set; }
    }
}
