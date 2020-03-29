using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Input;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Allows playing sounds located in a 3D envoirement. 
    /// </summary>
    public class SoundSource : SoundEffect
    {
        /// <summary>
        /// Empty SoundSource constructor.
        /// </summary>
        public SoundSource()
        {
            Name = "SoundSource";
            Enabled = false;
            Resource = null;
            Volume = 0f;
            _cam = null;
        }
        /// <summary>
        /// Main SoundSource constructor.
        /// </summary>
        /// <param name="name">Object Name.</param>
        /// <param name="enabled">Is playing sounds allowed?</param>
        /// <param name="resource">Resource file</param>
        /// <param name="volume">Volume ranging from 0.0 to 1.0</param>
        /// <param name="position">Sound source position.</param>
        /// <param name="listener">Camera used as a listener.</param>
        /// <param name="pitch">Sound pitch ranging from -1.0f to 1.0f</param>
        /// <param name="pan">Headphones balance, ranging from -1.0f to 1.0f</param>
        /// <param name="doppler">Doppler effect scale.</param>
        public SoundSource(string name, bool enabled, string resource, float volume, Vector3 position, Camera listener, float pitch = 0f,float pan = 0f,float doppler = 1f)
        {
            Name = name;
            Enabled = enabled;
            Resource = resource;
            Volume = volume;
            Pitch = pitch;
            Pan = pan;
            if (listener == null)
            {
                SetListenerPosition(Vector3.Zero, Vector3.Up);
            }
            else
            {
                Position = position;
                _cam = listener;
            }
            DopplerScale = doppler;
        }
        /// <summary>
        /// Defines the Sound's location.
        /// </summary>
        public new Vector3 Position
        {
            get
            {
                return _pos;
            }
            set
            {
                _pos = value;
                if (SoundInstance != null)
                {
                    AudioListener listener = new AudioListener();
                    listener.Forward = Vector3.Forward;
                    if (LinkedCam != null)
                    {
                        listener.Up = LinkedCam.CameraRotation;
                        listener.Position = LinkedCam.Position;
                    }
                    //We assume the listener's position is Vector3.Zero
                    else
                    {
                        listener.Up = Vector3.Up;
                        listener.Position = Vector3.Zero;
                    }
                    AudioEmitter emitter = new AudioEmitter();
                    emitter.Up = Vector3.Up;
                    emitter.Forward = Vector3.Forward;
                    emitter.DopplerScale = DopplerScale;
                    SoundInstance.Apply3D(listener, emitter);
                }
            }
        }
        Vector3 _pos;
        /// <summary>
        /// Gets or set a scale applied to the doppler effect between the listener(<seealso cref="LinkedCam"/>LinkedCam) and the sound source (<seealso cref="Position"/>)
        /// </summary>
        public float DopplerScale
        {
            get
            {
                return _doppler;
            }
            set
            {
                Position = Position;
                _doppler = value;
            }
        }
        float _doppler;
        /// <summary>
        /// Camera object used as listener.
        /// </summary>
        public Camera LinkedCam
        {
            get
            {
                return _cam;
            }
            set
            {
                if (value != null)
                {
                    Position = Position;
                    _cam = value;
                }
                else SetListenerPosition(Vector3.Zero, Vector3.Up);
            }
        }
        Camera _cam;
        /// <summary>
        /// Sets the listener's position.
        /// </summary>
        /// <param name="pos">Position.</param>
        /// <param name="up">Up normalized vector.</param>
        public void SetListenerPosition(Vector3 pos,Vector3 up)
        {
            _cam = new Camera();
            _cam.Position = pos;
            _cam.CameraRotation = up;
        }
    }
}
