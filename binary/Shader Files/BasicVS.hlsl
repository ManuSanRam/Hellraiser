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



Texture2D DiffuseTexture: register(t0);
SamplerState DiffuseSampler: register(s0);



struct VS_INPUT
{
	float4	Position	:	POSITION;
	float2	TexCoord	:	TEXCOORD0;
};



struct VS_OUTPUT
{
	float4	Position	:	SV_POSITION;
	float2	TexCoord	:	TEXCOORD0;
};



VS_OUTPUT VSMain(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.Position = mul(float4(Input.Position.xyz, 1.0f), World);
	Output.Position = mul(Output.Position, View);
	Output.Position = mul(Output.Position, Proj);

	Output.TexCoord = Input.TexCoord;

	return Output;
}



struct PS_INPUT
{
	float4  Position    :   SV_POSITION;
	float2	TexCoord	:	TEXCOORD0;
};



float4 PSMain(PS_INPUT Input) : SV_TARGET
{
	return (float4(1.0f, 0.0f, 0.0f, 0.0f));
}