using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using Microsoft.Xna.Framework;

#pragma warning disable IDE1006 // Naming Styles
namespace Lib3DRadSpace_DX
{
    /// <summary>
    /// This is the class containing replicas of the old functions just like in the original 3D Rad engine.
    /// </summary>
    public static class Scripting
    {
        /*
         *  OBJECT FUNCTIONS
         */

        /// <summary>
        /// Starts or triggers the specified object.
        /// </summary>
        /// <param name="id"></param>

        public static void iObjectStart(int id)
        {
            CurrentProject.GameObjects[id].Trigger();
        }
        /// <summary>
        /// Stops the specified object from executing it's update logic loop.
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectStop(int id)
        {
            CurrentProject.GameObjects[id].Enabled = false;
        }
        /// <summary>
        /// Switch the specified object (starts if stopped, and vice-versa). This affects the updating cycle.
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectSwitch(int id)
        {
            CurrentProject.GameObjects[id].Enabled = !(CurrentProject.GameObjects[id].Enabled);
        }
        /// <summary>
        /// Shows the specified object by allowing it in the draw cycle.
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectShow(int id)
        {
            CurrentProject.GameObjects[id].Visible = true;
        }
        /// <summary>
        /// Hides the object, by stopping it from being draw in the drawing cycle.
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectHide(int id)
        {
            CurrentProject.GameObjects[id].Visible = false;
        }
        /// <summary>
        /// Switches the object's visibility
        /// </summary>
        /// <param name="id"></param>
        public static void iObjectShowHideSwitch(int id)
        {
            CurrentProject.GameObjects[id].Visible = !CurrentProject.GameObjects[id].Visible;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        [ObsoleteAttribute("This is not implemented. Using this will always throw a NotImplementedException")]
        public static void iObjectReset(int id)
        {
            //???
            //How the heck are we even going to store the initial object values? Who wants an exta copy of an array?
            throw new NotImplementedException("iObjectReset is not implemented because there's a need for an extra array containinig the project data. ImPleMeNT iT yOUrSeLF");
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="q"></param>
        public static void iObjectOrientation(int id, out Quaternion q)
        {
            q = CurrentProject.GameObjects[id].Rotation;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="q"></param>
        public static void iObjectOrientationSet(int id,Quaternion q)
        {
            CurrentProject.GameObjects[id].Rotation = q;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="q"></param>
        [ObsoleteAttribute("Resetting objects won't be implemented in 0.1.0a. This will only set the quaternion.")]
        public static void iObjectOrientationReset(int id,Quaternion q)
        {
            CurrentProject.GameObjects[id].Rotation = q;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="loc"></param>
        public static void iObjectLocation(int id, out Vector3 loc)
        {
            loc = CurrentProject.GameObjects[id].Position;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="pos"></param>
        public static void iObjectLocationSet(int id,Vector3 pos)
        {
            CurrentProject.GameObjects[id].Position = pos;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="pos"></param>
        [ObsoleteAttribute("Resetting objects is not implemented. This will only set the object's position.")]
        public static void iObjectLocationReset(int id, Vector3 pos)
        {
            CurrentProject.GameObjects[id].Position = pos;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="q"></param>
        /// <param name="pos"></param>
        [ObsoleteAttribute("Resetting objects is not implemented. This will only set the object's position plus rotation.")]
        public static void iObjectPositionReset(int id,Quaternion q,Vector3 pos)
        {
            CurrentProject.GameObjects[id].Rotation = q;
            CurrentProject.GameObjects[id].Position = pos;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="scale"></param>
        public static void iObjectScaleSet(int id,int scale)
        {
            CurrentProject.GameObjects[id].Scale = new Vector3(scale,scale,scale);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="s"></param>
        public static void iObjectScaleSet(int id,Vector3 s)
        {
            CurrentProject.GameObjects[id].Scale = s;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="scale"></param>
        public static void iObjectScale(int id, out Vector3 scale)
        {
            scale = CurrentProject.GameObjects[id].Scale;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public static float iObjectKmh(int id)
        {
            //TODO: Determine speed for dynamic rigicbodies and FPVCameras. Do the physics interface check. Return 0 if not.
            return 0;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="vel"></param>
        public static void iObjectVelocity(int id,out Vector3 vel)
        {
            vel = Vector3.Zero;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="vel"></param>
        public static void iObjectVelocitySet(int id,Vector3 vel)
        {
            ((IPhysicsObject)CurrentProject.GameObjects[id]).ApplyForce(Vector3.Normalize(vel),Physics.ForceType.Acceleration,vel.Length()); //check for comillation errors as this is written inside a browser lel       
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="id"></param>
        /// <param name="speen"></param>
        public static void iObjectSpin(int id,out Vector3 speen)
        {
            
            speen = Vector3.Zero;
        }
        ///
        public static void iObjectSpinSet(int id,Vector3 spin)
        { 
            ((IPhysicsObject)CurrentProject.GameObjects[id]).ApplyForce(Vector3.Normalize(spin),Physics.ForceType.Spin,spin.Length());
        }
    }
}
