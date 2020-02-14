#include "stdafx.h"
#include "Player.h"
#include "ShadowMap.h"
#include "GameData.h"

Player::Player()
{
	//アニメーションクリップのロード。
	m_animClips[Animation_Idel].Load(L"Assets/animData/playIdel.tka");
	m_animClips[Animation_Walk].Load(L"Assets/animData/playwalk.tka");
	m_animClips[Animation_Attack1].Load(L"Assets/animData/playAttack.tka");
	m_animClips[Animation_Attack2].Load(L"Assets/animData/playAttack2.tka");
	m_animClips[Animation_Dead].Load(L"Assets/animData/playdead.tka");

	//ループフラグの設定。
	m_animClips[Animation_Idel].SetLoopFlag(true);
	m_animClips[Animation_Walk].SetLoopFlag(true);

	m_model.Init(L"Assets/modelData/play.cmo");
	m_position = { 0.0f,60.0f,0.0f };
	m_scale = { 0.4f,0.4f,0.4f };
	m_characon.Init(20.0f, 30.0f, m_position);//キャラコン
	m_move = m_position;
	m_animation.Init(m_model, m_animClips, AnimationClip_Num);	//アニメーションの初期化
}
Player::~Player()
{
}
void Player::Idel()
{
	//待機状態なにもしない
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

	if (m_characon.IsOnGround()) {
		//重力ストップ
		m_move.y = 0.0f;
	}

	m_position = m_characon.Execute(m_caraTime, m_move);

}
void Player::Attack()
{
	Atcount++;
	if (Atcount == 1) {
		//攻撃1回目
		m_animation.Play(Animation_Attack1, 0.5f);
		attackflag = true;
		if (m_animation.IsPlaying() == false) {
			//再生終了したら待機に戻る
			Atcount = 0;
			attackflag = false;
			m_state = Player_Idle;
		}
	}
	if (Atcount >= 2) {
		//攻撃2回目
		m_animation.Play(Animation_Attack2, 0.5f);
		attackflag = true;
		if (m_animation.IsPlaying() == false) {
			//再生終了したら待機に戻る
			Atcount = 0;
			attackflag = false;
			m_anime = Animation_Idel;
		}

	}
}
void Player::Dead()
{
	//死亡
	m_animation.Play(Animation_Dead, 0.5f);
}
void Player::Update()
{

	if (g_pad[0].IsTrigger(enButtonA) &&
		GameData::GetInstance()->GetHitPoint() >= 0.0f) {
		m_state = Player_Attack;
	}

	switch (m_state)
	{
	case Player::Player_Idle:
		//待機
		if (g_pad[0].IsPress(enButtonLeft) ||
			g_pad[0].IsPress(enButtonRight) ||
			g_pad[0].IsPress(enButtonUp) ||
			g_pad[0].IsPress(enButtonDown))
		{
			m_state = Player_Walk;
		}
		break;
	case Player::Player_Walk:
		Move();
		break;
	case Player::Player_Attack:
		Attack();
		break;
	case Player::Player_Dead:
		Dead();
		break;
	default:
		break;
	}

	//死亡判定。
	if (GameData::GetInstance()->GetHitPoint() == 0.0f) {
		//HP0なので死。
		m_state = Player_Dead;
	}

	m_animation.Update(0.05f);//アニメーション再生
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.Update();
}

void Player::Draw(EnRenderMode renderMode)
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
}