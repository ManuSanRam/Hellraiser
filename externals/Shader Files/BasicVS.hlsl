cbuffer World : register (b0)
{
	float4x4 World;
};

cbuffer View : register (b1)
{
	float4x4 View;
};

cbuffer Proj : register (b2)
{
	float4x4 Proj;
};

struct VS_INPUT
{
	float3	Position	:	POSITION;
	float4	Color		:	COLOR;
};

struct VS_OUTPUT
{
	float4	Position	:	SV_POSITION;
	float4	Color		:	COLOR;
};

VS_OUTPUT VSMain(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.Position = mul(float4(Input.Position.xyz, 1.0f), World);
	Output.Position = mul(Output.Position, View);
	Output.Position = mul(Output.Position, Proj);

	//Output.Position = float4(Input.Position.xyz, 1.0f);

	Output.Color =		Input.Color;

	return Output;
}



struct PS_INPUT
{
	float4  Position	:	SV_POSITION;
	float4	Color		:	COLOR;
};

float4 PSMain(PS_INPUT Input) : SV_TARGET
{
	return Input.Color;
}