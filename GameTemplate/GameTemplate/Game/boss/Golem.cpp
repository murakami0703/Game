#include "stdafx.h"
#include "boss/Golem.h"
#include "player/Player.h"
#include "data/GameData.h"

#include "manager/EffectManager.h"
#include "manager/SoulManager.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const float HP_SPRITE_W = 150.0f;			//HP�X�v���C�g�̕��B
const float HP_SPRITE_H = 50.0f;			//HP�X�v���C�g�̍����B
const float HP_SETACTIVE_TRUE = 1.0f;		//HP�\�����B
const float HP_SETACTIVE_FALSE = 0.0f;		//HP��\���B
const CVector2 HP_PIVOT = { 1.0f,0.5f };	//HP�o�[�̊�_�B
const int MAX_HP = 120;		//�ő�HP

///////////////////////
///sprite
const int HP_FRAME = 0;
const int HP_BAR = 1;
///////////////////////

const int TIMER_INITIAL_VALUE_ZERO = 0;		//�^�C�}�[�̏������p�̒l
const float GOLEM_IDLE_TIME = 120.0f;		//�x�e���ԁB
const float GOLEM_ATTACK_LENGTH = 300.0f;	//�U�����鋗���B
const float GOLEM_VECTOR_Y_ZERO = 0.0f;		//�ړ��x�N�g����Y���̒l�B
const float GOLEM_FOLLOW_SPEED = 5.0f;		//�ǐՒ��̈ړ����x�B

const CVector3 GOLEM_FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f };			//�S�[�����̑O�x�N�g���B
const int EFFECT_STARTPLAY_TIME = 1;								//�G�t�F�N�g���Đ������鎞�ԁB
const float GOLEM_ATTACK_EFFECT_POS_Y = 430.0f;						//�U���G�t�F�N�g��Y���W�B
const CVector3 GOLEM_ATTACK_EFFECT_SCALE = { 50.0f,50.0f,50.0f };	//�U���G�t�F�N�g�̊g�嗦�B
const float GOLEM_DAMAGE_RANGE = 300.0f;							//�_���[�W����͈̔́B
const int GOLEM_ATTACK_ENDTIME = 60;								//�U����ԏI���^�C���B �P��:frame

const float HP_SPRITE_SCALE_ONE = 1.0f;		//HP�̊g�嗦�B
const float GOLEM_DAMAGE_LENGTH = 250.0f;	//�_���[�W���󂯂鋗���B
const int REDUCE_HP = 40;					//����������HP�̒l�B
const int HP_LOWEST_VALUE = 0;				//HP�̍Œ�l�B

const float EF_SOUL_SET_POSY = 430.0f;						//�G�t�F�N�g�A���o������Y���̍����B
const CVector3 SMOKE_SCALE = { 2.0f,2.0f,2.0f };			//���G�t�F�N�g�̊g�嗦�B

const float HPBAR_ACTIVE_TRUE = 1.0f;				//�����x(�\��)�B
const float HPBAR_ACTIVE_FALSE = 0.0f;				//�����x(��\��)�B

const float HPBAR_ADD_POSY = 300.0f;				//HP�o�[�\����Y���̉��Z�l�B
const float HPBAR_REMOVAL_POSZ = 0.0f;				//HP�o�[Z���̐��l�̏����B
const int GOLEM_DAMAGE_FIRST = 0;					//�_���[�W1��ځB
const int GOLEM_DAMAGE_SECOND = 1;					//�_���[�W2��ځB
const int GOLEM_DAMAGE_THIRD = 2;					//�_���[�W3��ځB
const float DAMAGE_FIRST_SETHPBAR_POSX = 150.0f;	//�_���[�W1��ڂ�HP�o�[��X���̈ʒu�B
const float DAMAGE_SECOND_SETHPBAR_POSX = 125.0f;	//�_���[�W2��ڂ�HP�o�[��X���̈ʒu�B
const float DAMAGE_THIRD_SETHPBAR_POSX = 98.0f;		//�_���[�W3��ڂ�HP�o�[��X���̈ʒu�B

const float HPBAR_ACTIVE_LENGTH = 1000.0f;			//HP�o�[��\��������͈́B

Golem::Golem(){}
Golem::~Golem(){}

bool Golem::Start()
{
	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/golem_Boss/golem_idle.tka");
	m_animClips[eAnimation_Idle].SetLoopFlag(true);
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/golem_Boss/golem_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/golem_Boss/golem_attack.tka");
	m_animClips[eAnimation_Back].Load(L"Assets/animData/golem_Boss/golem_back.tka");
	m_animClips[eAnimation_Damage].Load(L"Assets/animData/golem_Boss/golem_damage.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/golem_Boss/golem_dead.tka");

	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/Golem_Boss.cmo", m_animClips, eAnimation_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_skinModelRender->SetShadowCaster(true);	//�V���h�E�L���X�^�[�ɓo�^�B

	//HP
	{
		//0�ԁ�Hp�t���[��
		m_hpbarSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_hpbarSprite->Init(L"Assets/sprite/Boss_Hpframe.dds", HP_SPRITE_W, HP_SPRITE_H);
		m_hpbarSprite->SetAlpha(HP_SETACTIVE_FALSE);
		m_spriteRender.push_back(m_hpbarSprite);
		//1�ԁ�Hp�o�[
		m_hpbarSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_hpbarSprite->Init(L"Assets/sprite/Boss_Hp.dds", HP_SPRITE_W, HP_SPRITE_H);
		m_hpbarSprite->SetAlpha(HP_SETACTIVE_FALSE);
		m_hpbarSprite->SetPivot(HP_PIVOT);
		m_spriteRender.push_back(m_hpbarSprite);
	}

	return true;
}

void Golem::Idle()
{
	//�x�e�B
	m_timer++;
	//�ǐՍĊJ�B
	if (m_timer >= GOLEM_IDLE_TIME) {
		m_timer = TIMER_INITIAL_VALUE_ZERO;
		m_damegeFlag = false;
		m_state = eState_Follow;
	}
	m_skinModelRender->PlayAnimation(eAnimation_Idle);
	
}
void Golem::Follow()
{
	//�v���C���[��ǐՁB
	m_move = m_toPlayerVec;

	if (m_toPlayerVec.Length() <= GOLEM_ATTACK_LENGTH) {
		//�U����ԂɑJ�ځB
		m_state = eState_Attack;
	}
	else {
		//�ړ��B
		m_move.y = GOLEM_VECTOR_Y_ZERO;
		m_move.Normalize();
		m_position += m_move * GOLEM_FOLLOW_SPEED;

	}

	CVector3 enemyForward = GOLEM_FORWARD_VECTOR;

	//�@���������������̃x�N�g�����v�Z����B
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = GOLEM_VECTOR_Y_ZERO;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

	m_skinModelRender->PlayAnimation(eAnimation_Walk);
}
void Golem::Attack()
{
	//�U���B
	EffectManager* effect = EffectManager::GetInstance();
	m_skinModelRender->PlayAnimation(eAnimation_Attack);

	if (m_skinModelRender->IsPlayingAnimation() == false)
	{
		//�U��
		m_attacktimer++;
		//�g��G�t�F�N�g�����B
		if (m_attacktimer <= EFFECT_STARTPLAY_TIME) {
			effect->EffectPlayer(
				EffectManager::Golem_Attack,
				{ m_position.x ,GOLEM_ATTACK_EFFECT_POS_Y ,m_position.z },
				GOLEM_ATTACK_EFFECT_SCALE
			);
		}
		//�v���C���[�̈ʒu����U���̃G�t�F�N�g�_���[�W�͈͂�ݒ肷��B
		float m_DamageX = m_position.x + GOLEM_DAMAGE_RANGE;
		float m_DamageZ = m_position.z + GOLEM_DAMAGE_RANGE;

		//�G�t�F�N�g�͈͓��̎��v���[���[�Ƀ_���[�W
		if (m_isDamageFlag == false &&
			m_position.x < m_DamageX &&
			m_position.x > -m_DamageX &&
			m_position.z < m_DamageZ &&
			m_position.z > -m_DamageZ
			)
		{
			GameData::GetInstance()->HPCalc(-1.0f);
			m_isDamageFlag = true;
		}

		//�U���I���ł��B
		if (m_attacktimer >= GOLEM_ATTACK_ENDTIME) {
			m_attacktimer = TIMER_INITIAL_VALUE_ZERO;
			m_isDamageFlag = false;
			m_state = eState_Back;
		}
	}
}
void Golem::Back()
{
	//����߂��B
	m_skinModelRender->PlayAnimation(eAnimation_Back);

	if (m_skinModelRender->IsPlayingAnimation() == false)
	{
		//�x�e����B
		m_timer = TIMER_INITIAL_VALUE_ZERO;
		m_state = eState_Idle;
	}
}

void Golem::MoveHPGage() {
	//HP���v�Z
	HP -= REDUCE_HP;
	m_lifeY = (float)HP / (float)MAX_HP;
	//HP�Q�[�W�𓮂���
	m_spriteRender[HP_BAR]->SetScale({ m_lifeY,HP_SPRITE_SCALE_ONE,HP_SPRITE_SCALE_ONE });
	m_damageCount++;
	m_moveGageEndflag = true;
}
void Golem::Damage()
{
	//�_���[�W��B
	if (m_moveGageEndflag == false) {
		//HP�o�[�̈ړ����������܂��B
		MoveHPGage();
		if (HP < HP_LOWEST_VALUE) {
			HP = HP_LOWEST_VALUE;
		}
	}
	else{
		//HP�Q�[�W�̈ړ��������I�������̂Œǔ���Ԃɖ߂�܂��B
		//�U�����󂯂��Ƃ��͖������Œǔ���Ԃł��B
		m_moveGageEndflag = false;
		m_state = eState_Follow;//�Ǐ]���܂��B
	}

}

void Golem::Dead()
{
	//���B
	EffectManager* effect = EffectManager::GetInstance();
	SoulManager* soul = SoulManager::GetInstance();
	m_skinModelRender->PlayAnimation(eAnimation_Death);

	if (m_skinModelRender->IsPlayingAnimation() == false) {
		//�A�j���[�V�����̍Đ����I������̂ŏ�����
		//�G�t�F�N�g�Đ���Soul�o��

		//////////////////////////
		effect->EffectPlayer(EffectManager::Enemy_Dead, { m_position.x ,EF_SOUL_SET_POSY ,m_position.z }, SMOKE_SCALE);
		//////////////////////////
		
		soul->SoulGenerated({ m_position.x ,EF_SOUL_SET_POSY ,m_position.z });

		//�G�l�~�[�̐����炵�܂�
		//////////////////////////
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();
		m_gamedate->SetResultFlag(true);
		//////////////////////////
		
		//�����Ȃ����B
		g_goMgr->DeleteGameObject(m_skinModelRender);
		g_goMgr->DeleteGameObject(this);
	}

}

void Golem::HPBarSaid()
{
	//HP�o�[�̕\���ʒu
	m_spriteRender[HP_FRAME]->SetAlpha(HPBAR_ACTIVE_TRUE);
	m_spriteRender[HP_BAR]->SetAlpha(HPBAR_ACTIVE_TRUE);
	m_headPos = m_position;
	m_headPos.y += HPBAR_ADD_POSY;
	g_camera3D.CalcScreenPositionFromWorldPosition2(m_screenPos, m_headPos);

	if (m_screenPos.z > HPBAR_REMOVAL_POSZ) {
		//�������Ƃ�HP�̈ʒu�̒��������Ă��܂��B
		m_screenPos.z = HPBAR_REMOVAL_POSZ;
		m_spriteRender[HP_FRAME]->SetPosition(m_screenPos);
		m_hpBarSetPos = m_screenPos;
		if (m_damageCount == GOLEM_DAMAGE_FIRST) {
			m_hpBarSetPos.x -= DAMAGE_FIRST_SETHPBAR_POSX;

		}
		else if (m_damageCount == GOLEM_DAMAGE_SECOND) {
			m_hpBarSetPos.x -= DAMAGE_SECOND_SETHPBAR_POSX;

		}
		else if (m_damageCount == GOLEM_DAMAGE_THIRD) {
			m_hpBarSetPos.x -= DAMAGE_THIRD_SETHPBAR_POSX;

		}

		m_spriteRender[HP_BAR]->SetPosition(m_hpBarSetPos);
	}
}

void Golem::Update()
{
	GameData* m_gamedate = GameData::GetInstance();
	if (m_gamedate->GetEnemyCount() < 10) {

		//�v���C���[�Ƃ̋����B
		m_playerPos = Player::GetInstance()->GetPosition();
		m_toPlayerVec = m_playerPos - m_position;

		//�U�������������B
		if (Player::GetInstance()->GetAttackflag() == true) {
			if (m_damegeFlag == false && m_state != eState_Attack && m_toPlayerVec.Length() < GOLEM_DAMAGE_LENGTH) {
				m_damegeFlag = true;
				m_state = eState_Damage;
			}
		}

		//HP�o�[�̕\�������B
		m_cameraPos = g_camera3D.GetPosition();
		m_hpSpritePos = m_cameraPos - m_position;
		if (m_hpSpritePos.Length() < HPBAR_ACTIVE_LENGTH) {
			//�v���C���[�Ƃ̋�����1000.0f�ȉ��Ȃ�\��������B
			HPBarSaid();
		}
		else {
			m_spriteRender[HP_FRAME]->SetAlpha(HPBAR_ACTIVE_FALSE);
			m_spriteRender[HP_BAR]->SetAlpha(HPBAR_ACTIVE_FALSE);
		}

		//���ɂ܂��B
		if (HP <= HP_LOWEST_VALUE) {
			m_state = eState_Dead;
		}

		switch (m_state)
		{
		case Golem::eState_Idle:
			Idle();			//�ҋ@�B
			break;
		case Golem::eState_Follow:
			Follow();		//�v���C���[��ǐՁB
			break;
		case Golem::eState_Attack:
			Attack();		//�U���B
			break;
		case Golem::eState_Back:
			Back();			//����߂��B
			break;
		case Golem::eState_Damage:
			Damage();		//�_���[�W��B
			break;
		case Golem::eState_Dead:
			Dead();			//���B
			break;
		}

		//���[���h�s��̍X�V�B
		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetRotation(m_rotation);
		m_skinModelRender->SetScale(m_scale);
	}
}
