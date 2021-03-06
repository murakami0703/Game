/// <summary>
/// スプライト用のシェーダー。
/// </summary>

cbuffer cd : register(b0) {
	float4x4 mvp;	//ワールドビュープロジェクション行列
	float4 mulColor;	//乗算カラー。
	float alpha;		//α値。
};
struct VSInput {
	float4 pos : SV_Position;
	float2 uv : TEXCOORDO;
};

struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORDO;
};

Texture2D<float4> colorTexture : register(t0);
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) {
	PSInput psIn;
	psIn.pos = mul(mvp, In.pos);
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain(PSInput In) : SV_Target0
{
	float4 texColor = colorTexture.Sample(Sampler,In.uv);
	//乗算カラー
	texColor = texColor * mulColor;
	//CPUから転送されたα値を使用。
	texColor.a *= alpha;
	return texColor;
}
