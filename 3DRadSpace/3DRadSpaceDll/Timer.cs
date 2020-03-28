using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Raised everytime the timer exceeds the period.
    /// </summary>
    /// <param name="sender">Timer object.</param>
    /// <param name="total_time">Total time passed since the creation of the timer object.</param>
    public delegate void TimerEvent(Timer sender, uint total_time);
    /// <summary>
    /// Executes an event everytime a 'period' passes for a number of times.
    /// </summary>
    public class Timer : GameObject
    {
        /// <summary>
        /// Empty Timer constructor.
        /// </summary>
        public Timer()
        {
            Name = "Timer";
            Enabled = false;
            Period = 0;
            Repetitions = 0;
            TotalTime = 0;
            Behiavours = new ActionScript.OpCodeCall[0];
        }
        /// <summary>
        /// Main Timer constructor.
        /// </summary>
        /// <param name="name">Name of the object.</param>
        /// <param name="enabled">If the timer will execute.</param>
        /// <param name="period">Timer period.</param>
        /// <param name="repetitions">How much time the event will execute. Use <seealso cref="uint.MaxValue"/> to represent ∞ . </param>
        public Timer(string name,bool enabled,uint period,uint repetitions)
        {
            Name = name;
            Enabled = enabled;
            Period = period;
            Repetitions = repetitions;
            Behiavours = new ActionScript.OpCodeCall[0];
        }
        uint _time;
        /// <summary>
        /// Defined the time in milliseconds between the timer event executions.
        /// </summary>
        public uint Period;
        /// <summary>
        /// Defines how many times the event will get called.
        /// <para> Use <seealso cref="uint.MaxValue"/> or <seealso cref="Infinity"/> to represent ∞ (infinity) </para>
        /// </summary>
        public uint Repetitions;
        /// <summary>
        /// Counts the time passed.
        /// <para>Maximum value is <seealso cref="Period"/> * <seealso cref="Repetitions"/></para>
        /// <para>NOTE: Unsigned integer overflows will occur if the Period is a value representing ∞ (<seealso cref="uint.MaxValue"/>)</para>
        /// </summary>
        public uint TotalTime { get; private set; }
        /// <summary>
        /// Raised everytime a repetition is complete.
        /// </summary>
        public event TimerEvent OnTimerRepetition;
        /// <summary>
        /// Represents ∞
        /// </summary>
        public const uint Infinity = uint.MaxValue;

        /// <summary>
        /// The event defined in the editor.
        /// </summary>
        public new ActionScript.OpCodeCall[] Behiavours;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="mouse"></param>
        /// <param name="keyboard"></param>
        /// <param name="time"></param>
        public override void Update(MouseState mouse, KeyboardState keyboard, GameTime time)
        {
            if (Enabled)
            {
                TotalTime += (uint)time.ElapsedGameTime.TotalMilliseconds;
                _time += (uint)time.ElapsedGameTime.TotalMilliseconds;
                if(_time >= Period)
                {
                    OnTimerRepetition?.Invoke(this, TotalTime);
                    ActionScript.OpCodeCall.Run(Behiavours);
                    _time = 0;
                }
                base.Update(mouse, keyboard, time);
            }
        }
    }
}
