using Microsoft.Xna.Framework;

namespace _3DRadSpaceDll
{
	/// <summary>
	/// Allows loading other projects.
	/// </summary>
	public class ExitFade : GameObject
	{
		/// <summary>
		/// Main constructor of ExitFade class.
		/// </summary>
		/// <param name="name">Name of the object.</param>
		/// <param name="Path">Project to load.</param>
		/// <param name="Fade">Fade Color.</param>
		/// <param name="fadetime">Fade Time. Defaults to 0.</param>
		public ExitFade(string name, string Path, Color Fade,int fadetime=0)
		{
			Name = name;
			Resource = Path;

		}

		/// <summary>
		/// Project path.
		/// </summary>
		public string ProjectToLoad { get; set; }

		/// <summary>
		/// Fade color.
		/// </summary>
		public Color Fade { get; set; }

		/// <summary>
		/// Time for the fade in milliseconds (ms)
		/// </summary>
		public int Time { get; set; }

		/// <summary>
		/// When starting the object in the editor events, or scripts, this will get called.
		/// </summary>
		public override void Trigger()
		{
			Project.UnloadObjects();
			Game.GameObjects = Project.Open(ProjectToLoad);
			base.Trigger();
		}
		/// <summary>
		/// Enables/disables the object.
		/// <para>In this case, since this object is 'triggerable', </para>
		/// </summary>
		public new bool Enabled
		{
			get
			{
				return _enabled;
			}
			set
			{
				_enabled = value;
				if(value) Trigger();
			}
		}
		bool _enabled;
	}
}
