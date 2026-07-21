using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lib3DRadSpace_DX
{
    /*
     *  ScriptBlocks is the visual scripting language that is in 3DRadSpace.
     *  It is going to support Scratch-like coding. It's already internally implemented as actions inside the EventOn<??> objects.
     */
    namespace ScriptBlocks
    {
        /// <summary>
        /// Defines an operation code, an identifier for operations and or functions in the ScriptBlocks language.
        /// </summary>
        public enum Opcode
        {
            /// <summary>
            /// No operation.
            /// </summary>
            NOP,
            /// <summary>
            /// Enables or triggers object.
            /// Argument: OBJ_ID (Object index)
            /// </summary>
            StartObject,
            /// <summary>
            /// Stops an object.
            /// </summary>
            StopObject,
            /// <summary>
            /// Switches the on state of an object.
            /// </summary>
            SwitchObject,
            /// <summary>
            /// Makes an object visible
            /// </summary>
            ShowObject,
            /// <summary>
            /// Hides an object.
            /// </summary>
            HideObject,
            /// <summary>
            /// Switches the visibility of an object.
            /// </summary>
            SwitchObjectVisibility,
            /// <summary>
            /// Starts the object, forces an update cycle, then stops the object.
            /// </summary>
            RunObjectOnce,
            /// <summary>
            /// Sets object position
            /// </summary>
            SetPos,
            /// <summary>
            /// Increases object position.
            /// </summary>
            AddPos,
            /// <summary>
            /// Sets object Euler rotation.
            /// </summary>
            SetRot,
            /// <summary>
            /// Increases the object's Euler rotation angles.
            /// </summary>
            AddRot,
            /// <summary>
            /// Sets the object's scale.
            /// </summary>
            SetScale,
            /// <summary>
            /// Increases the object's scale.
            /// </summary>
            AddScale,
        }
    }
}
