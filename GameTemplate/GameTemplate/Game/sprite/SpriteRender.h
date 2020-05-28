#pragma once
class SpriteRender : public IGameObject
{
	/// <summary>
	/// �X�v���C�g�����_���[
	/// </summary>
	
	void Update();
	void PostRender();
public:
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
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// ���W���擾�B
	/// </summary>
	/// <returns></returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	/// <param name="rotation">��]</param>
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// ��]���擾�B
	/// </summary>
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// �g�嗦��ݒ�B
	/// </summary>
	/// <param name="scl">�g�嗦</param>
	void SetScale(const CVector3& scl)
	{
		m_scale = scl;
	}
	/// <summary>
	/// �g�嗦���擾�B
	/// </summary>
	/// <returns></returns>
	const CVector3& GetScale() const
	{
		return m_scale;
	}
	/// <summary>
	/// ��Z�J���[��ݒ�B
	/// </summary>
	/// <param name="mulColor">��Z�J���[</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_sprite.SetMulColor(mulColor);
	}
	/// <summary>
	/// ��Z�J���[���擾
	/// </summary>
	/// <returns>��Z�J���[</returns>
	CVector4 GetMulColor()
	{
		return m_sprite.GetMulColor();
	}

	/// <summary>
	/// a�l�̐ݒ�
	/// </summary>
	void SetAlpha(const float& alpha)
	{
		m_sprite.SetAlpha(alpha);
	}
	/// <summary>
	/// a�l���擾
	/// </summary>
	float GetAlpha()
	{
		return m_sprite.GetAlpha();
	}


private:
	Sprite	m_sprite;				//�X�v���C�g�B
	CVector3 m_position = CVector3().Zero();			//���W
	CQuaternion m_rotation = CQuaternion().Identity();	//��]
	CVector3 m_scale = CVector3().One();			//�g�嗦�B
	CVector2 m_pivot = { 0.5f,0.5f };	// �s�{�b�g�B

};

