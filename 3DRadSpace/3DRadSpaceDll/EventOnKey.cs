using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework;
using _3DRadSpaceDll.OpcodeEvent;

namespace _3DRadSpaceDll
{
	/// <summary>
	/// Defines the input states.
	/// </summary>
	public enum KeyInputType
	{
		/// <summary>
		/// The key is up.
		/// </summary>
		Released=0,
		/// <summary>
		/// The key is being pressed.
		/// </summary>
		Pressed,
		/// <summary>
		/// The key is being pressed for one than one frame.
		/// </summary>
		Holding
	}
	/// <summary>
	/// Input key used for the EventOnKey and related objects.
	/// </summary>
	public struct KeyInput
	{
		/// <summary>
		/// Main constructor of KeyInput
		/// </summary>
		/// <param name="key">Specified keyboard button.</param>
		/// <param name="state">Specified state.</param>
		public KeyInput(Keys key= Keys.None, KeyInputType state= KeyInputType.Released)
		{
			Key = key;
			State = state;
		}
		/// <summary>
		/// The key
		/// </summary>
		public Keys Key;
		/// <summary>
		/// The key state.
		/// </summary>
		public KeyInputType State;
	}
	/// <summary>
	/// Triggers when the key is up/down/ hold for enough time.
	/// </summary>
	/// <param name="sender">EOK sender.</param>
	/// <param name="delta">DeltaTime.</param>
	public delegate void KeyEvent(EventOnKey sender,GameTime delta);
	/// <summary>
	/// Triggers when the key is being pressed and when the <seealso cref="EventOnKey.Key"/>.State is equal to <seealso cref="KeyInputType.Holding"/>
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="Time"></param>
	/// <param name="deltaTime"></param>
	public delegate void OnKeyHold(EventOnKey sender, uint Time, GameTime deltaTime);
	/// <summary>
	/// Allows raising events whenever a key is being pressed.
	/// </summary>
	public class EventOnKey : GameObject
	{
		/// <summary>
		/// Empty EOK constructor.
		/// </summary>
		public EventOnKey()
		{
			Name = "EventOnKey";
			Enabled = false;
			Key = new KeyInput(Keys.None, KeyInputType.Holding);
			HoldingTime = uint.MaxValue;
			Behiavours = new List<OpCodeCall>();
		}
		/// <summary>
		/// Main EOK constructor.
		/// </summary>
		/// <param name="name">Object Name.</param>
		/// <param name="enabled">Will the event get raised?</param>
		/// <param name="input">Defines the key and input type.</param>
		/// <param name="time_necesarry">Time necessary for holding down the button in order to trigger the button.</param>
		public EventOnKey(string name,bool enabled, KeyInput input,uint time_necesarry=0)
		{
			Name = name;
			Enabled = enabled;
			Key = input;
			HoldingTime = time_necesarry;
			Behiavours = new List<OpCodeCall>();
		}
		/// <summary>
		/// Defines the key and the expected key state.
		/// </summary>
		public KeyInput Key;
		/// <summary>
		/// Defined the time in milliseconds how much time is needed to hold down the given key to trigger the event.
		/// </summary>
		public uint HoldingTime
		{
			get
			{
				return _time;
			}
			set
			{
				if(value == 0)
				{
					Key.State = KeyInputType.Pressed;
				}
				_time = value;
			}
		}
		uint _time = 0;
		/// <summary>
		/// Defnes how much time the button is being hold.
		/// </summary>
		public uint TotalHoldTime { get; private set; }

		/// <summary>
		/// The event defined in the editor.
		/// </summary>
		public new List<OpCodeCall> Behiavours;

		/// <summary>
		/// Triggers when the inputs are equal to the given conditions.
		/// </summary>
		event KeyEvent OnKeyTrigger;
		/// <summary>
		/// Triggers when the key is being hold.
		/// </summary>
		event OnKeyHold OnKeyHolding;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="mouse"></param>
		/// <param name="keyboard"></param>
		/// <param name="time"></param>
		public override void Update(MouseState mouse, KeyboardState keyboard, GameTime time)
		{
			if (Key.State == KeyInputType.Released && keyboard.IsKeyUp(Key.Key))
			{
				OpCodeCall.Run(Behiavours);
				OnKeyTrigger?.Invoke(this, time);
			}
			if (Key.State == KeyInputType.Pressed && keyboard.IsKeyDown(Key.Key))
			{
				OpCodeCall.Run(Behiavours);
				OnKeyTrigger?.Invoke(this, time);
			}
			if (Key.State == KeyInputType.Holding)
			{
				if (keyboard.IsKeyDown(Key.Key))
				{
					TotalHoldTime += (uint)time.ElapsedGameTime.TotalMilliseconds;
					OnKeyHolding?.Invoke(this, TotalHoldTime, time);
					if (TotalHoldTime >= HoldingTime)
					{
						TotalHoldTime = 0;
						OnKeyTrigger?.Invoke(this, time);
						OpCodeCall.Run(Behiavours);
					}
				}
				else TotalHoldTime = 0;
			}
			base.Update(mouse, keyboard, time);
		}
	}
}
