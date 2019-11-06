#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animClips[Animation_Idel].Load(L"Assets/animData/run.tka");
	m_animClips[Animation_Walk].Load(L"Assets/animData/walk.tka");
	//���[�v�t���O�̐ݒ�B
	m_animClips[Animation_Idel].SetLoopFlag(true);
	m_animClips[Animation_Walk].SetLoopFlag(true);

	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_position = { 0.0f,5.0f,0.0f };
	//m_characon.Init(20.0f, 100.0f, m_position);
	m_move = m_position;
	m_plAnime.Init(m_model, m_animClips, AnimationClip_Num);
	m_plAnime.Play(Animation_Walk);

}
Player::~Player()
{
}

void Player::Move()
{
	//�\���ړ��B
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_move.x -= 4.0f;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		m_move.x += 4.0f;
	}
	if (g_pad[0].IsPress(enButtonUp)) {
		m_move.z += 4.0f;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		m_move.z -= 4.0f;
	}
}
void Player::Update()
{
	Move();
	//�d��
	if (m_position.y > 0.0f) {
		//m_move.y -= 0.2f;

	}
	//m_position = m_characon.Execute((1.0f / 60.0f), m_move);
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_move, CQuaternion::Identity(), CVector3::One());
	m_model.Update();
}
void Player::PlAnimation()
{
	switch (m_anime)
	{
	case Player::Animation_Idel:
		//�ҋ@��
		//�\���L�[�������ꂽ��ړ��A�j���[�V�����Đ�
		if (g_pad[0].IsPress(enButtonLeft) ||
			g_pad[0].IsPress(enButtonRight) ||
			g_pad[0].IsPress(enButtonUp) ||
			g_pad[0].IsPress(enButtonDown))
		{
			m_anime = Animation_Walk;
		}
		break;
	case Player::Animation_Walk:
		//�ړ���
		break;
	case Player::Animation_Attack1:
		break;
	case Player::Animation_Attack2:
		break;
	case Player::Animation_Jump:
		//�W�����v��
		break;
	default:
		break;
	}

}

void Player::Draw(int renderMode)
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
}