/// <summary>
/// �X�v���C�g�p�̃V�F�[�_�[�B
/// </summary>

cbuffer cd : register(b0) {
	float4x4 mvp;	//���[���h�r���[�v���W�F�N�V�����s��
	float4 mulColor;	//��Z�J���[�B
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
	return colorTexture.Sample(Sampler,In.uv) * mulColor;
}
