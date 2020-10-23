#pragma once
#include "character/CharacterController.h"
#include "IActor.h"

class Player  : public IActor
{
public:
	Player();
	~Player();

	bool Start() override;
	void Update() override;

	/// <summary>
	/// �U������
	/// </summary>
	/// <returns>true		�U����</returns>
	const bool Player::GetAttackflag() {
		return attackflag;
	}

	//�C���X�^���X�̎擾
	static Player* GetInstance() {
		return m_instance;
	}
private:

	//��ԁB
	enum EState {
		Player_Idle,		//�ҋ@
		Player_Walk,		//����
		Player_Attack,		//�U��
		Player_Damage,		//�_���[�W
		Player_Dead			//��
	};

	//�A�j���[�V�����B
	enum PAnimation {
		Animation_Idel,
		Animation_Walk,
		Animation_Run,
		Animation_Drink,
		Animation_Attack,
		Animation_Damage,
		AnimationClip_Num
	};
private:
	static Player* m_instance;

	void Idel();		//�ҋ@�B
	void Move();		//�ړ��B
	void Attack();		//�U���B
	void ItemUse();		//�A�C�e���g�p�B
	void Damage();		//�_���[�W�󂯂܂����B
	void Dead();		//���S�B

private:
	CVector3 m_move = CVector3().Zero();				//�ړ��ʁB
	EState m_state = Player_Idle;						//��ԁB
	CharacterController m_characon;					//�L�����R��
	AnimationClip m_animClips[AnimationClip_Num];	//�A�j���[�V�����N���b�v

	//Animation�֘A
	int m_Atcount = 0;			//�U���񐔔���p�B

	//�U���֘A
	bool attackflag = false;	//�U������p�B

	//HP
	float m_nowHP = 0;			//���݂�HP�i�[�ɁB
	int m_damageTimer = 0;		//�_���[�W���Ɍ��点��Ƃ��Ɏg���^�C�}�[�B

};

