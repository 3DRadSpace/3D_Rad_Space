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
			get { return SoundInstance.Volume; }
			set
			{
				if (value > 1.0f) value = 1.0f;
				if (value < 0.0f) value = 0.0f;
				SoundInstance.Volume = value;
			}
		}
		/// <summary>
		/// Sound pitch. Ranges from -1.0f to 1.0f.
		/// </summary>
		public float Picth
		{
			get { return SoundInstance.Pitch; }
			set { SoundInstance.Pitch = value; }
		}
		/// <summary>
		/// Pan / speaker balance.
		/// </summary>
		public float Pan
		{
			get { return SoundInstance.Pan; }
			set { SoundInstance.Pan = value; }
		}
		/// <summary>
		/// Gets or sets the current state of the sound.
		///<para>Unlike SoundInstance.State, this property can be also set.</para>
		///<para>Setting this property to any value will call the <seealso cref="Play"/>, <seealso cref="Stop"/> and <seealso cref="Pause"/> depinding on the value.</para>
		/// </summary>
		public SoundState SoundState
		{
			get { return SoundInstance.State;  }
			set
			{
				switch(value)
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
		}

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
			SoundInstance.Play();
		}
		/// <summary>
		/// Pauses the sound.
		/// </summary>
		public void Pause()
		{
			SoundInstance.Pause();
		}
		/// <summary>
		/// Stops the sound
		/// </summary>
		public void Stop()
		{
			SoundInstance.Stop();
		}
		/// <summary>
		/// Checks if the sound is playing.
		/// </summary>
		/// <returns></returns>
		public bool IsPlaying()
		{
			return SoundInstance.State == SoundState.Playing;
		}
		/// <summary>
		/// Checks if the sound is paused.
		/// </summary>
		/// <returns></returns>
		public bool IsPaused()
		{
			return SoundInstance.State == SoundState.Paused;
		}
		/// <summary>
		/// Checks if the sound is stopped.
		/// </summary>
		/// <returns></returns>
		public bool IsStopped()
		{
			return SoundInstance.State == SoundState.Stopped;
		}
	}
}
