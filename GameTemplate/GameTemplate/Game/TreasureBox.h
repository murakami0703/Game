#pragma once
class TreasureBox : public IGameObject
{
public:
	TreasureBox();
	~TreasureBox();

	bool Start();
	void Update(); //�X�V�B

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void TreasureBox::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void TreasureBox::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]����ݒ�B
	/// </summary>
	void TreasureBox::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}
private:
	void Open();
	void HpRecovery();
	void Bum();
	void AttackUp();
	void SpeedUp();

	void OnlyDelete();

	enum eState {
		eState_Idle,
		eState_Open,
		eState_HpRecovery,
		eState_Bum,
		eState_AttackUp,
		eState_SpeedUp
	};
	enum EAnimationClip {
		eAnimation_Close,
		eAnimation_Open,
		eAnimation_Num
	};
private:
	SkinModelRender* m_BoxModelRender;				//�󔠃X�L�����f�������_�[�B
	SkinModelRender* m_ItemModelRender;				//�A�C�e���X�L�����f�������_�[�B

	CVector3 m_position = CVector3().Zero();			//���W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//��]�B
	CVector3 m_scale = CVector3().One();				//�g�嗦�B

	eState m_state = eState_Idle;
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B

	//�J���֘A
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���[���[�Ɣ��̃x�N�g���B
	const float m_openYVec = 30.0f;						//�J���p�����B
	const int m_randNum[4] = { 0,1,2,3 };				//�J���p�����B
	int m_rand = 0;										//�����_�����̊i�[�B

};
