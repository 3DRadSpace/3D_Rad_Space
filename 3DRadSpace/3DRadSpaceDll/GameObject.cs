using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

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
            OnInitialization(this);
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
        public virtual void Load()
        {
            OnObjectLoad(this);
        }
        /// <summary>
        /// Unloads the resource.
        /// </summary>
        public virtual void Free()
        {
            OnObjectUnload(this);
        }

        /// <summary>
        /// Object Drawing code
        /// </summary>
        public virtual void Draw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            OnDraw(this, spriteBatch, view, projection);
        }
        /// <summary>
        /// Object draw code for the 3DRadSpace editor
        /// </summary>
        public virtual void EditorDraw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {

        }
        /// <summary>
        /// Object update logic
        /// </summary>
        public virtual void Update()
        {
            OnUpdate(this, null, null, null);
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
            OnRemoval(this);
        }
    }
}
