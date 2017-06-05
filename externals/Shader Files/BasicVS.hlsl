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

	Output.Position = float4(Input.Position.xyz, 1.0f);
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