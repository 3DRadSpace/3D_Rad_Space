using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Bounding objects types.
    /// </summary>
    public enum BoundingObject
    {
        /// <summary>
        /// Not defined.
        /// </summary>
        None,
        /// <summary>
        /// AABB collision-type box
        /// </summary>
        Box,
        /// <summary>
        /// A 3D Sphere
        /// </summary>
        Sphere,
        /// <summary>
        /// A 3D Plane
        /// </summary>
        Plane,
    }

    /// <summary>
    /// Event raised when a `collision` is happening.
    /// </summary>
    /// <param name="sender">Always a EOL (EventOnLocation) </param>
    /// <param name="boundingObject">Type of the bounding object</param>
    /// <param name="Object_Inside">Object inside.</param>
    public delegate void OnBoundingObjectEnter(EventOnLocation sender, BoundingObject boundingObject, GameObject Object_Inside);
    /// <summary>
    /// Allows raising events when a object is within the specified bounding object.
    /// </summary>
    public class EventOnLocation : GameObject
    {
        /// <summary>
        /// Empty EventOnLocation constructor.
        /// </summary>
        public EventOnLocation()
        {
            Name = "EventOnLocation";
            Enabled = false;

            BoundingSphere = new BoundingSphere(Vector3.Zero, 0);
            BoundingBox = new BoundingBox(Vector3.Zero, Vector3.Zero);
            BoundingPlane = new Plane(Vector4.Zero);
            BoundingType = BoundingObject.None;
            Behiavours = new List<OpcodeEvent.OpCodeCall>();
        }
        /// <summary>
        /// Creates a EventOnLocation based on the given Microsoft.Xna.Framework.BoundingBox/
        /// </summary>
        /// <param name="name">Name of the object</param>
        /// <param name="enabled">Checks if the collisoin events will be raised.</param>
        /// <param name="visible_editor">Checks if the object is visible in the editor</param>
        /// <param name="box">Bounding box.</param>
        public EventOnLocation(string name, bool enabled, bool visible_editor, BoundingBox box)
        {
            Name = name;
            Enabled = enabled;
            VisibleInEditor = visible_editor;
            BoundingBox = box;
            BoundingType = BoundingObject.Box;
            BoundingSphere = BoundingSphere.CreateFromBoundingBox(box);
            BoundingPlane = new Plane(Vector4.Zero);
            Behiavours = new List<OpcodeEvent.OpCodeCall>();
        }
        /// <summary>
        /// Creates a EventOnLocation based on the given BoundingSphere
        /// </summary>
        /// <param name="name">Name of the object</param>
        /// <param name="enabled">Checks if the collisoin events will be raised.</param>
        /// <param name="visible_editor">Checks if the object is visible in the editor</param>
        /// <param name="sphere">Bounding sphere.</param>
        public EventOnLocation(string name, bool enabled, bool visible_editor, BoundingSphere sphere)
        {
            Name = name;
            Enabled = enabled;
            VisibleInEditor = visible_editor;
            BoundingBox = BoundingBox.CreateFromSphere(sphere);
            BoundingType = BoundingObject.Sphere;
            BoundingSphere = sphere;
            BoundingPlane = new Plane(Vector4.Zero);
        }
        /// <summary> 
        /// Creates a EventOnLocation based on the given Plane
        /// </summary>
        /// <param name="name">Name of the object</param>
        /// <param name="enabled">Checks if the collisoin events will be raised.</param>
        /// <param name="visible_editor">Checks if the object is visible in the editor</param>
        /// <param name="plane">Bounding plane</param>
        public EventOnLocation(string name, bool enabled, bool visible_editor, Plane plane)
        {
            Name = name;
            Enabled = enabled;
            VisibleInEditor = visible_editor;
            BoundingBox = new BoundingBox(Vector3.Zero, Vector3.Zero);
            BoundingType = BoundingObject.Plane;
            BoundingSphere = new BoundingSphere(Vector3.Zero, 0);
            BoundingPlane = plane;
        }

        /// <summary>
        /// Raised when a object is inside the bounding object.
        /// </summary>
        public event OnBoundingObjectEnter OnObjectInside;

        /// <summary>
        /// Sets the bounding type for the detection.
        /// </summary>
        public BoundingObject BoundingType;

        /// <summary>
        /// Bounding sphere.
        /// </summary>
        public BoundingSphere BoundingSphere;
        /// <summary>
        /// Bounding box.
        /// </summary>
        public BoundingBox BoundingBox;

        /// <summary>
        /// Plane made up of
        /// </summary>
        public Plane BoundingPlane;
        /// <summary>
        /// A list containing the objects that are being detected by the box.
        /// </summary>
        public List<int> ColidingObjects;

        /// <summary>
        /// If yes, shows a green box marking the bounding zone.
        /// </summary>
        public bool VisibleInEditor;

        /// <summary>
        /// A green transparent cube used to mark the bounding cube in the editor.
        /// </summary>
        public static Model Cube;
        /// <summary>
        /// A green trransparent sphere used to mark the bounding sphere in the editor.
        /// </summary>
        public static Model Sphere;

        /// <summary>
        /// The event defined in the editor.
        /// </summary>
        public new List<OpcodeEvent.OpCodeCall> Behiavours;

        /// <summary>
        /// Editor only - Loads the models used to mark the bounding volume
        /// </summary>
        /// <param name="content"></param>
        public static void LoadModels(ContentManager content)
        {
            Cube = content.Load<Model>("EOL_Cube");
            Sphere = content.Load<Model>("EOL_Sphere");
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="mouse"></param>
        /// <param name="keyboard"></param>
        /// <param name="time"></param>
        public override void Update(MouseState mouse, KeyboardState keyboard, GameTime time)
        {
            switch (BoundingType)
            {
                case BoundingObject.Box:
                    {
                        for (int i = 0; i < ColidingObjects.Count; i++)
                        {
                            GameObject obj = Game.GameObjects[ColidingObjects[i]];
                            if (obj is Skinmesh skinmesh)
                            {
                                for (int j = 0; j < skinmesh.Model.Meshes.Count; i++)
                                {
                                    if (skinmesh.Model.Meshes[j].BoundingSphere.Intersects(BoundingBox))
                                    {
                                        OnObjectInside?.Invoke(this, BoundingObject.Box, skinmesh);
                                        OpcodeEvent.OpCodeCall.Run(Behiavours);
                                    }
                                }
                            }
                            else
                            {
                                if (BoundingBox.Contains(obj.Position) == ContainmentType.Contains)
                                {
                                    OnObjectInside?.Invoke(this, BoundingType, obj);
                                    OpcodeEvent.OpCodeCall.Run(Behiavours);
                                }
                            }
                        }
                        break;
                    }
                case BoundingObject.Sphere:
                    {
                        for (int i = 0; i < ColidingObjects.Count; i++)
                        {
                            GameObject obj = Game.GameObjects[ColidingObjects[i]];
                            if (obj is Skinmesh skinmesh)
                            {
                                for (int j = 0; j < skinmesh.Model.Meshes.Count; i++)
                                {
                                    if (skinmesh.Model.Meshes[j].BoundingSphere.Intersects(BoundingSphere))
                                    {
                                        OnObjectInside?.Invoke(this, BoundingObject.Box, skinmesh);
                                        OpcodeEvent.OpCodeCall.Run(Behiavours);
                                    }
                                }
                            }
                            else
                            {
                                if (BoundingSphere.Contains(obj.Position) == ContainmentType.Contains)
                                {
                                    OnObjectInside?.Invoke(this, BoundingType, obj);
                                    OpcodeEvent.OpCodeCall.Run(Behiavours);
                                }
                            }
                        }
                        break;
                    }
                case BoundingObject.Plane:
                    {
                        for (int i = 0; i < ColidingObjects.Count; i++)
                        {
                            GameObject obj = Game.GameObjects[ColidingObjects[i]];
                            if (obj is Skinmesh skinmesh)
                            {
                                for (int j = 0; j < skinmesh.Model.Meshes.Count; i++)
                                {
                                    if (skinmesh.Model.Meshes[j].BoundingSphere.Intersects(BoundingPlane) == PlaneIntersectionType.Intersecting)
                                    {
                                        OnObjectInside?.Invoke(this, BoundingObject.Box, skinmesh);
                                        OpcodeEvent.OpCodeCall.Run(Behiavours);
                                    }
                                }
                            }
                            else
                            {
                                if (BoundingPlane.Intersects(new BoundingSphere(obj.Position, 1)) == PlaneIntersectionType.Intersecting)
                                {
                                    OnObjectInside?.Invoke(this, BoundingType, obj);
                                    OpcodeEvent.OpCodeCall.Run(Behiavours);
                                }
                            }
                        }
                        break;
                    }
                default: break;
            }
            base.Update(mouse, keyboard, time);
        }
        /// <summary>
        /// Marks the bounding area in the editor.
        /// </summary>
        /// <param name="spriteBatch">Not used.</param>
        /// <param name="view">View Matrix.</param>
        /// <param name="projection">Projection Matrix.</param>
        public override void EditorDraw(SpriteBatch spriteBatch, Matrix? view, Matrix? projection)
        {
            if (VisibleInEditor)
            {
                if (BoundingType == BoundingObject.Box)
                {
                    Vector3 Size = BoundingBox.Max - BoundingBox.Min;
                    Matrix translation = Matrix.CreateScale(Size) * Matrix.CreateTranslation(BoundingBox.Min);
                    Game.DrawModelAlpha(Cube, translation, view.Value, projection.Value,0.5f, false);
                }
                if (BoundingType == BoundingObject.Sphere)
                {
                    Matrix translation = Matrix.CreateScale(BoundingSphere.Radius) * Matrix.CreateTranslation(BoundingSphere.Center);
                    Game.DrawModelAlpha(Sphere, translation, view.Value, projection.Value, 0.5f, false);
                }
                if (BoundingType == BoundingObject.Plane)
                {
                    Vector3 Size = new Vector3(1000, 0.1f, 1000);
                    Vector3 Rotation = new Vector3(BoundingPlane.Normal.X, BoundingPlane.Normal.Y, BoundingPlane.Normal.Z);
                    Matrix translation = Matrix.CreateScale(Size) * Matrix.CreateTranslation(Rotation*BoundingPlane.D);
                    Game.DrawModelAlpha(Cube, translation, view.Value, projection.Value, 0.5f, false);
                }
                base.EditorDraw(spriteBatch, view, projection);
            }
        }
        /// <summary>
        /// Loads the sphere and box markings.
        /// </summary>
        /// <param name="content"></param>
        public override void Load(ContentManager content)
        {
            Cube = content.Load<Model>("EOL_Cube");
            Sphere = content.Load<Model>("EOL_Sphere");
            base.Load(content);
        }
    }
}
