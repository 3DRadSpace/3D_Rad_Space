struct PosColInput
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

struct PosColOutput
{
	float4 Pos : POSITION;
	float4 Color : COLOR;
};

PosColInput basic_vs(PosColInput inp)
{
	PosColInput o;
	o.Pos = inp.Pos;
	o.Color = inp.Color;

	return o;
}

float4 basic_ps(PosColOutput inp) : SV_Target
{
	return inp.Color;
}