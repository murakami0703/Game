#include "stdafx.h"
#include "Player.h"
#include "ShadowMap.h"
#include "GameData.h"
#include "EffectManager.h"


Player* Player::m_instance = nullptr;
const CVector4 PLAYER_LIGHTCOLOR_RED = { 0.8f,0.0f,0.0f,1.0f };	//ダメージ時にプレイヤーに当たっているカメラを赤くする
const CVector4 PLAYER_LIGHTCOLOR_DEFAULT = { 0.7f, 0.7f, 0.7f, 1.0f };//通常カメラの色
const int LIGHT_CHANGEDEFAULT_TIME = 10;//ライトのカラーをデフォルトに戻すまでの時間
const int TIMER_INITIAL_VALUE_ZERO = 0;		//タイマーの初期化用の値

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
	m_animClips[Animation_Idel].Load(L"Assets/animData/playIdel.tka");
	m_animClips[Animation_Walk].Load(L"Assets/animData/playwalk.tka");
	m_animClips[Animation_Walk].SetLoopFlag(true);
	m_animClips[Animation_Attack].Load(L"Assets/animData/playAttack.tka");

	//cmoファイルの読み込み。
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/Footman_Default.cmo", m_animClips, AnimationClip_Num);
	m_position = { -4300.0f, 430.0f, -3000.0f };
	m_skinModelRender->SetPosition(m_position);

	m_scale = { 0.5f, 0.5f, 0.5f };
	m_skinModelRender->SetScale(m_scale);
	m_characon.Init(20.0f, 30.0f, m_position);//キャラコン
	m_move = m_position;

	//各マップの設定。
	/*m_skinModelRender->SetNormalMap(L"Assets/modelData/Normal.dds");
	m_skinModelRender->SetSpecularMap(L"Assets/modelData/MatallicSmoothness.dds");
	m_skinModelRender->SetAmbientMap(L"Assets/modelData/AO.dds");
	*/
	m_nowHP = GameData::GetInstance()->GetHitPoint();
	m_skinModelRender->SetShadowCaster(true);
	return true;
}

void Player::Idel()
{
	m_skinModelRender->PlayAnimation(0);

	//待機状態なにもしない
	if (g_pad[0].IsPressAnyKey())
	{
		m_state = Player_Walk;
	}

}
void Player::Move()
{
	m_move.x = 0.0f;
	m_move.z = 0.0f;

	//十字移動と回転。
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_move.x -= m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), m_rotationLR);

	}
	else if (g_pad[0].IsPress(enButtonRight)) {
		m_move.x += m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), -m_rotationLR);

	}
	else if (g_pad[0].IsPress(enButtonUp)) {
		m_move.z += m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), 0.0f);

	}
	else if (g_pad[0].IsPress(enButtonDown)) {
		m_move.z -= m_movespeed;
		m_rotation.SetRotation(CVector3().AxisY(), m_rotationD);

	}
	m_move.y -= 1.0f;
	if (m_characon.IsOnGround()) {
		//重力ストップ
		m_move.y = 0.0f;
	}
	m_position = m_characon.Execute(m_caraTime, m_move);
	m_skinModelRender->PlayAnimation(1);

}
void Player::Attack()
{
	EffectManager* effect = EffectManager::GetInstance();
	if (Atcount == 1 && attackflag == false) {
		//攻撃1回目
		m_skinModelRender->PlayAnimation(2);
		//effect->EffectPlayer(EffectManager::Bat_memai, m_position, { 10.0f,10.0f,10.0f });
		//m_se.Play(false);
		attackflag = true;
		Atcount = 0;
	}
	/*if (Atcount >= 2) {
		//攻撃2回目
		m_animation.Play(Animation_Attack2, 0.5f);
		attackflag = true;
		if (m_animation.IsPlaying() == false) {
			//再生終了したら待機に戻る
			Atcount = 0;
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
void Player::Dead()
{
	//死亡
}

void Player::Damage()
{
	GameData* gamedata = GameData::GetInstance();
	//ダメージ受けました。
	//赤くしますよお
	m_skinModelRender->SetLightColor(PLAYER_LIGHTCOLOR_RED);
	m_damageTimer++;
	//ちょっと時間経過したら元に戻す。
	if (m_damageTimer>= LIGHT_CHANGEDEFAULT_TIME) {
		m_damageTimer = TIMER_INITIAL_VALUE_ZERO;
		m_skinModelRender->SetLightColor(PLAYER_LIGHTCOLOR_DEFAULT);
		m_nowHP = gamedata->GetHitPoint();
	}

}
void Player::Update()
{
	GameData* gamedata = GameData::GetInstance();
	//攻撃します。
	if (g_pad[0].IsTrigger(enButtonA) ) {
		Atcount = 1;
		m_state = Player_Attack;
	}
	//ダメージ受けましたわよ
	if (gamedata->GetHitPoint() < m_nowHP) {
		Damage();		//ダメージ受けましたぁ
	}
	
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
	case Player::Player_Dead:
		Dead();			//死亡
		break;
	case Player::Player_Damage:
		Damage();		//ダメージ受けましたぁ
		break;
	}

	//ワールド行列の更新。
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}

