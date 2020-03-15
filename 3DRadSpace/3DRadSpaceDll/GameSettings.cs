using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Represents game's settings like fullscreen, framerate, resolution.
    /// </summary>
    public class GameSettings
    {
        /// <summary>
        /// Represents the resolution.
        /// </summary>
        public Point GameScreen;
        /// <summary>
        /// Represents the maximum frames per second values.
        /// </summary>
        public int MaximumFramerate;
        /// <summary>
        /// Toggles fullscreen mode.
        /// </summary>
        public bool Fullscreen;
        /// <summary>
        /// Empty GameSettings constructor.
        /// </summary>
        public GameSettings()
        {
            GameScreen = new Point(600, 480);
            MaximumFramerate = 60;
            Fullscreen = false;
        }
        /// <summary>
        /// Main GameSettings constructor.
        /// </summary>
        /// <param name="resolution"></param>
        /// <param name="fps"></param>
        /// <param name="full"></param>
        public GameSettings(Point resolution,int fps,bool full)
        {
            GameScreen = resolution;
            MaximumFramerate = fps;
            Fullscreen = full;
        }
        /// <summary>
        /// Returns a string representing the settings.
        /// </summary>
        /// <returns>A string containing the values.</returns>
        public override string ToString()
        {
            return GameScreen.X + " " + GameScreen.Y + ' ' + MaximumFramerate + ' ' + Fullscreen;
        }
    }
}
