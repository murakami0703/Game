#include "stdafx.h"
#include "Bat.h"
#include "Player.h"
#include "SiegePoint.h"
#include "EffectManager.h"
#include "GameData.h"
#include "SoulManager.h"


Bat::Bat()
{

}


Bat::~Bat()
{
}

bool Bat::Start()
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
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

	m_enemyModelRender->SetShadowMap(true);

	return true;
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
		EneAttackflag = true;
		EffectManager* effect = EffectManager::GetInstance();
		effect->EffectPlayer(EffectManager::bat_pre, { m_position.x ,m_position.y + 80.0f ,m_position.z }, { 5.0f,5.0f,5.0f }, m_rotation);
		m_state = eState_Premove;
	}
	//���f���̑O�����B
	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
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
	EffectManager* effect = EffectManager::GetInstance();
	//�U���B
	m_enemyModelRender->PlayAnimation(2);	//�U���A�j���̍Đ��B
	//�G�t�F�N�g�Đ��i�U���j
	m_timer++;
	//�A�j�����I������̂Ŝp�j��ԂɑJ�ځB
	if (m_timer <= 1)
	{
		effect->EffectPlayer(EffectManager::Bat_Attack, { m_position.x ,m_position.y + 80.0f ,m_position.z }, { 10.0f,10.0f,10.0f }, m_rotation);
	}
	else if (EneAttackflag == true && m_timer <= 20)
	{
		CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
		m_rotation.Multiply(enemyForward);

		//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
		CVector3 toPlayerDir = m_toPlayerVec;

		//���K�����s���O�ɁA�v���C���[�܂ł̋��������߂Ă����B
		float toPlayerLen = toPlayerDir.Length();
		//���K��
		toPlayerDir.Normalize();

		//enemyForward��toPlayerDir�Ƃ̓��ς��v�Z����B
		float d = enemyForward.Dot(toPlayerDir);

		//���ς̌��ʂ�acos�֐��ɓn���āAenemyForward��toPlayerDir�̂Ȃ��p�����߂�B
		float angle = acos(d);


		//����p����
		//fabsf�͐�Βl�����߂�֐��I
		//�p�x�̓}�C�i�X�����݂��邩��A��Βl�ɂ���B
		if (EneAttackflag == true && fabsf(angle) < CMath::DegToRad(45.0f) && toPlayerLen < 200.0f){
			//�ߋ����ōU��������
			//HP���炷
			GameData::GetInstance()->HPCalc(-1.0f);
			EneAttackflag = false;
		}
	}
	else if (m_enemyModelRender->IsPlayingAnimation() != true && m_timer>=20)
	{
		m_timer = 0;
		m_state = eState_Loitering;
	}

}
void Bat::Dead()
{
	EffectManager* effect = EffectManager::GetInstance();
	SoulManager* soul = SoulManager::GetInstance();

	m_enemyModelRender->PlayAnimation(3);
	if (m_enemyModelRender->IsPlayingAnimation() != true) {
		//�A�j���[�V�����̍Đ����I������̂ŏ�����
	//�G�t�F�N�g�Đ���Soul�o��
		effect->EffectPlayer(EffectManager::Enemy_Dead, { m_position.x ,420.0f,m_position.z }, { 20.0f,20.0f,20.0f });
		effect->EffectPlayer(EffectManager::Item_Get, { m_position.x ,430.0f,m_position.z }, { 10.0f,10.0f,10.0f });
		soul->SoulGenerated({ m_position.x ,430.0f,m_position.z });
		//�G�l�~�[�̐����炵�܂�
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();

		//�A�j���[�V�����̍Đ����I������̂ŏ�����
		//�����Ȃ����B
		g_goMgr->DeleteGameObject(m_enemyModelRender);
		g_goMgr->DeleteGameObject(this);
	}
}

void Bat::Update()
{

	//�v���C���[�Ƃ̋����𒲂ׂ�B
	m_playerPos = Player::GetInstance()->GetPosition();
	m_toPlayerVec = m_playerPos - m_position;

	//�U�������������̂Ŏ��ʁB
	if (Player::GetInstance()->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < 120.0f) {
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
