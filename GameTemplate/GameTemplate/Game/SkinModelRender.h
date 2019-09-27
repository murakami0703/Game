#pragma once
/// <summary>
/// 3D���f����\������@�\��񋟂���N���X�B
/// </summary>
class SkinModelRender : public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();
	
	/// <summary>
	/// �������B
	/// </summary>
	void Init();

	/// <summary>
	/// �A�j���[�V�����̍Đ��B
	/// </summary>
	void PlayAnimation();

	/// <summary>
	/// �A�j���[�V�����̏������B
	/// </summary>
	void InitAnimation();

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const CVector3& position)
	{
		m_position = position;
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
	/// �g�嗦��ݒ�B
	/// </summary>
	/// <param name="scl">�g�嗦</param>
	void SetScale(const CVector3& scl)
	{
		m_scale = scl;
	}
	/// <summary>
	/// �X�V�O�ɌĂ΂��֐��B
	/// </summary>
	bool Start();

	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();

private:
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position;			//���W�B
	CQuaternion m_rotation;			//��]�B
	CVector3 m_scale = CVector3().One();			//�g�嗦�B

};

