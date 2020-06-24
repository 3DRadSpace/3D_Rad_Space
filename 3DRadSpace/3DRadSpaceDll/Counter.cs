using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Microsoft.Xna.Framework.Content;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// 
    /// </summary>
    public class Counter : GameObject
    {
        /// <summary>
        /// The value this object was initialized with.
        /// </summary>
        public float InitialValue
        {
            get
            {
                return _initialv;
            }
        }
        float _initialv;
        /// <summary>
        /// Stored value.
        /// </summary>
        public float Value;
        /// <summary>
        /// Increment value. (can be negative)
        /// </summary>
        public float Increment;
        /// <summary>
        /// File to get the value saved.
        /// </summary>
        public string File;
        /// <summary>
        /// Empty constructor.
        /// </summary>
        public Counter()
        {
            File = null;
            Increment = 1;
            Value = 0;
            _initialv = 0;
        }
        /// <summary>
        /// Main constructor.
        /// </summary>
        /// <param name="name">Object name</param>
        /// <param name="enabled">Can this object `trigger`?</param>
        /// <param name="increment">Addidion value. Negatives are also allowed.</param>
        /// <param name="initialv">Start value.</param>
        /// <param name="file">File to save the stored value.</param>
        public Counter(string name,bool enabled,float increment=1,float initialv=0,string file=null)
        {
            Name = name;
            Enabled = true;
            Increment = increment;
            Value = initialv;
            File = file;
            _initialv = initialv;
        }
        /// <summary>
        /// Constructor for use if loading from a file.
        /// </summary>
        /// <param name="name">Object name</param>
        /// <param name="enabled">Can this object get triggered?</param>
        /// <param name="increment">Increment value</param>
        /// <param name="f">File</param>
        public Counter(string name,bool enabled, float increment,string f)
        {
            Name = name;
            Enabled = enabled;
            Increment = increment;
            _initialv = int.MinValue; // Unkwnown, let's use a confusing value.
            File = f;
        }
        /// <summary>
        /// Constrcuctor allowing setting a private value.
        /// </summary>
        /// <param name="i">Initial</param>
        public Counter(float i)
        {
            _initialv = i;
            Value = i;
            Increment = 1;
            Name = "Counter";
            Enabled = true;
        }
        /// <summary>
        /// Saves the stored value into the specified file.
        /// </summary>
        public void SaveFile()
        {
            if(File != null) System.IO.File.WriteAllText(File, Value+"");
        }
        /// <summary>
        /// Used only in 3DRadSpacePlayer.
        /// </summary>
        /// <param name="content"></param>
        public override void Load(ContentManager content)
        {
            LoadFile();
            base.Load(content);
        }
        /// <summary>
        /// Loads the saved number from the specified file.
        /// </summary>
        public void LoadFile()
        {
            if (File != null) Value = Convert.ToSingle(System.IO.File.ReadAllText(File), Main.CultureInfo);
        }
        /// <summary>
        /// Increment the value.
        /// </summary>
        public override void Trigger()
        {
            Value += Increment;
            base.Trigger();
        }
        /// <summary>
        /// Only used in 3DRad editor IO
        /// </summary>
        public string FileIOSafe
        {
            get
            {
                if (File != null) return File;
                else return ""+(char)0; // <-- forbidden linux character
            }
        }
    }
}
