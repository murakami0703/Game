#pragma once
class Golem : public IGameObject
{
public:
	Golem();
	~Golem();

	bool Start();
	void Update();

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void Golem::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void Golem::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]����ݒ�B
	/// </summary>
	void Golem::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

private:
	//��ԁB
	enum EState {
		eState_Idle,		//�ҋ@�B
		eState_Follow,		//�v���C���[��ǐՁB
		eState_Attack,		//�U���B
		eState_Back,		//����߂��B
		eState_Damage,		//�_���[�W��B
		eState_Dead			//���B
	};
	//�A�j���[�V�����B
	enum EAnimationClip {
		eAnimation_Idle,
		eAnimation_Walk,
		eAnimation_Attack,
		eAnimation_Back,
		eAnimation_Damage,
		eAnimation_Death,
		eAnimation_Num
	};

private:
	void Idle();		//�ҋ@�B
	void Follow();		//�v���C���[��ǐՁB
	void Attack();		//�U���B
	void Back();		//����߂��B
	void Damage();		//�_���[�W��B
	void Dead();		//���B

	void MoveHPGage();	//HP�Q�[�W�̈ړ��B
	void HPBarSaid();	//HP�o�[�̕\�������B
private:
	SkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_�[�B
	CVector3 m_position = CVector3().Zero();			//���W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//��]�B
	CVector3 m_scale = CVector3().One();				//�g�嗦�B
	EState m_state = eState_Idle;						//��ԁB
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B

	std::vector<SpriteRender*> m_spriteRender;			//�X�v���C�g�̓��I�z��B
	SpriteRender* m_hpbarSprite;						////�X�v���C�g�����_�[�B

	//���ʎg�p
	CVector3 m_playerPos = CVector3().Zero();			//�v���C���[�̍��W�B
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B
	int m_timer = 0;	//�^�C�}�[
	//�ҋ@�֌W
	const float m_idleTime = 120.0f;	//�x�e���ԁB
	//�Ǐ]�֌W
	CVector3 m_move = CVector3().Zero();		//�ړ�
	//�U���֌W
	const float m_damageLen = 300.0f;	//�_���[�W����̋���
	bool m_isDamageFlag = false;		//�U�����Ƀv���C���[�Ƀ_���[�W�^���܂������H
	int m_attacktimer = 0;				//�U�����p�^�C�}�[
	const int m_attackEndTime = 60;	//�U����ԏI���^�C��

	//�_���[�W�֌W
	const float m_damageLength = 250.0f;	//�_���[�W���󂯂鋗���B
	const int SUB_HP = 40;		//����������HP�̒l�B

	//HPPP
	int HP = 120;				//����HP
	const int MAX_HP = 120;		//�ő�HP
	float m_lifeY = 0.0f;
	bool m_moveGageEndflag = false;	//�Q�[�W�̈ړ��I���܂������H

	CVector3 screenPos = CVector3().Zero();
	CVector3 hoge = CVector3().Zero();
	CVector3 cameraPos = CVector3().Zero();
	CVector3 Pos = CVector3().Zero();
	CVector3 atamaNoPos = CVector3().Zero();
	CVector3 LifeScale = CVector3().Zero();
	const CVector2 LifePivot = { 1.0f,0.5f };//HP�̊�{
	bool m_damegeFlag = false;
	int count = 0;
};

