#include "stdafx.h"
#include "player/Player.h"
#include "graphics/ShadowMap.h"
#include "data/GameData.h"
#include "manager/EffectManager.h"


Player* Player::m_instance = nullptr;

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////
const float PLAYER_COLLISION_RADIUS = 20.0f;	//プレイヤーのカプセルコリジョンの半径。
const float PLAYER_COLLISION_HEIGHT = 30.0f;	//プレイヤーのカプセルコリジョンの高さ。
const float CHARACON_TIME = (1.0f / 60.0f);		//キャラコンの経過時間。

const CVector4 PLAYER_LIGHTCOLOR_RED = { 0.8f,0.0f,0.0f,1.0f };			//ダメージ時にプレイヤーに当たっているカメラを赤くする。
const CVector4 PLAYER_LIGHTCOLOR_DEFAULT = { 0.7f, 0.7f, 0.7f, 1.0f };	//通常カメラの色。
const int LIGHT_CHANGEDEFAULT_TIME = 10;			//ライトのカラーをデフォルトに戻すまでの時間。
const int TIMER_INITIAL_VALUE_ZERO = 0;				//タイマーの初期化用の値。
const float PLAYER_ROTATION_ANGLE_L = 80.0f;		//左の回転角度。
const float PLAYER_ROTATION_ANGLE_R = -80.0f;		//右の回転角度。
const float PLAYER_ROTATION_ANGLE_F = 0.0f;			//上の回転角度。
const float PLAYER_ROTATION_ANGLE_D = 110.0f;		//下の回転角度。
const float MOVE_SPEED = 900.0f;					//移動速度。

Player::Player()
{
	m_instance = this;
}
Player::~Player()
{
}

bool Player::Start()
{

	//アニメーションクリップのロードとループフラグの設定。
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

	//cmoファイルの読み込み。
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/player.cmo", m_animClips, AnimationClip_Num);
	m_position = { -4300.0f, 430.0f, -3000.0f };
	m_skinModelRender->SetPosition(m_position);
	m_scale = { 3.0f, 3.0f, 3.0f };
	m_skinModelRender->SetScale(m_scale);

	//キャラコン
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
	//待機状態
	//なにもしない
	GameData* gamedata = GameData::GetInstance();

	//アイテム所持の有無によってアニメーションを変えます。
	//if (gamedata->GetItemInUseFlag() != false) {
	//	m_skinModelRender->PlayAnimation(Animation_Bomb_With);
	//}
	//else {
		m_skinModelRender->PlayAnimation(Animation_Idel);
	//}

	//移動ボタンが押されたら歩き状態へ。
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

	//攻撃ボタンが押されたら攻撃状態に。
}
void Player::Move()
{
	GameData* gamedata = GameData::GetInstance();
	//移動

	m_move.x = 0.0f;
	m_move.z = 0.0f;
	//十字移動と回転。
	if (g_pad[0].IsPress(enButtonLeft)) {
		//左
		m_move.x -= gamedata->GetSPD();
		m_rotation.SetRotation(CVector3().AxisY(), PLAYER_ROTATION_ANGLE_L);

	}
	else if (g_pad[0].IsPress(enButtonRight)) {
		//右
		m_move.x += gamedata->GetSPD();
		m_rotation.SetRotation(CVector3().AxisY(), PLAYER_ROTATION_ANGLE_R);

	}
	else if (g_pad[0].IsPress(enButtonUp)) {
		//前
		m_move.z += gamedata->GetSPD();
		m_rotation.SetRotation(CVector3().AxisY(), PLAYER_ROTATION_ANGLE_F);

	}
	else if (g_pad[0].IsPress(enButtonDown)) {
		//後ろ
		m_move.z -= gamedata->GetSPD();
		m_rotation.SetRotation(CVector3().AxisY(), PLAYER_ROTATION_ANGLE_D);

	}
	else {
		//移動してないので待機状態に遷移。
		m_state = Player_Idle;
	}
	//走り
	if (g_pad[0].IsPress(enButtonB)) {
		m_move = m_move * 2.0f;
	}
	//重力
	m_move.y -= 1.0f;

	if (m_characon.IsOnGround()) {
		//地面上なので重力ストップ
		m_move.y = 0.0f;
	}

	m_position = m_characon.Execute(CHARACON_TIME, m_move);

	//アイテム所持の有無によってアニメーションを変えます。
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
	//攻撃
	//二段階攻撃もできます。
	EffectManager* effect = EffectManager::GetInstance();
	if (m_Atcount == 1 && attackflag == false) {
		//攻撃1回目
		m_skinModelRender->PlayAnimation(Animation_Attack);
		//effect->EffectPlayer(EffectManager::Bat_memai, m_position, { 10.0f,10.0f,10.0f });
		//m_se.Play(false);
		attackflag = true;
		m_Atcount = 0;
	}
	/*if (m_Atcount >= 2) {
		//攻撃2回目
		m_animation.Play(Animation_Attack2, 0.5f);
		attackflag = true;
		if (m_animation.IsPlaying() == false) {
			//再生終了したら待機に戻る
			m_Atcount = 0;
			attackflag = false;
			m_anime = Animation_Idel;
		}

	}*/
	if (m_skinModelRender->IsPlayingAnimation() == false && attackflag == true) {
		//再生終了したら待機に戻る
		attackflag = false;
		m_state = Player_Idle;
	}

}
void Player::ItemUse()
{
	//アイテム使用。
}

void Player::Damage()
{
	GameData* gamedata = GameData::GetInstance();
	//ダメージ受けました。
	//赤くしますよお
	m_skinModelRender->SetLightColor(PLAYER_LIGHTCOLOR_RED);
	m_damageTimer++;
	//ちょっと時間経過したら元に戻す。
	if (m_damageTimer >= LIGHT_CHANGEDEFAULT_TIME) {
		m_damageTimer = TIMER_INITIAL_VALUE_ZERO;
		m_skinModelRender->SetLightColor(PLAYER_LIGHTCOLOR_DEFAULT);
		m_nowHP = gamedata->GetHitPoint();
	}

}

void Player::Dead()
{
	//死亡
}

void Player::Update()
{
	GameData* gamedata = GameData::GetInstance();
	//攻撃します。
	if (g_pad[0].IsTrigger(enButtonA) ) {
		m_Atcount = 1;
		m_state = Player_Attack;
	}
	//ダメージ受けました
	if (gamedata->GetHitPoint() < m_nowHP) {
		Damage();		//ダメージ受けました
	}

	if (gamedata->GetItemInUseFlag() != false) {

	}
	//状態。
	switch (m_state)
	{
	case Player::Player_Idle:
		Idel();			//待機
		break;
	case Player::Player_Walk:
		Move();			//移動
		break;
	case Player::Player_Attack:
		Attack();		//攻撃
		break;
	case Player::Player_Damage:
		Damage();		//ダメージ受けました
		break;
	case Player::Player_Dead:
		Dead();			//死亡
		break;
	}

	//ワールド行列の更新。
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}

