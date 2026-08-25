using Engine3DRadSpace;

namespace Engine3DRadSpace_CSharp_Tests
{
    class TestGame : Game
    {
        public TestGame() : base("3DRadSpace C# Sample")
        {
        }

    }

    [TestClass]
	public class GameTests
	{
		[TestMethod]
		public void Run10Frames()
		{
			TestGame game = new TestGame();
			for (int i = 0; i < 10; i++)
			{
				game.RunOneFrame();
			}
		}
	}
}