#include "stdafx.h"
#include "Player.h"
#include "ShadowMap.h"
#include "GameData.h"

Player* Player::m_instance = nullptr;

Player::Player()
{
	m_instance = this;

	//アニメーションクリップのロードとループフラグの設定。
	m_animClips[Animation_Idel].Load(L"Assets/animData/eneIdle.tka");
	m_animClips[Animation_Idel].SetLoopFlag(true);
	m_animClips[Animation_Walk].Load(L"Assets/animData/eneWalk.tka");
	m_animClips[Animation_Walk].SetLoopFlag(true);
	m_animClips[Animation_Attack1].Load(L"Assets/animData/eneAT1.tka");
	m_animClips[Animation_Dead].Load(L"Assets/animData/eneDeath.tka");

	//cmoファイルの読み込み。
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/Footman_Default.cmo", m_animClips, AnimationClip_Num);
	m_position= { -4500.0f, 400.0f, -2500.0f };
	m_skinModelRender->SetPosition(m_position);

	m_scale = { 50.0f, 50.0f, 50.0f };
	m_skinModelRender->SetScale(m_scale);
	m_characon.Init(20.0f, 30.0f, m_position);//キャラコン
	m_move = m_position;
	m_skinModelRender->SetShadowMap(true);
}
Player::~Player()
{
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
	else if (g_pad[0].IsTrigger(enButtonA) && m_characon.IsOnGround() == false) {
		//ジャンプ
		//m_move.y = m_jumpPos;
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
	if (Atcount == 1) {
		//攻撃1回目
		m_skinModelRender->PlayAnimation(2);
		attackflag = true;
		if (m_skinModelRender->IsPlayingAnimation() == false) {
			//再生終了したら待機に戻る
			Atcount = 0;
			attackflag = false;
			m_state = Player_Idle;
		}
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
}
void Player::Dead()
{
	//死亡
}
void Player::Update()
{
	//攻撃します。
	if (g_pad[0].IsTrigger(enButtonA) ) {
		Atcount = 1;
		m_state = Player_Attack;
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
	}

	//ワールド行列の更新。
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}

