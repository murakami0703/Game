#include "stdafx.h"
#include "Bat.h"
#include "Player.h"
#include "SiegePoint.h"


Bat::Bat()
{
	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/bat/bat_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/bat/bat_premove.tka");
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/bat/bat_attack.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/bat/bat_dead.tka");
	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/bat.cmo", m_animClips, eAnimation_Num);
	m_enemyModelRender->PlayAnimation(0);
	m_position = { -4500.0f, 450.0f, -2500.0f };
	m_scale = { 5.0f,5.0f,5.0f };
	m_enemyModelRender->SetShadowMap(true);

}


Bat::~Bat()
{
}
void Bat::Loitering()
{
	m_enemyModelRender->PlayAnimation(0);
	m_state = eState_Follow;
}
void Bat::Follow()
{
	//�ǔ����B
	CVector3 m_toEPVec = m_toPlayerVec;

	//���̋����܂ŋ߂Â��܂��B
	if (m_toEPVec.Length() > m_toPlyaerLength) {
		m_toEPVec.y = 0.0f;
		m_toEPVec.Normalize();
		m_position += m_toEPVec * 1.0f;
	}
	//�߂Â����̂ŗ\�������ԂɑJ�ڂ��܂��B
	else if (m_toEPVec.Length() <= m_toPlyaerLength)
	{
		m_state = eState_Premove;
	}
	//���f���̑O�����B
	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };
	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

	//�����Ȃ����̂ł��̏�Ŝp�j����B
	if (m_toPlayerVec.Length() > m_returnLength) {
		m_state = eState_Loitering;
	}

	m_enemyModelRender->PlayAnimation(0);

}
void Bat::Premove()
{
	//�\������B
	m_enemyModelRender->PlayAnimation(1);	//�\������A�j���̍Đ��B
	//�\������A�j�����I������̂ōU����ԂɑJ�ځB
	if (m_enemyModelRender->IsPlayingAnimation() != true)
	{
		m_state = eState_Attack;

	}
}
void Bat::Attack()
{
	//�U���B
	m_enemyModelRender->PlayAnimation(2);	//�U���A�j���̍Đ��B
	//�G�t�F�N�g�Đ��i�U���j

	//�A�j�����I������̂Ŝp�j��ԂɑJ�ځB
	if (m_enemyModelRender->IsPlayingAnimation() != true)
	{
		m_state = eState_Loitering;

	}
}
void Bat::Dead()
{
	m_enemyModelRender->PlayAnimation(3);
	if (m_enemyModelRender->IsPlayingAnimation() != true) {
		//�A�j���[�V�����̍Đ����I������̂ŏ�����
		//�����Ȃ����B
		g_goMgr->DeleteGameObject(this);
		g_goMgr->DeleteGameObject(m_enemyModelRender);
	}
}

void Bat::Update()
{

	//�v���C���[�Ƃ̋����𒲂ׂ�B
	m_playerPos = Player::GetInstance()->GetPosition();
	m_toPlayerVec = m_playerPos - m_position;

	//�U�������������̂Ŏ��ʁB
	if (Player::GetInstance()->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < 200.0f) {
			m_state = eState_Dead;
		}
	}

	switch (m_state)
	{
	case Bat::eState_Loitering:
		Loitering();		//�p�j��
		break;
	case Bat::eState_Follow:
		Follow();			//�v���C���[��ǐ�
		break;
	case Bat::eState_Premove:
		Premove();			//�\������
		break;
	case Bat::eState_Attack:
		Attack();			//�U��
		break;
	case Bat::eState_Dead:
		Dead();				//��
		break;
	}

	//���[���h�s��̍X�V�B
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);
	
}
