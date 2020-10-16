#include "stdafx.h"
#include "Ghost.h"
#include "GameData.h"
#include "Player.h"

#include "SiegePoint.h"

#include "EffectManager.h"
#include "SoulManager.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const CVector3 GHOST_FORWARD_VECTOR = { 0.0f, 0.0f, -1.0f };		//�S�[�X�g�̑O�x�N�g���B
const float GHOST_HORIANGLE = 90.0f;					//����p����̊p�x�B
const float GHOST_HORILONG = 500.0f;					//����p����̋����B

const float GHOST_IDLE_TIME = 30.0f;					//�ҋ@���ԁB
const float GHOST_TIMER_RESET = 0.0f;					//�^�C�}�[��������Ԃɖ߂��B
const int GHOST_RAND_TIMER = 120;						//�����]�����鎞�ԁB
const int GHOST_RAND_RANGE = 360;						//�����]������͈́B
const int GHOST_RAND_CALC_TIME = 0;						//�����]���̌������v�Z���鎞�ԁB

const float FOLLOW_LENGTH = 500.0f;						//�ǐՂ��n�߂鋗���B
const float FOLLOW_Y_REMOVAL = 0.0f;					//Y�����̏����B
const float FOLLOW_MOVE_SPEED = 5.0f;					//�ǔ����̈ړ����x�B

Ghost::Ghost(){}
Ghost::~Ghost(){}

bool Ghost::Start()
{
	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/ghost/ghost_Idle.tka");
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/ghost/ghost_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/ghost/ghost_premove.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/ghost/ghost_death.tka");
	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/ghosts.cmo", m_animClips, eAnimation_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_skinModelRender->SetShadowCaster(true);		//�V���h�E�}�b�v�ɕ`��B

	return true;
}

void Ghost::Horizon()
{
	//�G�l�~�[�̑O�����������߂�B
	//�O��������{0, 0, 1}�̃x�N�g����m_rotation�ŉ񂵂ċ��߂�B
	CVector3 enemyForward = GHOST_FORWARD_VECTOR;
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
	//�p�x�͐�Βl�ɂ���B
	if (fabsf(angle) < CMath::DegToRad(GHOST_HORIANGLE) && toPlayerLen < GHOST_HORILONG)
	{
		//�߂��I�I�I�I�I
		m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
		//�󂢂Ă�o�g���|�C���g�Ɍ������Ă�����
		if (m_battlePoint != nullptr) {
			m_state = eState_Follow;
		}

	}

}
void Ghost::Idle()
{
	//�ҋ@�B
	m_timer++;
	//��莞�Ԍo�Ɯp�j���܂��B
	if (m_timer >= GHOST_IDLE_TIME) {
		m_timer = GHOST_TIMER_RESET;
		m_state = eState_Loitering;
	}

	Horizon();	//����p����

	m_skinModelRender->PlayAnimation(eAnimation_Idle);
}
void Ghost::Loitering()
{
	//�p�j�B
	//��莞�Ԃ��Ƃɕ����]������B
	if (m_timer <= GHOST_RAND_CALC_TIME) {
		//�����_���ŕ��������肵�ē����܂�
		m_randRot = rand() % GHOST_RAND_RANGE;
		m_rotation.SetRotation(CVector3::AxisY(), (float)m_randRot);
		m_frontmove = GHOST_FORWARD_VECTOR;
		m_rotation.Multiply(m_frontmove);
		m_timer++;
	}
	else if (m_timer > GHOST_RAND_TIMER) {
		//�^�C�}�[�̏������B
		m_timer = GHOST_TIMER_RESET;
	}
	else {
		m_timer++;
	}

	m_position += m_frontmove * m_loiteringSpeed;
	Horizon();	//����p����

	m_skinModelRender->PlayAnimation(eAnimation_Walk);

}

void Ghost::Follow()
{
	//�ǔ�����
	//�o�g���|�C���g�Ƃ̋����𒲂ׂ�B
	CVector3 m_toBPVec = m_battlePoint->position - m_position;

	if (m_toBPVec.Length() > FOLLOW_LENGTH) {
		m_toBPVec.y = FOLLOW_Y_REMOVAL;
		m_toBPVec.Normalize();
		m_position += m_toBPVec * FOLLOW_MOVE_SPEED;

	}
	/*else if (m_toBPVec.Length() < 10.0f) {
		//BP���܂���
		m_battlePosflag = true;
	}*/

	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(GHOST_FORWARD_VECTOR, targetVector);
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
	m_skinModelRender->PlayAnimation(1);

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

	m_skinModelRender->PlayAnimation(2,0.5f);
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
	m_skinModelRender->PlayAnimation(0);

}

void Ghost::Dead()
{
	EffectManager* effect = EffectManager::GetInstance();
	SoulManager* soul = SoulManager::GetInstance();
	m_skinModelRender->PlayAnimation(3);
	m_scale -= m_smallValue;

	if (m_skinModelRender->IsPlayingAnimation() == false) {
		//�A�j���[�V�����̍Đ����I������̂ŏ�����
		//�G�t�F�N�g�Đ���Soul�o��
		effect->EffectPlayer(EffectManager::Enemy_Dead, { m_position.x ,m_effectEneDeadYPos ,m_position.z }, m_effectEneDeadSca);
		effect->EffectPlayer(EffectManager::Item_Get, { m_position.x ,430.0f,m_position.z }, { 12.0f,12.0f,12.0f });
		soul->SoulGenerated({ m_position.x ,m_soulSetYPos ,m_position.z });
		//�G�l�~�[�̐����炵�܂�
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();
		//�����Ȃ����B
		g_goMgr->DeleteGameObject(m_skinModelRender);
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
		if (m_toPlayerVec.Length() < m_deadLength) {
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
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
}
