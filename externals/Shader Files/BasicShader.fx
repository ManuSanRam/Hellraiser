cbuffer World
{
	float4x4 World;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

VS_OUTPUT VS(float4 inPos : POSITION, float4 inColor : COLOR)
{
	VS_OUTPUT Output;
	Output.Pos = inPos;
	Output.Color = inColor;

	return Output;
}

float4 PS(VS_OUTPUT Input) : SV_TARGET
{
	return Input.Color;
}