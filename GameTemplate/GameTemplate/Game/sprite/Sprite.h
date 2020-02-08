#pragma once
#include "graphics/Shader.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="texFilePath">�e�N�X�`���̃t�@�C���p�X</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	void Init(const wchar_t* texFilePath, float w, float h);
	/// <summary>
	/// �e�N�X�`����SRV���w�肵�ď������B
	/// </summary>
	/// <param name="srv"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void Init(ID3D11ShaderResourceView* srv, float w, float h);

	/// <summary>
	/// �X�V�B
	/// </summary>
	/// <param name="pos">���s�ړ�</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g��</param>
	/// <param name="pivot">��_</param>
	/// <remarks>
	///		0.5, 0.5�ŉ摜�̒��S����_�B
	/// </remarks>
	void Update(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });
	//�`��B
	void Draw();
	/// <summary>
	/// ��Z�J���[��ݒ�
	/// </summary>
	/// <param name="mulColor">��Z�J���[</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_mulColor = mulColor;
	}
	/// <summary>
	/// ��Z�J���[���擾
	/// </summary>
	/// <returns>��Z�J���[</returns>
	CVector4 GetMulColor()
	{
		return m_mulColor;
	}

	/// <summary>
	/// a�l�̐ݒ�
	/// </summary>
	void SetAlpha(const float& alpha)
	{
		m_alpha = alpha;
	}
	/// <summary>
	/// a�l���擾
	/// </summary>
	float GetAlpha()
	{
		return m_alpha;
	}

	/// <summary>
	/// ���l��ψʂ�����
	/// </summary>
	/// <param name="delta">��Z����ψʂ������</param>
	void DeltaAlpha(float delta)
	{
		m_alpha += delta;
		//���l�̋��E�`�F�b�N�B
		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;
		}
		else if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}
	}

	/// <summary>
	/// �u�����h�X�e�[�g���擾�B
	/// </summary>
	/// <returns></returns>
	ID3D11BlendState* GetID3D11BlendState()
	{
		return m_translucentBlendState;
	}

	/// <summary>
	/// �\���̐ݒ�
	/// </summary>
	/// <param name="flag">false(��\��)</param>
	/// <param name="flag">true(�\��)</param>
	void SetActiveFlag(bool& flag)
	{
		m_activeFlag = flag;
	}


	struct ConstantBuffer {
		CMatrix WVP;		//���[���h�r���[�v���W�F�N�V�����s��B
		CVector4 mulColor;	//��Z�J���[�B
		float alpha;		//���l�B
	};
	ID3D11Buffer*				m_vertexBuffer = NULL;					//���_�o�b�t�@�B
	ID3D11Buffer*				m_indexBuffer = NULL;					//�C���f�b�N�X�o�b�t�@�B
	Shader						m_ps;							//!<�s�N�Z���V�F�[�_�[�B
	Shader						m_vs;							//!<���_�V�F�[�_�[�B
	ID3D11ShaderResourceView*	m_texture = NULL;						//�e�N�X�`���B
	ID3D11SamplerState*			m_samplerState = NULL;					//�T���v���X�e�[�g�B
	CVector3					m_position = CVector3::Zero();			//���W�B
	CQuaternion					m_rotation = CQuaternion::Identity();	//��]
	CVector3					m_scale = CVector3::One();				//�g�嗦
	CVector4					m_mulColor = {1.0f, 1.0f, 1.0f, 1.0f};	//��Z�J���[�B
	CMatrix						m_world = CMatrix::Identity();			//���[���h�s��B
	CVector2					m_size = CVector2::Zero();				//�摜�̃T�C�Y�B
	ID3D11Buffer*				m_cb = nullptr;							//�萔�o�b�t�@�B
	bool						m_isInited = false;				//!<�������t���O�B
	float						m_alpha = 1.0f;							//�X�v���C�g�̃��l�B
	ID3D11BlendState* m_translucentBlendState = nullptr;	//�����������p�̃u�����h�X�e�[�g�B
	bool						m_activeFlag = true;				//�\�����܂����H

private:
	/*!
	 *@brief	�萔�o�b�t�@�̏������B
	 */
	void InitConstantBuffer();
	/// <summary>
	/// �������̋��ʏ����B
	/// </summary>
	void InitCommon(float w, float h);

	/// <summary>
	/// �u�����h�X�e�[�g�̏�����
	/// </summary>
	void InitTranslucentBlendState();

};

