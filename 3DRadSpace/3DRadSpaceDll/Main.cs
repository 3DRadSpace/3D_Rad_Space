using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Globalization;

namespace _3DRadSpaceDll
{
    /// <summary>
    /// Global stuff there and over there.
    /// </summary>
    public static class Main
    {
        /// <summary>
        /// Haha, fixes related to computers using other languages
        /// </summary>
        public static CultureInfo CultureInfo { get; } = CultureInfo.InvariantCulture; //An fix for the culture related issues
    }
}
