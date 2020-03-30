using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Audio;

namespace _3DRadSpaceDll
{
	/// <summary>
	/// SoundEffect class. Allows loading and playing sound effects.
	/// </summary>
	public class SoundEffect : GameObject 
	{
		/// <summary>
		/// Sound file. Use <seealso cref="SoundInstance"/> to directly access the <seealso cref="Microsoft.Xna.Framework.Audio.SoundEffect"/>.
		/// </summary>
		public Microsoft.Xna.Framework.Audio.SoundEffect Sound { get; private set; }
		/// <summary>
		/// SoundInstance object. Allows playing the sound.
		/// </summary>
		public SoundEffectInstance SoundInstance { get; set; }
		/// <summary>
		/// Sound volume. Ranges from 0.0f to 1.0f.
		/// </summary>
		public float Volume
		{
			get 
			{
				if (SoundInstance != null) return SoundInstance.Volume;
				else return _volume;
			}
			set
			{
				if (value > 1.0f) value = 1.0f;
				if (value < 0.0f) value = 0.0f;
				if (SoundInstance != null) SoundInstance.Volume = value;
				else _volume = value;
			}
		}
		float _volume;
		/// <summary>
		/// Sound pitch. Ranges from -1.0f to 1.0f.
		/// </summary>
		public float Pitch
		{
			get 
			{
				if (SoundInstance != null) return SoundInstance.Pitch;
				else return _pitch;
			}
			set 
			{
				if (value < -1.0f) value = -1.0f;
				else if (value > 1.0f) value = 1.0f;
				if (SoundInstance != null)SoundInstance.Pitch = value;
				else _pitch = value;
			}
		}
		float _pitch;
		/// <summary>
		/// Pan / speaker balance.
		/// </summary>
		public float Pan
		{
			get 
			{
				if (SoundInstance != null) return SoundInstance.Pan;
				else return _pan;
			}
			set 
			{
				if (value < -1.0f) value = -1.0f;
				else if (value > 1.0f) value = 1.0f;
				if (SoundInstance != null) SoundInstance.Pan = value;
				else _pan = value;
			}
		}
		float _pan;
		/// <summary>
		/// Gets or sets the current state of the sound.
		///<para>Unlike SoundInstance.State, this property can be also set.</para>
		///<para>Setting this property to any value will call the <seealso cref="Play"/>, <seealso cref="Stop"/> and <seealso cref="Pause"/> depinding on the value.</para>
		/// </summary>
		public SoundState SoundState
		{
			get 
			{
				if (SoundInstance != null) return SoundInstance.State;
				else return _soundstate;
			}
			set
			{
				if (SoundInstance != null)
				{
					switch (value)
					{
						case SoundState.Paused:
							{
								Pause();
								break;
							}
						case SoundState.Playing:
							{
								Play();
								break;
							}
						case SoundState.Stopped:
							{
								Stop();
								break;
							}
						default: break;
					}
				}
				else _soundstate = value;
			}
		}
		SoundState _soundstate;

		/// <summary>
		/// Main constructor.
		/// </summary>
		/// <param name="name"></param>
		/// <param name="active"></param>
		/// <param name="resource"></param>
		/// <param name="volume"></param>
		public SoundEffect(string name, bool active, string resource, float volume=1.0f)
		{
			Name = name;
			Enabled = active;
			Resource = resource;
			Volume = volume;
		}
		/// <summary>
		/// Empty SoundEffect constructor.
		/// </summary>
		public SoundEffect()
		{
			Name = "SoundEffect";
			Enabled = false;
			Resource = null;
			Volume = 0f;
		}
		/// <summary>
		/// Loads the sound
		/// </summary>
		/// <param name="content"></param>
		public override void Load(ContentManager content)
		{
			Sound = content.Load<Microsoft.Xna.Framework.Audio.SoundEffect>(Resource);
			SoundInstance = Sound.CreateInstance();
			base.Load(content);
		}
		/// <summary>
		/// Plays the sound.
		/// </summary>
		public void Play()
		{
			if(SoundInstance != null && Enabled) SoundInstance.Play();
		}
		/// <summary>
		/// Pauses the sound.
		/// </summary>
		public void Pause()
		{
			if (SoundInstance != null) SoundInstance.Pause();
		}
		/// <summary>
		/// Stops the sound
		/// </summary>
		public void Stop()
		{
			if (SoundInstance != null) SoundInstance.Stop();
		}
		/// <summary>
		/// Checks if the sound is playing.
		/// </summary>
		/// <returns></returns>
		public bool IsPlaying()
		{
			if (SoundInstance != null) return SoundInstance.State == SoundState.Playing;
			else return false;
		}
		/// <summary>
		/// Checks if the sound is paused.
		/// </summary>
		/// <returns></returns>
		public bool IsPaused()
		{
			if (SoundInstance != null) return SoundInstance.State == SoundState.Paused;
			else return false;
		}
		/// <summary>
		/// Checks if the sound is stopped.
		/// </summary>
		/// <returns></returns>
		public bool IsStopped()
		{
			if (SoundInstance != null) return SoundInstance.State == SoundState.Stopped;
			else return true;
		}
		/// <summary>
		/// Plays the sound.
		/// </summary>
		public override void Trigger()
		{
			base.Trigger();
			Play();
		}
	}
}
