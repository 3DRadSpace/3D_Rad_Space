using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Microsoft.Xna.Framework.Content;

namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// 
    /// </summary>
    public class Counter : BaseGameObject
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <param name="enabled"></param>
        /// <param name="val"></param>
        /// <param name="inc"></param>
        /// <param name="filename"></param>
        public Counter(string name,bool enabled,float val,float inc,string filename)
        {
            Name = name;
            Enabled = enabled;
            Value = val;
            Increment = inc;
            Asset = filename;
        }
        /// <summary>
        /// Counter value.
        /// </summary>
        public float Value;
        /// <summary>
        /// Counter increment value.
        /// </summary>
        public float Increment;

        /// <summary>
        /// If the object will save/load the number in a file if the project is being unloaded or loaded.
        /// </summary>
        public bool SaveToDrive;

        /// <summary>
        /// 'Triggers' the object. Used in the visual scripting interface.
        /// </summary>
        public override void Trigger()
        {
            if(_enabled)
            {
                Value += Increment;
            }
        }
        /// <summary>
        /// 
        /// </summary>
        public new bool Enabled
        { 
            set
            {
                if(value && _enabled)
                {
                    Trigger();
                    return;
                }
                _enabled = value;
            }
            get
            {
                return _enabled;
            }
        }
        bool _enabled;
        /// <summary>
        /// 
        /// </summary>
        public void SaveData()
        {
            File.WriteAllText("//SaveData//" + Asset, Value + "");
        }
        /// <summary>
        /// 
        /// </summary>
        public void LoadData()
        {
            if(SaveToDrive)
            {
                if(File.Exists("//SaveData//" + Asset))
                {
                    string f = File.ReadAllText("//SaveData//" + Asset);
                    Value = Convert.ToSingle(f);
                }
                else SaveData(); //saves the default value.
            }
        }
        /// <summary>
        /// Loads the counter value.
        /// </summary>
        /// <param name="content">unused</param>
        public override void Load(ContentManager content)
        {
            LoadData();
        }
        /// <summary>
        /// Saves the counter value into a file.
        /// </summary>
        public override void Unload()
        {
            SaveData();
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="buff"></param>
        /// <param name="position"></param>
        /// <param name="result"></param>
        public override void LoadF(List<byte> buff, ref int position, out IGameObject result)
        {
            result = null;
        }
    }
}
