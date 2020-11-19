#include "stdafx.h"
#include "player/Player.h"
#include "graphics/ShadowMap.h"
#include "data/GameData.h"
#include "manager/EffectManager.h"


Player* Player::m_instance = nullptr;

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////
const float PLAYER_COLLISION_RADIUS = 20.0f;	//�v���C���[�̃J�v�Z���R���W�����̔��a�B
const float PLAYER_COLLISION_HEIGHT = 30.0f;	//�v���C���[�̃J�v�Z���R���W�����̍����B
const float CHARACON_TIME = (1.0f / 60.0f);		//�L�����R���̌o�ߎ��ԁB

const CVector4 PLAYER_LIGHTCOLOR_RED = { 0.8f,0.0f,0.0f,1.0f };			//�_���[�W���Ƀv���C���[�ɓ������Ă���J������Ԃ�����B
const CVector4 PLAYER_LIGHTCOLOR_DEFAULT = { 0.7f, 0.7f, 0.7f, 1.0f };	//�ʏ�J�����̐F�B
const int LIGHT_CHANGEDEFAULT_TIME = 10;			//���C�g�̃J���[���f�t�H���g�ɖ߂��܂ł̎��ԁB
const int TIMER_INITIAL_VALUE_ZERO = 0;				//�^�C�}�[�̏������p�̒l�B
const float PLAYER_ROTATION_ANGLE_L = 80.0f;		//���̉�]�p�x�B
const float PLAYER_ROTATION_ANGLE_R = -80.0f;		//�E�̉�]�p�x�B
const float PLAYER_ROTATION_ANGLE_F = 0.0f;			//��̉�]�p�x�B
const float PLAYER_ROTATION_ANGLE_D = 110.0f;		//���̉�]�p�x�B
const float MOVE_SPEED = 900.0f;					//�ړ����x�B

Player::Player()
{
	m_instance = this;
}
Player::~Player()
{
}

bool Player::Start()
{

	//�A�j���[�V�����N���b�v�̃��[�h�ƃ��[�v�t���O�̐ݒ�B
	m_animClips[Animation_Idel].Load(L"Assets/animData/player/player_idle.tka");
	m_animClips[Animation_Idel].SetLoopFlag(true);
	m_animClips[Animation_Walk].Load(L"Assets/animData/player/player_walk.tka");
	m_animClips[Animation_Walk].SetLoopFlag(true);
	m_animClips[Animation_Run].Load(L"Assets/animData/player/player_dash.tka");
	m_animClips[Animation_Run].SetLoopFlag(true);

	m_animClips[Animation_Bomb_With].Load(L"Assets/animData/player/player_bom_with.tka");
	m_animClips[Animation_Bomb_With_Walk].Load(L"Assets/animData/player/player_bomwith_walk.tka");
	m_animClips[Animation_Bomb_With_Walk].SetLoopFlag(true);
	m_animClips[Animation_Bomb_Throw].Load(L"Assets/animData/player/player_bom_throw.tka");

	m_animClips[Animation_Drink].Load(L"Assets/animData/player/player_drink.tka");
	m_animClips[Animation_Attack].Load(L"Assets/animData/player/player_attacktes.tka");
	m_animClips[Animation_Damage].Load(L"Assets/animData/player/player_damage.tka");

	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/player.cmo", m_animClips, AnimationClip_Num);
	m_position = { -4300.0f, 430.0f, -3000.0f };
	m_skinModelRender->SetPosition(m_position);
	m_scale = { 3.0f, 3.0f, 3.0f };
	m_skinModelRender->SetScale(m_scale);

	//�L�����R��
	m_characon.Init(
		PLAYER_COLLISION_RADIUS, 
		PLAYER_COLLISION_HEIGHT,
		m_position
	);
	m_move = m_position;


	m_nowHP = GameData::GetInstance()->GetHitPoint();	//playerHP
	m_skinModelRender->SetShadowCaster(true);
	return true;
}

void Player::Idel()
{
	//�ҋ@���
	//�Ȃɂ����Ȃ�
	GameData* gamedata = GameData::GetInstance();

	//�A�C�e�������̗L���ɂ���ăA�j���[�V������ς��܂��B
	//if (gamedata->GetItemInUseFlag() != false) {
	//	m_skinModelRender->PlayAnimation(Animation_Bomb_With);
	//}
	//else {
		m_skinModelRender->PlayAnimation(Animation_Idel);
	//}

	//�ړ��{�^���������ꂽ�������ԂցB
	if (g_pad[0].IsPress(enButtonLeft) ||
		g_pad[0].IsPress(enButtonRight) ||
		g_pad[0].IsPress(enButtonUp) ||
		g_pad[0].IsPress(enButtonDown) 
)	{
		m_state = Player_Walk;
	}
	if (g_pad[0].IsPress(enButtonA)) {
		m_state = Player_Attack;
	}

	//�U���{�^���������ꂽ��U����ԂɁB
}
void Player::Move()
{
	GameData* gamedata = GameData::GetInstance();
	//�ړ�

	m_move.x = 0.0f;
	m_move.z = 0.0f;
	//�\���ړ��Ɖ�]�B
	if (g_pad[0].IsPress(enButtonLeft)) {
		//��
		m_move.x -= gamedata->GetSPD();
		m_rotation.SetRotation(CVector3().AxisY(), PLAYER_ROTATION_ANGLE_L);

	}
	else if (g_pad[0].IsPress(enButtonRight)) {
		//�E
		m_move.x += gamedata->GetSPD();
		m_rotation.SetRotation(CVector3().AxisY(), PLAYER_ROTATION_ANGLE_R);

	}
	else if (g_pad[0].IsPress(enButtonUp)) {
		//�O
		m_move.z += gamedata->GetSPD();
		m_rotation.SetRotation(CVector3().AxisY(), PLAYER_ROTATION_ANGLE_F);

	}
	else if (g_pad[0].IsPress(enButtonDown)) {
		//���
		m_move.z -= gamedata->GetSPD();
		m_rotation.SetRotation(CVector3().AxisY(), PLAYER_ROTATION_ANGLE_D);

	}
	else {
		//�ړ����ĂȂ��̂őҋ@��ԂɑJ�ځB
		m_state = Player_Idle;
	}
	//����
	if (g_pad[0].IsPress(enButtonB)) {
		m_move = m_move * 2.0f;
	}
	//�d��
	m_move.y -= 1.0f;

	if (m_characon.IsOnGround()) {
		//�n�ʏ�Ȃ̂ŏd�̓X�g�b�v
		m_move.y = 0.0f;
	}

	m_position = m_characon.Execute(CHARACON_TIME, m_move);

	//�A�C�e�������̗L���ɂ���ăA�j���[�V������ς��܂��B
	/*if (gamedata->GetItemInUseFlag() != false) {
		m_skinModelRender->PlayAnimation(Animation_Bomb_With_Walk);
	}
	else {
	*/	if (g_pad[0].IsPress(enButtonB)) {
			m_skinModelRender->PlayAnimation(Animation_Run);
		}
		else {
			m_skinModelRender->PlayAnimation(Animation_Walk);
		}
	//}

}
void Player::Attack()
{
	//�U��
	//��i�K�U�����ł��܂��B
	EffectManager* effect = EffectManager::GetInstance();
	if (m_Atcount == 1 && attackflag == false) {
		//�U��1���
		m_skinModelRender->PlayAnimation(Animation_Attack);
		//effect->EffectPlayer(EffectManager::Bat_memai, m_position, { 10.0f,10.0f,10.0f });
		//m_se.Play(false);
		attackflag = true;
		m_Atcount = 0;
	}
	/*if (m_Atcount >= 2) {
		//�U��2���
		m_animation.Play(Animation_Attack2, 0.5f);
		attackflag = true;
		if (m_animation.IsPlaying() == false) {
			//�Đ��I��������ҋ@�ɖ߂�
			m_Atcount = 0;
			attackflag = false;
			m_anime = Animation_Idel;
		}

	}*/
	if (m_skinModelRender->IsPlayingAnimation() == false && attackflag == true) {
		//�Đ��I��������ҋ@�ɖ߂�
		attackflag = false;
		m_state = Player_Idle;
	}

}
void Player::ItemUse()
{
	//�A�C�e���g�p�B
}

void Player::Damage()
{
	GameData* gamedata = GameData::GetInstance();
	//�_���[�W�󂯂܂����B
	//�Ԃ����܂��您
	m_skinModelRender->SetLightColor(PLAYER_LIGHTCOLOR_RED);
	m_damageTimer++;
	//������Ǝ��Ԍo�߂����猳�ɖ߂��B
	if (m_damageTimer >= LIGHT_CHANGEDEFAULT_TIME) {
		m_damageTimer = TIMER_INITIAL_VALUE_ZERO;
		m_skinModelRender->SetLightColor(PLAYER_LIGHTCOLOR_DEFAULT);
		m_nowHP = gamedata->GetHitPoint();
	}

}

void Player::Dead()
{
	//���S
}

void Player::Update()
{
	GameData* gamedata = GameData::GetInstance();
	//�U�����܂��B
	if (g_pad[0].IsTrigger(enButtonA) ) {
		m_Atcount = 1;
		m_state = Player_Attack;
	}
	//�_���[�W�󂯂܂���
	if (gamedata->GetHitPoint() < m_nowHP) {
		Damage();		//�_���[�W�󂯂܂���
	}

	if (gamedata->GetItemInUseFlag() != false) {

	}
	//��ԁB
	switch (m_state)
	{
	case Player::Player_Idle:
		Idel();			//�ҋ@
		break;
	case Player::Player_Walk:
		Move();			//�ړ�
		break;
	case Player::Player_Attack:
		Attack();		//�U��
		break;
	case Player::Player_Damage:
		Damage();		//�_���[�W�󂯂܂���
		break;
	case Player::Player_Dead:
		Dead();			//���S
		break;
	}

	//���[���h�s��̍X�V�B
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}

