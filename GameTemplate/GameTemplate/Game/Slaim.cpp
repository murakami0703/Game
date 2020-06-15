#include "stdafx.h"
#include "Slaim.h"
#include "GameData.h"
#include "Anima.h"
#include "AnimaManeger.h"
#include "Player.h"
#include "SiegePoint.h"


Slaim::Slaim()
{
}


Slaim::~Slaim()
{

}

bool Slaim::Start()
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
	m_animClips[eAnimation_Vertigo].SetLoopFlag(true);

	//m_animClips[eAnimation_Death].Load(L"Assets/animData/slaim/slaim_dead.tka");

	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/slaim.cmo", m_animClips, eAnimation_Num);
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

	m_characon.Init(20.0f, 30.0f, m_position);//�L�����R��
	m_enemyModelRender->SetShadowMap(true);

	return true;
}

void Slaim::Idle()
{
	//�ҋ@�B
	timer++;
	//��莞�Ԍo�Ɯp�j���܂��B
	if (timer >= m_idleTime) {
		m_timer = 0;
		m_state = eState_Loitering;
	}
	m_enemyModelRender->PlayAnimation(0);
}
void Slaim::Loitering()
{
	//�p�j�B
	CVector3 diff = m_toPlayerVec;

	//��莞�Ԃ��Ƃɕ����]������B
	if (m_timer == 0) {
		//�����_���ŕ��������肵�ē����܂�
		m_randRot = rand() % 360;
		m_rotation.SetRotation(CVector3::AxisY(), (float)m_randRot);
		m_rotation.Multiply(m_enemyForward);
		m_timer = 1;
		flag = false;
	}
	else if (m_timer > m_randTimer) {
		m_timer = 0;
	}
	else {
		m_timer++;
	}

	//BP���󂢂ĂāA���������߂��ƒǐՏ�ԂցB
	if (diff.Length() < m_followLength) {
		m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
		//�󂢂Ă�o�g���|�C���g�Ɍ������Ă�����
		if (m_battlePoint != nullptr) {
			m_timer = 0;
			m_state = eState_Follow;
		}
	}
	moveVec = m_enemyForward * m_loiteringSpeed;
	m_position = m_characon.Execute(m_caraTime, moveVec);

}
void Slaim::Follow()
{	
	//�ǔ�����
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	//�o�g���|�C���g�Ɍ������Ĉړ����܂���
	if (m_toBPVec.Length() > m_toBPPos) {
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
	}
	else {
		//�߂��̂ňړ�����
		moveVec = {0.0f, 0.0f, 0.0f};
	}

	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(m_enemyForward, targetVector);
	m_rotation = qRot;

	moveVec = m_toBPVec * m_followSpeed;
	m_position = m_characon.Execute(m_caraTime, moveVec);
	//�o�g���|�C���g�����܂��Ă�I
	if (m_battlePoint != nullptr) {
		//�������߂��̂ŁA�\������ցB
		if (m_toPlayerVec.Length() <= m_toBPPos) {
			m_state = eState_Premove;
		}
	}
	//�����������̂ŁA�p�j�ɖ߂�B
	if (m_toPlayerVec.Length() > m_loiteringLength) {
		//
		m_battlePoint = nullptr;
		m_state = eState_Loitering;
	}

	m_enemyModelRender->PlayAnimation(1);
}
void Slaim::Premove()
{
	//�\�����삻��1
	m_enemyModelRender->PlayAnimation(2);
	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		m_state = eState_Premove2;

	}
}
void Slaim::Premove2()
{
	//�\�����삻��1
	m_enemyModelRender->PlayAnimation(3,0.5f);
	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		//�v���C���[�̏�ɗ���܁[�[�[�[�[�X
		dddd.Normalize();
		moveVec = dddd * 4000.0f ;

		//m_position.y += 50.0f;
		//�����ԏ�ɍs�����̂ōU�����܂����B
		if (m_position.y >= 1000.0f) {
			Player* player = Player::GetInstance();
			CVector3 P_Position = player->GetPosition();
			P_Position.y += 500.0f;

			m_position = P_Position;
			m_state = eState_Attack;
		}
	}
	else {
		Player* player = Player::GetInstance();
		CVector3 P_Position = player->GetPosition();
		P_Position.y += 500.0f;
		dddd = P_Position - m_position;

	}
	m_position = m_characon.Execute(m_caraTime, moveVec);

}

void Slaim::Attack()
{
	if (m_position.y >= 450.0f) {
		//Player* player = Player::GetInstance();
		//Vector3 P_Position = player->GetPosition();
		//dddd = P_Position - m_position;
		dddd.y -= 2000.0f;
		m_enemyModelRender->PlayAnimation(0);
	}
	else {
		m_enemyModelRender->PlayAnimation(4,0.5f);
		timer1++;
		if (timer1 >= 20) {
			m_state = eState_Vertigo;
		}
		else if (timer1>=5) {
			m_position.x += 1.0f;
			m_position.z += 1.0f;

		}
	}
	m_position = m_characon.Execute(m_caraTime, dddd);
	
}
void Slaim::Vertigo()
{
	m_enemyModelRender->PlayAnimation(5,0.5f);
	timer2++;
	if (timer2 >= 60) {
		m_state = eState_Loitering;
	}
}

void Slaim::Return()
{}
void Slaim::Dead()
{
	//m_enemyModelRender->PlayAnimation(2);
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
	case Slaim::eState_Premove2:
		Premove2();			//�\������
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

