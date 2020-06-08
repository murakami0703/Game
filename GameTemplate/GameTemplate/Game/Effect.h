#pragma once
class Effect : public IGameObject
{
	/// <summary>
	/// �G�t�F�N�g
	/// </summary>
public:
	Effect();
	~Effect();
	/// <summary>
	/// ����B
	/// </summary>
	void Release();
	/// <summary>
	/// �G�t�F�N�g���Đ��B
	/// </summary>
	/// <param name="filePath">�Đ�����G�t�F�N�g�̃t�@�C���p�X�B</param>
	void Play(const wchar_t* filePath);
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]�̐ݒ�B
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// �g�嗦��ݒ�B
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// �G�t�F�N�g���Đ���������B
	/// </summary>
	bool IsPlay() const
	{
		return g_graphicsEngine->GetEffectEngine().GetEffekseerManager().GetShown(m_handle);
	}
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
private:
	Effekseer::Effect*	m_effect = nullptr;
	Effekseer::Handle	m_handle = -1;
	CVector3 m_position = CVector3().Zero();			//!<���W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//!<��]�B
	CVector3 m_scale = CVector3().One();				//!<�g�嗦�B
};
