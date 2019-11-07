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
	m_characon.Init(20.0f, 100.0f, m_position);//�L�����R��
	m_move = m_position;
	m_animation.Init(m_model, m_animClips, AnimationClip_Num);	//�A�j���[�V�����̏�����
	m_animation.Play(Animation_Walk);//�A�j���[�V�����Đ�
}
Player::~Player()
{
}

void Player::Move()
{
	//�\���ړ��B
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_move.x = -100.0f;
		m_rotation.SetRotation(CVector3().AxisY(), 80.0f);

	}
	else if (g_pad[0].IsPress(enButtonRight)) {
		m_move.x = 100.0f;
		m_rotation.SetRotation(CVector3().AxisY(), -80.0f);

	}
	else if (g_pad[0].IsPress(enButtonUp)) {
		m_move.z = 100.0f;
		m_rotation.SetRotation(CVector3().AxisX(), 0.0f);

	}
	else if (g_pad[0].IsPress(enButtonDown)) {
		m_move.z = -100.0f;
		m_rotation.SetRotation(CVector3().AxisY(), -110.0f);

	}
	//�d��
	if (m_characon.IsOnGround()) {
		m_move.y = 0.0f;
	}

	m_position = m_characon.Execute((1.0f / 60.0f), m_move);

}
void Player::Update()
{
	m_animation.Update(0.05f);//�A�j���[�V�����Đ�
	Move();//�\���ړ�
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3().AxisX(), 80.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������B
	qRot.Multiply(m_rotation, qRot);
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, qRot, CVector3::One());
	m_model.Update();
}
void Player::PlAnimation()
{
	/*switch (m_anime)
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
	}*/

}

void Player::Draw(int renderMode)
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
}