cbuffer Data : register(b0)
{
    row_major matrix matWorldViewProj; // MVP transformation
	uint ObjectID;
}

struct VertexIn
{
    float3 Position : POSITION;
    float4 Color : COLOR;
};

struct VertexOut
{
    float4 Position : SV_Position;
    float4 Color : COLOR;
};

VertexOut VS_Main(VertexIn v)
{
    VertexOut r;
    r.Position = mul(float4(v.Position.xyz,1), matWorldViewProj);
    r.Color = v.Color;
    return r;
}

struct PSOutput
{
	float4 Color : SV_Target0;
	uint ID : SV_Target1;
}

PSOutput PS_Main(VertexOut v)
{
	PSOutput output;
    output.Color = v.Color;
	output.ID = ObjectID;
	return output;
}