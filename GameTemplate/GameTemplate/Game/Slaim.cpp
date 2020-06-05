#include "stdafx.h"
#include "Slaim.h"
#include "GameData.h"
#include "Anima.h"
#include "AnimaManeger.h"
#include "Player.h"
#include "SiegePoint.h"


Slaim::Slaim()
{
	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/slaim/slaim_idle.tka");
	m_animClips[eAnimation_Idle].SetLoopFlag(true);
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/slaim/slaim_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/slaim/slaim_premove.tka");
	m_animClips[eAnimation_Premove2].Load(L"Assets/animData/slaim/slaim_premove2.tka");
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/slaim/slaim_attack.tka");
	m_animClips[eAnimation_Vertigo].Load(L"Assets/animData/slaim/slaim_vertigo.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/slaim/slaim_dead.tka");

	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/slaim.cmo", m_animClips, eAnimation_Num);
}


Slaim::~Slaim()
{

}
void Slaim::Idle()
{
	m_enemyModelRender->PlayAnimation(0);
	m_state = eState_Follow;
}

void Slaim::Loitering()
{
	if (m_toPlayerVec.Length() < m_tuisekiLength) {
		//�v���C���[�Ƃ̋������߂��Ȃ�����ǐՂ��܂�
		m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
		//�󂢂Ă�o�g���|�C���g�Ɍ������Ă�����
		if (m_battlePoint != nullptr) {
			m_state = eState_Follow;
		}
	}

	m_enemyModelRender->PlayAnimation(0);

}
void Slaim::Follow()
{	
	//�ǔ�����
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	if (m_toBPVec.Length() > 10.0f) {
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
		m_position += m_toBPVec * m_follSpeed;
	}
	else if (m_toBPVec.Length() < 10.0f) {
		//BP���܂���
		m_battlePosflag = true;
	}
	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };

	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

	//�߂��̂ōU��
	/*if (m_battlePoint != nullptr) {
		if (m_toPlayerVec.Length() <= 150.0f) {
			EneAttackflag = true;
			m_state = eState_Attack;
		}
	}*/
	//�����Ȃ����̂Ŝp�j�ʒu�ɖ߂�
	if (m_toPlayerVec.Length() > 1000.0f) {
		m_battlePoint->enemyCount = 0;
		m_battlePoint = nullptr;
		m_state = eState_Return;
	}

}
void Slaim::Premove()
{
	if (m_battlePoint != nullptr) {

		m_state = eState_Follow;
	}
	else {
		m_battlePoint->enemyCount = 0;
		m_battlePoint = nullptr;
		m_state = eState_Loitering;
	}

}
void Slaim::Attack()
{}
void Slaim::Vertigo()
{}

void Slaim::Return()
{}
void Slaim::Dead()
{
	m_enemyModelRender->PlayAnimation(2);
	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		//�A�j���[�V�����̍Đ����I������̂ŏ�����
		//�G�l�~�[�̐����炵�܂�
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();
		//�����Ȃ����B
		g_goMgr->DeleteGameObject(this);
		g_goMgr->DeleteGameObject(m_enemyModelRender);
	}
}

void Slaim::Update()
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
	case Slaim::eState_Idle:
		Idle();
		break;
	case Slaim::eState_Loitering:
		Loitering();		//�p�j��
		break;
	case Slaim::eState_Follow:
		Follow();			//�v���C���[��ǐ�
		break;
	case Slaim::eState_Premove:
		Premove();			//�\������
		break;
	case Slaim::eState_Attack:
		Attack();			//�U��
		break;
	case Slaim::eState_Vertigo:
		Vertigo();
		break;
	case Slaim::eState_Return:
		Return();			//�p�j�ʒu�ɖ߂�
		break;
	case Slaim::eState_Dead:
		Dead();				//��
		break;
	}

	//���[���h�s��̍X�V�B
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

}

