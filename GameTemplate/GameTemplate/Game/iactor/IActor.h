#pragma once
/// <summary>
/// �A�N�^�[�N���X
/// </summary>
/// <remarks>
/// ���̃N���X�͑����̃Q�[���L�����N�^�[�ŕK�v�ɂȂ郁���o�ϐ��A�֐����܂Ƃ߂��N���X�ł��B
/// �v���C���[�Ȃǂ̃N���X�͂��̃N���X���p�����Ă��܂��B
/// </remarks>
class IActor : public IGameObject
{
public:
	IActor();
	~IActor();

	/// <summary>
	/// ���W���擾�B
	/// </summary>
	CVector3 GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void SetPosition(const CVector3 pos) 
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	CQuaternion GetRotation() const
	{
		return m_rotation;
	}

	/// <summary>
	/// ��]����ݒ�B
	/// </summary>
	void SetScale(const CVector3 sca)
	{
		m_scale = sca;
	}
	/// <summary>
	/// �A�N�^�[�̑O�������Ǝw�肳�ꂽ�I�u�W�F�N�g�Ƃ̊p�x���v�Z���܂��B
	/// </summary>
	/// <param name="angle">�p�x�̊i�[��</param>
	/// <param name="distance">�����̊i�[��</param>
	/// <param name="actorForward">�A�N�^�[�̑O������</param>
	/// <param name="toObject">�I�u�W�F�N�g�܂ł̋���</param>
	void CalcAngleAndLength(float& angle, float& distance, const CVector3& actorForward, const CVector3& toObject);
protected:
	SkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_�[�B
	CVector3 m_position = CVector3::One();				//���W�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	CVector3 m_scale = CVector3::One();				//�g�嗦�B
};

