#pragma once
#include "IActor.h"

class Golem final : public IActor
{
public:
	Golem();
	~Golem();

	bool Start() override;
	void Update() override;

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
	
	EState m_state = eState_Idle;						//��ԁB
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B

	std::vector<SpriteRender*> m_spriteRender;			//�X�v���C�g�̓��I�z��B
	SpriteRender* m_hpbarSprite;						////�X�v���C�g�����_�[�B

	//���ʎg�p
	CVector3 m_playerPos = CVector3().Zero();			//�v���C���[�̍��W�B
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B
	int m_timer = 0;	//�^�C�}�[

	//�Ǐ]�֌W
	CVector3 m_move = CVector3().Zero();		//�ړ�

	//�U���֌W
	bool m_isDamageFlag = false;		//�U�����Ƀv���C���[�Ƀ_���[�W�^���܂������H
	int m_attacktimer = 0;				//�U�����p�^�C�}�[

	//HP�����֌W
	int HP = 120;				//����HP
	float m_lifeY = 0.0f;
	bool m_moveGageEndflag = false;	//�Q�[�W�̈ړ��I���܂������H

	//HP�̕\���֌W
	CVector3 m_screenPos = CVector3().Zero();
	CVector3 m_hpBarSetPos = CVector3().Zero();
	CVector3 m_cameraPos = CVector3().Zero();
	CVector3 m_hpSpritePos = CVector3().Zero();
	CVector3 m_headPos = CVector3().Zero();
	CVector3 m_lifeScale = CVector3().Zero();
	const CVector2 LifePivot = { 1.0f,0.5f };//HP�̊�{
	bool m_damegeFlag = false;
	int m_damageCount = 0;
};

