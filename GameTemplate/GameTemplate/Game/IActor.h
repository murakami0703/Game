#pragma once
class IActor : public IGameObject
{
public:
	IActor();
	~IActor();
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]����ݒ�B
	/// </summary>
	void SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

protected:
	SkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_�[�B
	CVector3 m_position = CVector3().Zero();			//���W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//��]�B
	CVector3 m_scale = CVector3().One();				//�g�嗦�B
};

