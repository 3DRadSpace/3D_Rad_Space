using System;

namespace _3DRadSpace_Player_DX
{
    public static class Program
    {
        [STAThread]
        static void Main()
        {
            using(var game = new Game1())
                game.Run();
        }
    }
}
