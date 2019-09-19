#pragma once

/// <summary>
/// 3D���f���`��N���X�B
/// </summary>
class C3DModelDraw
{
	//�萔�o�b�t�@�B
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
	};

	std::unique_ptr<DirectX::Model>		m_modelDx;				//DirectXTK���񋟂��郂�f���B
	ID3D11Buffer*		m_cb = nullptr;						//!<�萔�o�b�t�@�B
	ID3D11SamplerState* m_samplerState = nullptr;			//!<�T���v���[�X�e�[�g�B
	ID3D11ShaderResourceView* m_albedoTextureSRV = nullptr;	//!<�A���x�h�e�N�X�`����SRV

public:
	~C3DModelDraw();

	void Init();//������
	void InitAlbedoTexture();	//�A���x�h�e�N�X�`�����������B
	void InitSamplerState();	//�T���v���X�e�[�g�̏������B
	void InitConstantBuffer();	//�萔�o�b�t�@�̏������B
	void Update();				//�X�V�B
	void Draw();				//�`�揈���B


};

