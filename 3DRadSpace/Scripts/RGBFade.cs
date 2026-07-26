using Engine3DRadSpace;
using Engine3DRadSpace.Math;
using Engine3DRadSpace.Objects;
using Engine3DRadSpace.Scripting;

class MyClass : Script
{
	SkyColor skycolor;

	public override void Start()
	{
		skycolor = new SkyColor((Object.Parent) as InstIObject).Handle);
		skyColor.Color = new Color(1, 0, 0, 1);
	}
	void RGBFade(ref byte r, ref byte g, ref byte b)
	{
		if(r > 0 && b == 0)
		{
			r--;
			g++;
		}

		if(g > 0 && r == 0)
		{
			g--;
			b++;
		}

		if(b > 0 && g == 0)
		{
			r++;
			b--;
		}
	}

	public override void Update()
	{
		byte r = (byte)(skycolor.Color.R * 255);
		byte g = (byte)(skycolor.Color.G * 255);
		byte b = (byte)(skycolor.Color.B * 255);

		RGBFade(ref r, ref g, ref b);
		skycolor.Color = new Color(r / 255f, g / 255f, b / 255f, 1.0f);
	}
}