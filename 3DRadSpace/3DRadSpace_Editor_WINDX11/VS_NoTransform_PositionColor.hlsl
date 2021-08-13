struct PosColInput
{
	float4 Pos : POSITION; //input is POS0 and it was set to SV_POS0 in the input layout???
	float4 Color : COLOR;
};

struct PosColOutput
{
	float4 Pos : SV_POSITION; 
	float4 Color : COLOR;
};

PosColOutput basic_vs(PosColInput inp)
{
	PosColOutput o;
	o.Pos = inp.Pos;
	o.Color = inp.Color;

	return o;
}

float4 basic_ps(PosColOutput inp) : SV_Target
{
	return inp.Color;
}