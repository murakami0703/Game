#pragma once
class DirectionLight
{
	/// <summary>
	/// �f�B���N�V�������C�g
	/// </summary>
	struct SDirectionLight {
		CVector4 direction;		//���C�g�̕����B
		CVector4 color;			//���C�g�̃J���[�B
	};
	ID3D11Buffer*		m_lightCb = nullptr;				//!<���C�g�p�̒萔�o�b�t�@�B
	SDirectionLight		m_dirLight;							//!<�f�B���N�V�������C�g�B
	
public:
	~DirectionLight();
	void Init();				//�������B
	void InitDirectionLight();	//�f�B���N�V�������C�g�̏������B
	void InitConstantBuffer();	//�萔�o�b�t�@�̏�����
	void Update();				//�X�V�B
	void Draw();				//�`��B
};

