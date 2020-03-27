#include "stdafx.h"
#include "Player.h"
#include "ShadowMap.h"
#include "GameData.h"

Player* Player::m_instance = nullptr;

Player::Player()
{
	m_instance = this;

	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animClips[Animation_Idel].Load(L"Assets/animData/eneIdle.tka");
	m_animClips[Animation_Walk].Load(L"Assets/animData/eneWalk.tka");
	m_animClips[Animation_Attack1].Load(L"Assets/animData/eneAT1.tka");
	m_animClips[Animation_Dead].Load(L"Assets/animData/eneDeath.tka");
	//���[�v�t���O�̐ݒ�B
	m_animClips[Animation_Idel].SetLoopFlag(true);
	m_animClips[Animation_Walk].SetLoopFlag(true);
	
	m_model = g_goMgr->NewGameObject<SkinModelRender>();
	m_model->Init(L"Assets/modelData/Footman_Default.cmo");
	//m_position= { 0.0f, 400.0f, 500.0f };
	m_model->SetPosition(m_position);

	m_scale = { 50.0f, 50.0f, 50.0f };
	m_model->SetScale(m_scale);
	m_characon.Init(20.0f, 30.0f, m_position);//�L�����R��
	m_move = m_position;
	m_animation.Init(m_model->GetSkinModel(), m_animClips, AnimationClip_Num);	//�A�j���[�V�����̏�����
	m_model->SetShadowMap(true);
}
Player::~Player()
{
}
void Player::Idel()
{
	//�ҋ@��ԂȂɂ����Ȃ�
	if (g_pad[0].IsPressAnyKey())
	{
		m_state = Player_Walk;
	}

}
void Player::Move()
{
	m_move.x = 0.0f;
	m_move.z = 0.0f;

	//�\���ړ��Ɖ�]�B
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_move.x -= m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), m_rotationLR);

	}
	else if (g_pad[0].IsPress(enButtonRight)) {
		m_move.x += m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), -m_rotationLR);

	}
	else if (g_pad[0].IsPress(enButtonUp)) {
		m_move.z += m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), 0.0f);

	}
	else if (g_pad[0].IsPress(enButtonDown)) {
		m_move.z -= m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), m_rotationD);

	}
	else if (g_pad[0].IsTrigger(enButtonA) && m_characon.IsOnGround() == false) {
		//�W�����v
		//m_move.y = m_jumpPos;
	}

	if (m_characon.IsOnGround()) {
		//�d�̓X�g�b�v
		m_move.y = 0.0f;
	}
	m_animation.Play(Animation_Walk, 0.5f);
	m_position = m_characon.Execute(m_caraTime, m_move);

}
void Player::Attack()
{
	if (Atcount == 1) {
		//�U��1���
		m_animation.Play(Animation_Attack1, 0.5f);
		attackflag = true;
		if (m_animation.IsPlaying() == false) {
			//�Đ��I��������ҋ@�ɖ߂�
			Atcount = 0;
			attackflag = false;
			m_state = Player_Idle;
		}
	}
	/*if (Atcount >= 2) {
		//�U��2���
		m_animation.Play(Animation_Attack2, 0.5f);
		attackflag = true;
		if (m_animation.IsPlaying() == false) {
			//�Đ��I��������ҋ@�ɖ߂�
			Atcount = 0;
			attackflag = false;
			m_anime = Animation_Idel;
		}

	}*/
}
void Player::Dead()
{
	//���S
	m_animation.Play(Animation_Dead, 0.5f);
	m_model->IsRequestDelete();
}
void Player::Update()
{
	
	if (g_pad[0].IsTrigger(enButtonA) ) {
		Atcount++;
		m_state = Player_Attack;
	}

	switch (m_state)
	{
	case Player::Player_Idle:
		//�ҋ@
		Idel();
		break;
	case Player::Player_Walk:
		//�ړ�
		Move();
		break;
	case Player::Player_Attack:
		//�U��
		Attack();
		break;
	case Player::Player_Dead:
		//���S
		Dead();
		break;
	}
	m_animation.Update(0.05f);//�A�j���[�V�����Đ�
	//���[���h�s��̍X�V�B
	m_model->SetPosition(m_position);
	m_model->SetRotation(m_rotation);
}

void Player::Render(){}
void Player::PostRender(){}
