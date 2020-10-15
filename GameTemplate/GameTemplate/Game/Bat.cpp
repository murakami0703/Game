#include "stdafx.h"
#include "Bat.h"
#include "Player.h"
#include "SiegePoint.h"
#include "EffectManager.h"
#include "GameData.h"
#include "SoulManager.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////
const CVector3 BAT_FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f };	//�R�E�����̑O�x�N�g���B
const float BAT_HORIANGLE = 45.0f;						//����p����̊p�x�B
const float BAT_HORILONG = 200.0f;						//����p����̋����B
const float FOLLOW_HORIANGLE = 90.0f;					//�Ǐ]�̎���p����̊p�x�B
const float FOLLOW_HORILONG = 500.0f;					//�Ǐ]�̎���p����̋����B

const float GHOST_IDLE_TIME = 30.0f;					//�ҋ@���ԁB
const int TIMER_RESET = 0;								//�^�C�}�[��������Ԃɖ߂��B
const int RAND_TIMER = 120;								//�����]�����鎞�ԁB
const int RAND_RANGE = 360;								//�����]������͈́B
const int RAND_CALC_TIME = 0;							//�����]���̌������v�Z���鎞�ԁB
const float LOITERING_SPEED = 2.0f;						//�p�j���x�B

const float BAT_PREMOVE_LENGTH = 250.0f;						//�\������J�n�����B
const float FOLLOW_Y_REMOVAL = 0.0f;							//Y�����̏����B
const float BAT_FOLLOW_MOVESPEED = 1.0f;						//�ǔ����̃R�E�����̈ړ����x�B
const float EF_SOUL_SET_POSY = 430.0f;							//�G�t�F�N�g�A���o������Y���̍����B

const CVector3 PREMOVE_EFFECT_SCALE = { 5.0f,5.0f,5.0f };		//�\������G�t�F�N�g�̊g�嗦�B
const float EFFECT_ADD_POSY = 80.0f;							//�G�t�F�N�g�o������Y���ɉ��Z����l�B
const float LOITERING_RETURN_LENGTH = 800.0f;					//�Ǐ]��Ԃ���p�j��Ԃɖ߂鋗��
const int ATTACK_EFFECT_STARTPLAY_TIME = 1;						//�U���G�t�F�N�g���Đ������鎞�ԁB
const CVector3 ATTACK_EFFECT_SCALE = { 10.0f,10.0f,10.0f };		//�U���G�t�F�N�g�̊g�嗦�B
const float ATTACK_TIME =20.0f;									//�U�����鎞�ԁB�P�ʁFframe

const CVector3 SMOKE_SCALE = { 20.0f,20.0f,20.0f };			//���G�t�F�N�g�̊g�嗦�B
const CVector3 YELLOWLIGHT_SCALE = { 10.0f,10.0f,10.0f };	//���G�t�F�N�g�̊g�嗦�B

const float BAT_DEAD_RANGE = 120.0f;		//�U����������͈́B

Bat::Bat(){}
Bat::~Bat(){}

bool Bat::Start()
{
	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/bat/bat_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/bat/bat_premove.tka");
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/bat/bat_attack.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/bat/bat_dead.tka");

	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/bat.cmo", m_animClips, eAnimation_Num);
	m_skinModelRender->PlayAnimation(0);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_skinModelRender->SetShadowCaster(true);	//�V���h�E�L���X�^�[�ɕ`��B

	return true;
}

void Bat::Horizon()
{
	//����p����
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toPlayerDir = m_toPlayerVec;

	//���K�����s���O�ɁA�v���C���[�܂ł̋��������߂Ă����B
	float toPlayerLen = toPlayerDir.Length();
	//���K��
	toPlayerDir.Normalize();

	//enemyForward��toPlayerDir�Ƃ̓��ς��v�Z����B
	float d = BAT_FORWARD_VECTOR.Dot(toPlayerDir);

	//���ς̌��ʂ�acos�֐��ɓn���āAenemyForward��toPlayerDir�̂Ȃ��p�����߂�B
	float angle = acos(d);

	//����p����B
	//fabsf�͐�Βl�����߂�֐��I
	//�p�x�̓}�C�i�X�����݂��邩��A��Βl�ɂ���B

	//�p�j���B
	if (fabsf(angle) < CMath::DegToRad(FOLLOW_HORIANGLE) && toPlayerLen < FOLLOW_HORILONG)
	{
			m_state = eState_Follow;
	}

	//�U���B
	if (EneAttackflag == true && fabsf(angle) < CMath::DegToRad(BAT_HORIANGLE) && toPlayerLen < BAT_HORILONG) {
		//�ߋ����ōU��������
		//�v���C���[��HP���炷
		GameData::GetInstance()->HPDecrease();
		EneAttackflag = false;
	}
}

void Bat::Loitering()
{
	//�p�j�B
	//��莞�Ԃ��Ƃɕ����]������B
	if (m_timer <= RAND_CALC_TIME) {
		//�����_���ŕ��������肵�ē����܂�
		m_randRot = rand() % RAND_RANGE;
		m_rotation.SetRotation(CVector3::AxisY(), (float)m_randRot);
		m_frontmove = BAT_FORWARD_VECTOR;
		m_rotation.Multiply(m_frontmove);
		m_timer++;
	}
	else if (m_timer > RAND_TIMER) {
		//�^�C�}�[�̏������B
		m_timer = TIMER_RESET;
	}
	else {
		m_timer++;
	}

	m_position += m_frontmove * LOITERING_SPEED;
	Horizon();		//����p����B

	m_skinModelRender->PlayAnimation(eAnimation_Walk);
}
void Bat::Follow()
{
	//�ǔ����B
	m_toFollowEPVec = m_toPlayerVec;

	//���̋����܂ŋ߂Â��܂��B
	if (m_toFollowEPVec.Length() > BAT_PREMOVE_LENGTH) {
		m_toFollowEPVec.y = FOLLOW_Y_REMOVAL;
		m_toFollowEPVec.Normalize();
		m_position += m_toFollowEPVec * BAT_FOLLOW_MOVESPEED;
	}
	//�߂Â����̂ŗ\�������ԂɑJ�ڂ��܂��B
	else if (m_toFollowEPVec.Length() <= BAT_PREMOVE_LENGTH)
	{
		EneAttackflag = true;
		EffectManager* effect = EffectManager::GetInstance();
		effect->EffectPlayer(
			EffectManager::bat_pre,
			{ m_position.x ,m_position.y + EFFECT_ADD_POSY ,m_position.z },
			PREMOVE_EFFECT_SCALE, m_rotation
		);

		m_state = eState_Premove;
	}
	//���f���̑O�����B
	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = m_toPlayerVec;
	//�@Y�����͏������Đ��K������B
	targetVector.y = FOLLOW_Y_REMOVAL;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(BAT_FORWARD_VECTOR, targetVector);
	m_rotation = qRot;

	//�����Ȃ����̂ł��̏�Ŝp�j����B
	if (m_toPlayerVec.Length() > LOITERING_RETURN_LENGTH) {
		m_state = eState_Loitering;
	}

	m_skinModelRender->PlayAnimation(eAnimation_Walk);

}
void Bat::Premove()
{
	//�\������B
	m_skinModelRender->PlayAnimation(eAnimation_Premove);	//�\������A�j���̍Đ��B
	//�\������A�j�����I������̂ōU����ԂɑJ�ځB
	if (m_skinModelRender->IsPlayingAnimation() != true)
	{
		m_state = eState_Attack;

	}
}
void Bat::Attack()
{
	EffectManager* effect = EffectManager::GetInstance();
	//�U���B
	m_skinModelRender->PlayAnimation(eAnimation_Attack);	//�U���A�j���̍Đ��B
	//�G�t�F�N�g�Đ��i�U���j
	m_timer++;
	if (m_timer <= ATTACK_EFFECT_STARTPLAY_TIME)
	{
		effect->EffectPlayer(
			EffectManager::Bat_Attack,
			{ m_position.x ,m_position.y + EFFECT_ADD_POSY ,m_position.z },
			ATTACK_EFFECT_SCALE,
			m_rotation
		);
	}
	else if (EneAttackflag == true && m_timer <= ATTACK_TIME)
	{
		//�g�����킩���z�B�v�m�F�B
		/////////////////////////////////////////////////
		/*CVector3 enemyForward = BAT_FORWARD_VECTOR;
		m_rotation.Multiply(enemyForward);*/
		/////////////////////////////////////////////////

		//����p����
		Horizon();
	}
	else if (m_skinModelRender->IsPlayingAnimation() != true && m_timer >= ATTACK_TIME)
	{
		//�A�j���[�V�������I������̂Ŝp�j��ԂɑJ�ځB
		m_timer = TIMER_RESET;
		m_state = eState_Loitering;
	}
}
void Bat::Dead()
{
	EffectManager* effect = EffectManager::GetInstance();
	SoulManager* soul = SoulManager::GetInstance();

	m_skinModelRender->PlayAnimation(eAnimation_Death);
	if (m_skinModelRender->IsPlayingAnimation() != true) {
		//�A�j���[�V�����̍Đ����I������̂ŏ�����
		//�G�t�F�N�g�Đ���Soul�o��
		effect->EffectPlayer(EffectManager::Enemy_Dead, { m_position.x ,EF_SOUL_SET_POSY,m_position.z }, SMOKE_SCALE);			//���B
		effect->EffectPlayer(EffectManager::Item_Get, { m_position.x ,EF_SOUL_SET_POSY,m_position.z }, YELLOWLIGHT_SCALE);		//���B
		soul->SoulGenerated({ m_position.x ,EF_SOUL_SET_POSY,m_position.z });
		//�G�l�~�[�̐����炵�܂�
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();

		//�A�j���[�V�����̍Đ����I������̂ŏ����܁B
		//�����Ȃ����B
		g_goMgr->DeleteGameObject(m_skinModelRender);
		g_goMgr->DeleteGameObject(this);
	}
}

void Bat::Update()
{

	//�v���C���[�Ƃ̋����𒲂ׂ�B
	m_playerPos = Player::GetInstance()->GetPosition();
	m_toPlayerVec = m_playerPos - m_position;

	//�U�������������̂Ŏ��ʁB
	//////////////////////////////////////////////////
	if (Player::GetInstance()->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < BAT_DEAD_RANGE) {
			m_state = eState_Dead;
		}
	}
	//////////////////////////////////////////////////

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
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
	
}
