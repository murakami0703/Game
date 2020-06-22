#pragma once
#include "character/CharacterController.h"

class Player  : public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	/// <summary>
	/// �v���C���[�̃|�W�V������Ԃ��֐��B
	/// </summary>
	/// <returns>���W</returns>
	CVector3 Player::GetPosition() {
		return m_position;
	}
	/// <summary>
	/// �U������
	/// </summary>
	/// <returns>true		�U����</returns>
	bool Player::GetAttackflag() {
		return attackflag;
	}

	//�C���X�^���X�̎擾
	static Player* GetInstance() {
		return m_instance;
	}
private:

	enum EState {
		Player_Idle,
		Player_Walk,
		Player_Attack,
		Player_Dead,
		Player_Damage
	};

	enum PAnimation {
		Animation_Idel,
		Animation_Walk,
		Animation_Attack1,
		Animation_Attack2,
		Animation_Dead,
		AnimationClip_Num
	};
private:
	static Player* m_instance;
	void Idel();
	void Move();						//�ړ��B
	void Attack();
	void Dead();

	void Damage();				//�_���[�W�󂯂܂����B

private:
	SkinModelRender* m_skinModelRender = nullptr;				//�X�L�����f�������_�[�B
	CVector3 m_position = CVector3().Zero();			//���W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//��]�B
	CVector3 m_scale = CVector3().One();				//�g�嗦�B

	CVector3 m_move = CVector3().Zero();				//�ړ��ʁB
	EState m_state = Player_Idle;					//��ԁB

	CharacterController m_characon;		//�L�����R��
	AnimationClip m_animClips[AnimationClip_Num];	//�A�j���[�V�����N���b�v

	//�ړ��֘A
	float m_movespeed = 800.0f;			//�ړ����x
	const float m_rotationLR = 80.0f;		//���E�̉�]�p�x
	const float m_rotationD = 110.0f;		//���̉�]�p�x
	float m_caraTime = (1.0f / 60.0f);		//�L�����R���̌o�ߎ���
	const float m_jumpPos = 50.0f;			//�W�����v�̍���

	//Animation�֘A
	int Atcount = 0;								//�U���񐔔���p�B

	//�U���֘A
	bool attackflag = false;	//�U������p�B
	//�T�E���h�֌W
	CSoundSource m_se;						//se�B

	//HP
	float m_nowHP = 0;
	int m_damageTimer = 0;
	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;
	ID3D11ShaderResourceView* g_specularMapSRV = nullptr;
	ID3D11ShaderResourceView* g_ambientMapSRV = nullptr;
};

