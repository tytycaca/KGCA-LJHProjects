struct VS_In
{
	float2 p : POS;
	float4 c : COLOR;
	float2 t : TEX;
};
struct VS_Out
{
	float4 p : SV_POSITION;// 반드시 float4
	float4 c  :COLOR0;//COLOR1;
	float2 t  :TEXCOORD0; // ~ TEXCOORD15
};
VS_Out VSMain(VS_In vsIn)
{
	VS_Out  vsOut = (VS_Out)0;
	vsOut.p = float4(vsIn.p.x, vsIn.p.y, 0, 1);
	vsOut.c = vsIn.c;
	vsOut.t = vsIn.t;
	return vsOut;
}

Texture2D g_txTexture : register(t0);
SamplerState sampler0 : register(s0);


struct PS_In
{
	float4 p : SV_POSITION;// 반드시 float4
	float4 c  :COLOR;
	float2 t  :TEXCOORD0;
};
struct PS_Out
{
	float4 c : SV_Target;
};
PS_Out PSMain(PS_In psIn)
{
	PS_Out  psOut = (PS_Out)0;
	float4 pixel = g_txTexture.Sample(sampler0, psIn.t);
	psOut.c = pixel * psIn.c;
	return psOut;
}