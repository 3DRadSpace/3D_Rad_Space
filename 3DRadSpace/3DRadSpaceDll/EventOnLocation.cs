using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Bounding objects types.
    /// </summary>
    public enum BoundingObject
    {
        /// <summary>
        /// AAABBB box
        /// </summary>
        Box, 
        /// <summary>
        /// A 3D Sphere
        /// </summary>
        Sphere,
    }

    /// <summary>
    /// Event raised when a `collision` is happening.
    /// </summary>
    /// <param name="sender">Always a EOL (EventOnLocation) </param>
    /// <param name="boundingObject">Type of the bounding object</param>
    /// <param name="Object_Inside">Object inside.</param>
    public delegate void OnBoundingObjectEnter(object sender, BoundingObject boundingObject, GameObject Object_Inside);
    /// <summary>
    /// Allows raising events when a object is within the specified bounding object.
    /// </summary>
    public class EventOnLocation : GameObject
    {
        /// <summary>
        /// Empty EventOnLocation constructor.
        /// </summary>
        EventOnLocation()
        {

        }
        /// <summary>
        /// Raised when a object is inside the bounding object.
        /// </summary>
        public event OnBoundingObjectEnter OnObjectInside;
        /// <summary>
        /// 
        /// </summary>
        /// <param name="mouse"></param>
        /// <param name="keyboard"></param>
        /// <param name="time"></param>
        public override void Update(MouseState mouse, KeyboardState keyboard, GameTime time)
        {
            base.Update(mouse, keyboard, time);
        }
    }
}
