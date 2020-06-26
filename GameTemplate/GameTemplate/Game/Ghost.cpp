#include "stdafx.h"
#include "Ghost.h"
#include "GameData.h"
#include "Player.h"
#include "SiegePoint.h"
#include "EffectManager.h"
#include "SoulManager.h"




Ghost::Ghost()
{
}

Ghost::~Ghost()
{
}

bool Ghost::Start()
{

	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/ghost/ghost_Idle.tka");
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/ghost/ghost_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/ghost/ghost_premove.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/ghost/ghost_death.tka");
	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/ghosts.cmo", m_animClips, eAnimation_Num);
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

	m_enemyModelRender->SetShadowMap(true);		//�V���h�E�}�b�v�ɕ`��B

	return true;
}

void Ghost::Horizon()
{
	//�G�l�~�[�̑O�����������߂�B
	//�O��������{0, 0, 1}�̃x�N�g����m_rotation�ŉ񂵂ċ��߂Ă݂�B
	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };
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
	if (fabsf(angle) < CMath::DegToRad(horiAngle) && toPlayerLen < horilong)
	{
		//�߂��I�I�I�I�I
		m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
		//�󂢂Ă�o�g���|�C���g�Ɍ������Ă�����
		if (m_battlePoint != nullptr) {
			flag = true;
			m_state = eState_Follow;
		}

	}

}

void Ghost::Idle()
{
	//�ҋ@�B
	m_timer++;
	//��莞�Ԍo�Ɯp�j���܂��B
	if (m_timer >= m_idleTime) {
		m_timer = 0;
		m_state = eState_Loitering;
	}

	Horizon();	//����p����

	m_enemyModelRender->PlayAnimation(1);
}
void Ghost::Loitering()
{
	//�p�j�B
	//��莞�Ԃ��Ƃɕ����]������B
	if (m_timer == 0) {
		//�����_���ŕ��������肵�ē����܂�
		m_randRot = rand() % 360;
		m_rotation.SetRotation(CVector3::AxisY(), (float)m_randRot);
		walkmove = { 0.0f, 0.0f,-1.0f };
		m_rotation.Multiply(walkmove);
		m_timer = 1;
		flag = false;
	}
	else if (m_timer > m_randTimer) {
		m_timer = 0;
	}
	else {
		m_timer++;
	}
	m_position += walkmove * randomSpeed;

	Horizon();	//����p����

	m_enemyModelRender->PlayAnimation(1);

}

void Ghost::Follow()
{
	//�ǔ�����
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	if (m_toBPVec.Length() > 50.0f) {
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
		m_position += m_toBPVec * 5.0f;

	}
	/*else if (m_toBPVec.Length() < 10.0f) {
		//BP���܂���
		m_battlePosflag = true;
	}*/
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
	if (m_battlePoint != nullptr) {
		if (m_toPlayerVec.Length() <= 200.0f) {
			EneAttackflag = true;
			m_timer = 0;
			m_state = eState_Premove;
		}
	}
	//�����Ȃ����̂ł��̏�Ŝp�j�B
	if (m_toPlayerVec.Length() > 600.0f) {
		m_battlePoint->enemyCount = 0;
		m_battlePoint = nullptr;
		m_state = eState_Loitering;
	}
	m_enemyModelRender->PlayAnimation(1);

}

void Ghost::Premove()
{	

	CVector3 diff = m_toPlayerVec;
	diff.Normalize();

	timer1++;
	if (timer1 <= 10) {
		m_position += diff * 1.0f;
		m_position.y -= 3.0f;

	}
	else if (timer1 >= 10 && timer1 <= 50) {
		m_position += diff * 4.0f;
		m_position.y += 8.0f;
	}
	else if (timer1 >= 50 && timer1 <= 60) {
		timer1 = 0;
		dff = m_toPlayerVec;
		dff.Normalize();
		m_state = eState_Attack;

	}


	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };

	//��]�̏���
	if (fabsf(m_position.x) < 0.001f
		&& fabsf(m_position.z) < 0.001f) {
		//�킩���
		return;
	}
	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = m_toPlayerVec;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

	m_enemyModelRender->PlayAnimation(2,0.5f);
}
void Ghost::Attack()
{
	//�U�������I�I�I

	//�}�~�����܂�
	EffectManager* effect = EffectManager::GetInstance();


	if (baund==true && m_position.y >= 410.0f) {
		m_position += dff * 60.0f;
		m_position.y -= 3.0f;
	}
	else {
		baund = false;
		m_timer++;
		if (m_timer<=1){
			effect->EffectPlayer(EffectManager::bund, { m_position.x ,430.0f,m_position.z }, { 30.0f,30.0f,30.0f });

		}
		else if (baund == false && m_position.y <= 410.0f) {
			m_position += dff * 1.0f;
			m_position.y += 3.0f;
			if (EneAttackflag == true && (Player::GetInstance()->GetPosition() - m_position).Length() < 80.0f) {
				//�ߋ����ōU��������
				//HP���炷
				GameData::GetInstance()->HPCalc(-1.0f);
				EneAttackflag = false;
			}

		}
		else if (m_timer <= 60.0f) {
			m_position = m_position;
		}
		else {
			m_timer = 0;
			baund = true;
			m_battlePoint->enemyCount = 0;
			m_battlePoint = nullptr;
			m_state = eState_Loitering;
		}
	}
	m_enemyModelRender->PlayAnimation(0);

}

void Ghost::Dead()
{
	EffectManager* effect = EffectManager::GetInstance();
	SoulManager* soul = SoulManager::GetInstance();
	m_enemyModelRender->PlayAnimation(3);
	m_scale -= {0.05f, 0.05f, 0.05f};
	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		//�A�j���[�V�����̍Đ����I������̂ŏ�����
		//�G�t�F�N�g�Đ���Soul�o��
		effect->EffectPlayer(EffectManager::Enemy_Dead, { m_position.x ,420.0f,m_position.z }, { 20.0f,20.0f,20.0f });
		effect->EffectPlayer(EffectManager::Item_Get, { m_position.x ,430.0f,m_position.z }, { 12.0f,12.0f,12.0f });
		soul->SoulGenerated({ m_position.x ,430.0f,m_position.z });
		//�G�l�~�[�̐����炵�܂�
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();
		//�����Ȃ����B
		g_goMgr->DeleteGameObject(m_enemyModelRender);
		g_goMgr->DeleteGameObject(this);
	}

}

void Ghost::Update()
{
	//�v���C���[�Ƃ̋����𒲂ׂ�B
	m_playerPos = Player::GetInstance()->GetPosition();
	m_toPlayerVec = m_playerPos - m_position;
	//�U�������������̂Ŏ��ʁB
	if (Player::GetInstance()->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < 150.0f) {
			m_state = eState_Dead;
		}
	}
	switch (m_state) {
	case Ghost::eState_Idle:
		Idle();
		break;
	case Ghost::eState_Loitering:
		Loitering();		//�p�j��
		break;
	case Ghost::eState_Follow:
		Follow();			//�v���C���[��ǐ�
		break;
	case Ghost::eState_Premove:
		Premove();			//�p�j�ʒu�ɖ߂�
		break;
	case Ghost::eState_Attack:
		Attack();			//�U��
		break;
	case Ghost::eState_Dead:
		Dead();				//��
		break;
	}

	//���[���h�s��̍X�V�B
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);
}
