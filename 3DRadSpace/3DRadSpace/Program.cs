using System;

namespace _3DRadSpace
{
#if WINDOWS || LINUX
    /// <summary>
    /// The main class.
    /// </summary>
    public static class Program
    {
        [STAThread]
        static void Main(string[] Arguments) //Command line arguments
        {
            using (var Editor = new Editor())
            {
                Editor.Run();
            }
        }
    }
#endif
}
