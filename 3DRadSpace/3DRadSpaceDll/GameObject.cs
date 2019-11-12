using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Content;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Called when drawing the object
    /// </summary>
    /// <param name="drawn">The drawn object. Conversion will be needed.</param>
    /// <param name="spriteBatch">SpriteBatch used for drawing 2D objects</param>
    /// <param name="view">View Matrix used for 3D model drawing</param>
    /// <param name="projection">Projection Matrix used for 3D model drawing</param>
    public delegate void onDraw(object drawn, SpriteBatch spriteBatch, Matrix? view, Matrix? projection);
    /// <summary>
    /// Called when updating.
    /// </summary>
    /// <param name="updated">The updated object</param>
    /// <param name="mouse">Mouse inputs</param>
    /// <param name="keyboard">Keyboard inputs</param>
    /// <param name="time">Game time input</param>
    public delegate void onUpdate(object updated, MouseState? mouse, KeyboardState? keyboard, GameTime time);
    /// <summary>
    /// Called when a object is being created in the constructor function.
    /// </summary>
    /// <param name="obj">The created object</param>
    public delegate void onObjectCreate(object obj);
    /// <summary>
    /// Called when a object is being removed.
    /// </summary>
    /// <param name="obj">The removed object</param>
    public delegate void onObjectDestroy(object obj);
    /// <summary>
    /// Called when a object resource is being loaded.
    /// </summary>
    /// <param name="obj">Object</param>
    public delegate void onObjectLoad(object obj);
    /// <summary>
    /// Called when a object is being unloaded.
    /// </summary>
    /// <param name="obj">Object to be unloaded</param>
    public delegate void onObjectUnload(object obj);
    
    /// <summary>
    /// Base class for all 3DRadSpace objects.
    /// </summary>
    public class GameObject
    {
        /// <summary>
        /// Default constructor.
        /// </summary>
        public GameObject()
        {
            OnInitialization?.Invoke(this);
        }
        /// <summary>
        /// Object Name
        /// </summary>
        public string Name;
        /// <summary>
        /// Checks if object is enabled.
        /// </summary>
        public bool Enabled;
        /// <summary>
        /// Checks if object is being drawn.
        /// </summary>
        public bool Hidden;
        /// <summary>
        /// Object position
        /// </summary>
        public Vector3 Position;
        /// <summary>
        /// Rotation in a Euler angles system.
        /// </summary>
        public Vector3 Rotation;

        /// <summary>
        /// Relation with other objects
        /// </summary>
        public List<ObjectBehiavour> Behiavours;

        /// <summary>
        /// Rotation in a Quaterion system.
        /// </summary>
        public Quaternion RotationQuaternion
        {
            get =>  Quaternion.CreateFromYawPitchRoll(Rotation.Y, Rotation.X, Rotation.Z);
        }
        /// <summary>
        /// Resource file
        /// </summary>
        public string Resource;
        /// <summary>
        /// Enables object.
        /// </summary>
        public void Enable() { Enabled = true; }
        /// <summary>
        /// Disables object.
        /// </summary>
        public void Disable() { Enabled = false; }
        /// <summary>
        /// Switches object on/off state.
        /// </summary>
        public void Toggle() { Enabled = !Enabled; }
        /// <summary>
        /// Shows the object.
        /// </summary>
        public void Show() { Hidden = false; }
        /// <summary>
        /// Hides the object.
        /// </summary>
        public void Hide() { Hidden = true; }
        /// <summary>
        /// Loads the resource(s).
        /// </summary>
        public virtual void Load(ContentManager content)
        {
            OnObjectLoad?.Invoke(this);
        }
        /// <summary>
        /// Unloads the resource.
        /// </summary>
        public virtual void Free(ContentManager content)
        {
            OnObjectUnload?.Invoke(this);
        }

        /// <summary>
        /// Object Drawing code
        /// </summary>
        public virtual void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            OnDraw?.Invoke(this, spriteBatch, view, projection);
        }
        /// <summary>
        /// Object draw code for the 3DRadSpace editor
        /// </summary>
        public virtual void EditorDraw(SpriteBatch spriteBatch,out Matrix? view,out Matrix? projection)
        {
            view = null;
            projection = null;
        }
        /// <summary>
        /// Object update logic
        /// </summary>
        public virtual void Update(MouseState mouse,KeyboardState keyboard,GameTime time)
        {
            OnUpdate?.Invoke(this, mouse, keyboard, time);
        }
        /// <summary>
        /// Called when object is being drawn on frame.
        /// </summary>
        public event onDraw OnDraw;
        /// <summary>
        /// Called when object is being updated on the update logic loop.
        /// </summary>
        public event onUpdate OnUpdate;
        /// <summary>
        /// Called when object is being created.
        /// </summary>
        public event onObjectCreate OnInitialization;
        /// <summary>
        /// Called when object is being deleted.
        /// </summary>
        public event onObjectDestroy OnRemoval;
        /// <summary>
        /// Called when a object resource is being loaded.
        /// </summary>
        public event onObjectLoad OnObjectLoad;
        /// <summary>
        /// Called when a object resource is being freed from the RAM memory.
        /// </summary>
        public event onObjectUnload OnObjectUnload;

        /// <summary>
        /// Object destructor.
        /// </summary>
        ~GameObject()
        {
            OnRemoval?.Invoke(this);
        }
        /// <summary>
        /// Checks if the object exists. Same as GameObject != null.
        /// </summary>
        /// <param name="o">GameObject to check.</param>
        public static implicit operator bool(GameObject o)
        {
            if (o != null) return true;
            else return false;
        }
        /// <summary>
        /// Returns the object's name
        /// </summary>
        /// <returns>the object's name</returns>
        public override string ToString()
        {
            return Name;
        }
    }
}
