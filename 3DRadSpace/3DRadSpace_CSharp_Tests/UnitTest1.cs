using Engine3DRadSpace;

namespace Engine3DRadSpace_CSharp_Tests
{
	[TestClass]
	public class UnitTest1
	{
		[TestMethod]
		public void TestMethod1()
		{
			GraphicsDevice device = new GraphicsDevice(IntPtr.Zero, 800, 600);
			device.Dispose();

			Assert.AreEqual(1, 1);
		}
	}
}