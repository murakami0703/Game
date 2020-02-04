#include "stdafx.h"
#include "Player.h"
#include "ShadowMap.h"

Player::Player()
{
	//アニメーションクリップのロード。
	m_animClips[Animation_Idel].Load(L"Assets/animData/tes.tka");
	m_animClips[Animation_Walk].Load(L"Assets/animData/tesIdle.tka");
	m_animClips[Animation_Attack1].Load(L"Assets/animData/tesAttack1.tka");
	m_animClips[Animation_Attack2].Load(L"Assets/animData/tesAttack2.tka");
	
	//ループフラグの設定。
	m_animClips[Animation_Idel].SetLoopFlag(true);
	m_animClips[Animation_Walk].SetLoopFlag(true);

	m_model.Init(L"Assets/modelData/pp.cmo");
	m_position = { 0.0f,60.0f,0.0f };

	m_characon.Init(20.0f, 30.0f, m_position);//キャラコン
	m_move = m_position;
	m_animation.Init(m_model, m_animClips, AnimationClip_Num);	//アニメーションの初期化
}
Player::~Player()
{
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
void Player::Update()
{
	Move();		//十字移動
	PlAnimation();	//アニメーション遷移

	m_animation.Update(0.05f);//アニメーション再生
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.Update();
}
void Player::PlAnimation()
{
	//攻撃アニメーション再生用
	if (g_pad[0].IsTrigger(enButtonA)) {
		Atcount++;
		if (Atcount == 1) {
			m_anime = Animation_Attack1;
			attackflag = true;
		}
		if (Atcount >= 2) {
			m_anime = Animation_Attack2;
			attackflag = true;
		}
	}



	switch (m_anime)
	{
	case Player::Animation_Idel:
		m_animation.Play(Animation_Idel);//待機
		//待機中
		//十字キーが押されたら移動アニメーション再生
		if (g_pad[0].IsPress(enButtonLeft) ||
			g_pad[0].IsPress(enButtonRight) ||
			g_pad[0].IsPress(enButtonUp) ||
			g_pad[0].IsPress(enButtonDown))
		{
			m_anime = Animation_Walk;
		}
		break;
	case Player::Animation_Walk:
		m_animation.Play(Animation_Walk);//歩き
		//十字キーが押されていない時待機アニメーション再生
		if ((g_pad[0].IsPress(enButtonLeft) ||
			g_pad[0].IsPress(enButtonRight) ||
			g_pad[0].IsPress(enButtonUp) ||
			g_pad[0].IsPress(enButtonDown))==false)
		{
			m_anime = Animation_Idel;
		}

		//移動中
		break;
	case Player::Animation_Attack1:
    			m_animation.Play(Animation_Attack1,0.5f); // 攻撃1
			if (m_animation.IsPlaying() == false) {
				Atcount = 0;
				attackflag = false;
				m_anime = Animation_Idel;

		}
		break;
	case Player::Animation_Attack2:
			m_animation.Play(Animation_Attack2, 0.5f);//攻撃2
			if (m_animation.IsPlaying() == false) {
				Atcount = 0;
				attackflag = false;
				m_anime = Animation_Idel;
			}
		break;
	default:
		break;
	}
}

void Player::Draw(EnRenderMode renderMode)
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
}