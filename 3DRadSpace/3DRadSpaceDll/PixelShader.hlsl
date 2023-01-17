
float4x4 Transform;

struct VInput
{
	float4 Position : SV_Position;
	float2 UV : TEXCOORD0;
};

struct VOutput
{
	float4 Position : SV_Position;
	float2 UV : TEXCOORD0;
};

Texture2D Texture : register(t0);

sampler TextureSampler = sampler_state
{
	Texture = <Texture>;
	MagFilter = Linear;
	MinFilter = Linear;
	AddressU = Clamp;
	AddressV = Clamp;
};

VOutput VS_Main(VInput vi)
{
	VOutput o;
	o.Position = mul(vi.Position, Transform);
	o.UV = vi.UV;
	return o;
}

float4 PS_Main(VOutput v) : SV_TARGET
{
	return Texture.Sample(TextureSampler,v.UV);
}