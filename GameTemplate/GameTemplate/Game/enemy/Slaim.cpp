#include "stdafx.h"
#include "enemy/Slaim.h"
#include "data/GameData.h"
#include "soul/Soul.h"
#include "player/Player.h"
#include "siegepoint/SiegePoint.h"
#include "manager/EffectManager.h"
#include "manager/SoulManager.h"


/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////
const float SLAIM_COLLISION_RADIUS = 60.0f;	//�X���C���̃J�v�Z���R���W�����̔��a�B
const float SLAIM_COLLISION_HEIGHT = 30.0f;	//�X���C���̃J�v�Z���R���W�����̍����B
const float CHARACON_TIME = (1.0f / 60.0f);	//�L�����R���̌o�ߎ��ԁB
const int SLAIM_MOVEROTATION_RANGE = 360;	//�X���C���̈ړ������̊p�x�͈̔́B
const int TIMER_INITIAL_VALUE_ZERO = 0;		//�^�C�}�[�̏������p�̒l
const int CHANG_DIRECTION_TIME = 120;		//�����]�����鎞�ԁB
const int TIMER_SET_ONE = 1;				//�����]���������Ƀ^�C�}�[�ɑ������l
const float SLAIM_FOLLOW_LENGTH = 300.0f;	//�ǐՂ��n�߂鋗���B
const CVector3 SRAIM_FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f };	//�G�l�~�[�̑O�x�N�g���B
const float SRAIM_LOITERING_MOVESPEED = 120.0f;				//�p�j�̎��̑��x�B

const float SRAIM_LOITERING_LENGTH = 500.0f;			//�p�j�ɖ߂鋗���B
const float SRAIM_PREMOVE_LENGTH = 50.0f;				//�\������J�n�����B
const float FOLLOW_Y_REMOVAL = 0.0f;					//Y�����̏����B
const CVector3 SRAIM_STOP_MOVE = { 0.0f, 0.0f, 0.0f };	//�ړ���~������B
const float SRAIM_FOLLOW_MOVESPEED = 250.0f;			//�p�j�̎��̑��x�B

const float SRAIM_FALLPOINT_SPEED = 4000.0f;			//�����n�_�ւ̈ړ����x�B
const float FALLPOINT_POSY_ADDVALUE = 500.0f;			//�����n�_��Y���W�ɑ����l�B
const float SLAIM_ATTACK_LENGTH = 1000.0f;				//�U�����n�߂鋗���B


const float SRAIM_DEAD_LENGTH = 200.0f;					//���S����̋���
const CVector3 SPLITSRAIM_SCALE = { 1.5f,1.5f,1.5f };	//�������f���̊g�嗦�B
const float EF_SOUL_SET_POSY = 430.0f;						//�G�t�F�N�g�A���o������Y���̍����B
const CVector3 SMOKE_SCALE = { 20.0f,20.0f,20.0f };			//���G�t�F�N�g�̊g�嗦�B
const CVector3 YELLOWLIGHT_SCALE = { 10.0f,10.0f,10.0f };	//���G�t�F�N�g�̊g�嗦�B

const float INTERPOLATE_TIME = 0.5f;					//��Ԏ��ԁB

Slaim::Slaim()
{
}


Slaim::~Slaim()
{

}

bool Slaim::Start()
{
	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	//�ʏ탂�f���̃A�j���[�V����
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/slaim/slaim_idle.tka");
	m_animClips[eAnimation_Idle].SetLoopFlag(true);
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/slaim/slaim_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/slaim/slaim_premove.tka");
	m_animClips[eAnimation_Premove2].Load(L"Assets/animData/slaim/slaim_premove2.tka");
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/slaim/slaim_attack.tka");
	m_animClips[eAnimation_Vertigo].Load(L"Assets/animData/slaim/slaim_vertigo.tka");
	m_animClips[eAnimation_Vertigo].SetLoopFlag(true);
	//�������f���̃A�j���[�V����
	m_animClips2[eAnimation2_Death].Load(L"Assets/animData/slaim/slaim_dead.tka");

	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/slaim.cmo", m_animClips, eAnimation_Num);
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

	//�L�����R��
	m_characon.Init(
		SLAIM_COLLISION_RADIUS, 
		SLAIM_COLLISION_HEIGHT, 
		m_position
	);

	m_enemyModelRender->SetShadowCaster(true);

	return true;
}

void Slaim::Idle()
{
	//�ҋ@�B
	m_timer++;
	//��莞�Ԍo�Ɯp�j���܂��B
	if (m_timer >= m_idleTime) {
		m_timer = TIMER_INITIAL_VALUE_ZERO;
		m_state = eState_Loitering;
	}
	m_enemyModelRender->PlayAnimation(eAnimation_Idle);
}
void Slaim::Loitering()
{
	//�p�j�B
	//�^�C�}�[��0�̎������_���ŕ��������肵�ĉ�]������
	if (m_timer == TIMER_INITIAL_VALUE_ZERO) {
		m_randRot = rand() % SLAIM_MOVEROTATION_RANGE;
		m_rotation.SetRotation(CVector3::AxisY(), (float)m_randRot);
		m_enemyForward = SRAIM_FORWARD_VECTOR;
		m_rotation.Multiply(m_enemyForward);
		m_timer = TIMER_SET_ONE;
	}
	else if (m_timer > CHANG_DIRECTION_TIME) {
		//�^�C�}�[��0�ɖ߂��B
		m_timer = TIMER_INITIAL_VALUE_ZERO;
	}
	else {
		m_timer++;
	}

	//�������߂��ABP���󂢂Ă���ƒǐՏ�ԂցB
	if (m_toPlayerVec.Length() < SLAIM_FOLLOW_LENGTH) {
		m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
		//�󂢂Ă�o�g���|�C���g�Ɍ������Ă�����
		if (m_battlePoint != nullptr) {
			m_timer = TIMER_INITIAL_VALUE_ZERO;
			m_state = eState_Follow;
		}
	}
	m_moveVec = m_enemyForward * SRAIM_LOITERING_MOVESPEED;
	m_position = m_characon.Execute(CHARACON_TIME, m_moveVec);
	m_enemyModelRender->PlayAnimation(eAnimation_Walk);

}
void Slaim::Follow()
{	
	//�ǔ�����
	//BP�Ǝ����Ƃ̋����𒲂ׂ�
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	//�o�g���|�C���g�Ɍ������Ĉړ����܂���
	if (m_toBPVec.Length() > SRAIM_PREMOVE_LENGTH) {
		m_toBPVec.y = FOLLOW_Y_REMOVAL;
		m_toBPVec.Normalize();
	}
	else {
		//�߂��̂Œ�~
		m_toBPVec = SRAIM_STOP_MOVE;
	}

	//�o�g���|�C���g�����܂��Ă�I
	if (m_battlePoint != nullptr) {
		//�������߂��̂ŁA�\������ցB
		if (m_toPlayerVec.Length() <= SRAIM_PREMOVE_LENGTH) {
			m_state = eState_Premove;
		}
	}
	//�����������̂ŁA�p�j�ɖ߂�B
	if (m_toPlayerVec.Length() > SRAIM_LOITERING_LENGTH) {
		//
		m_battlePoint = nullptr;
		m_state = eState_Loitering;
	}

	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = m_toPlayerVec;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = FOLLOW_Y_REMOVAL;
	targetVector.Normalize();
	m_enemyForward = SRAIM_FORWARD_VECTOR;
	CQuaternion qRot;
	qRot.SetRotation(m_enemyForward, targetVector);
	m_rotation = qRot;

	m_moveVec = m_toBPVec * SRAIM_FOLLOW_MOVESPEED;
	m_position = m_characon.Execute(CHARACON_TIME, m_moveVec);
	m_enemyModelRender->PlayAnimation(eAnimation_Walk);
}
void Slaim::Premove()
{
	//�\�����삻��1
	m_enemyModelRender->PlayAnimation(eAnimation_Premove);
	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		m_state = eState_Premove2;
	}
}
void Slaim::Premove2()
{
	//�\�����삻��2�B
	m_enemyModelRender->PlayAnimation(eAnimation_Premove2, INTERPOLATE_TIME);

	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		//�v���C���[�̏�ɗ���܂�
		m_setMoveVec.Normalize();
		m_moveVec = m_setMoveVec * SRAIM_FALLPOINT_SPEED;

		//�����ԏ�ɍs�����̂ōU�����܂��B
		if (m_position.y >= SLAIM_ATTACK_LENGTH) {
			m_setMoveVec = m_toPlayerVec;
			//�U����ԂɑJ�ځB
			m_state = eState_Attack;
		}
	}
	else {
		//�v���C���[�Ƃ̋����𒲂׌����킹������̃x�N�g�������߂܂��B
		m_playerPos.y += FALLPOINT_POSY_ADDVALUE;
		m_setMoveVec = m_toPlayerVec - m_position;

	}
	m_position = m_characon.Execute(CHARACON_TIME, m_moveVec);
}
void Slaim::Attack()
{
	//�U��
	//�������܂��B
	if (m_position.y >= 450.0f) {
		m_setMoveVec.y -= 400.0f;
		m_enemyModelRender->PlayAnimation(0);
	}
	else {
		//�o�E���h�����I
		m_enemyModelRender->PlayAnimation(4,0.5f);
		timer1++;
		if (timer1 >= 20) {
			timer1 = 0;
			m_state = eState_Vertigo;
		}
		else if (timer1>=5) {
			m_position.x += 1.0f;
			m_position.z += 1.0f;

		}
	}
	m_position = m_characon.Execute(CHARACON_TIME, m_setMoveVec);
	
}
void Slaim::Vertigo()
{
	//�߂܂�
	EffectManager* effect = EffectManager::GetInstance();
	effect->EffectPlayer(EffectManager::Bat_memai, m_position, { 5.0f,5.0f,5.0f });

	m_enemyModelRender->PlayAnimation(eAnimation_Vertigo, INTERPOLATE_TIME);
	m_vertigoTimer++;
	//��莞�Ԃ��o������ǔ���ԂɑJ�ځB
	if (m_vertigoTimer >= 60) {
		m_timer = TIMER_INITIAL_VALUE_ZERO;
		m_vertigoTimer = 0;
		m_state = eState_Loitering;
	}
}

void Slaim::Dead()
{
	EffectManager* m_effect = EffectManager::GetInstance();
	SoulManager* m_soul = SoulManager::GetInstance();

	//�������f���ɍ����ւ�
	if (m_modelChangeFlag == false) {
		m_enemyDeadModelRender = g_goMgr->NewGameObject<SkinModelRender>();
		m_enemyDeadModelRender->Init(L"Assets/modelData/slaim_dead.cmo", m_animClips2, eAnimation2_Num);
		m_enemyDeadModelRender->SetPosition(m_position);
		m_enemyDeadModelRender->SetRotation(m_rotation);
		m_enemyDeadModelRender->SetScale(SPLITSRAIM_SCALE);
		g_goMgr->DeleteGameObject(m_enemyModelRender);
		m_modelChangeFlag = true;
	}

	m_enemyDeadModelRender->PlayAnimation(eAnimation2_Death);

	if (m_enemyDeadModelRender->IsPlayingAnimation() == false) {
		//�A�j���[�V�����̍Đ����I������̂ŏ�����
		//�G�t�F�N�g�Đ�
		//��
		m_effect->EffectPlayer(
			EffectManager::Enemy_Dead,
			{ m_position.x , EF_SOUL_SET_POSY, m_position.z },
			SMOKE_SCALE
		);
		//��
		m_effect->EffectPlayer(
			EffectManager::Item_Get,
			{ m_position.x , EF_SOUL_SET_POSY, m_position.z },
			YELLOWLIGHT_SCALE
		);
		//Soul�o��
		m_soul->SoulGenerated({ m_position.x , EF_SOUL_SET_POSY, m_position.z });

		//�G�l�~�[�̐����炵�܂�
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();
		//�����Ȃ����B
		m_characon.RemoveRigidBoby();
		g_goMgr->DeleteGameObject(m_enemyDeadModelRender);
		g_goMgr->DeleteGameObject(this);
	}
}

void Slaim::Update()
{
	//�v���C���[�Ƃ̋����𒲂ׂ�B
	m_playerPos = Player::GetInstance()->GetPosition();
	m_toPlayerVec = m_playerPos - m_position;

	//�U�������������̂Ŏ��ʁB
	if (Player::GetInstance()->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < SRAIM_DEAD_LENGTH) {
			m_state = eState_Dead;
		}
	}

	switch (m_state)
	{
	case Slaim::eState_Idle:
		Idle();
		break;
	case Slaim::eState_Loitering:
		Loitering();		//�p�j���B
		break;
	case Slaim::eState_Follow:
		Follow();			//�v���C���[��ǐՁB
		break;
	case Slaim::eState_Premove:
		Premove();			//�\������B
		break;
	case Slaim::eState_Premove2:
		Premove2();			//�\������2�B
		break;
	case Slaim::eState_Attack:
		Attack();			//�U���B
		break;
	case Slaim::eState_Vertigo:
		Vertigo();			//�߂܂��B
		break;
	case Slaim::eState_Dead:
		Dead();				//���B
		break;
	}

	//���[���h�s��̍X�V�B
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

}

