#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	//アニメーションクリップのロード。
	m_animClips[Animation_Idel].Load(L"Assets/animData/run.tka");
	m_animClips[Animation_Walk].Load(L"Assets/animData/walk.tka");
	//ループフラグの設定。
	m_animClips[Animation_Idel].SetLoopFlag(true);
	m_animClips[Animation_Walk].SetLoopFlag(true);

	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_position = { 0.0f,5.0f,0.0f };
	//m_characon.Init(20.0f, 100.0f, m_position);
	m_move = m_position;
	m_plAnime.Init(m_model, m_animClips, AnimationClip_Num);
	m_plAnime.Play(Animation_Walk);

}
Player::~Player()
{
}

void Player::Move()
{
	//十字移動。
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_move.x -= 4.0f;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		m_move.x += 4.0f;
	}
	if (g_pad[0].IsPress(enButtonUp)) {
		m_move.z += 4.0f;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		m_move.z -= 4.0f;
	}
}
void Player::Update()
{
	Move();
	//重力
	if (m_position.y > 0.0f) {
		//m_move.y -= 0.2f;

	}
	//m_position = m_characon.Execute((1.0f / 60.0f), m_move);
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_move, CQuaternion::Identity(), CVector3::One());
	m_model.Update();
}
void Player::PlAnimation()
{
	switch (m_anime)
	{
	case Player::Animation_Idel:
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
		//移動中
		break;
	case Player::Animation_Attack1:
		break;
	case Player::Animation_Attack2:
		break;
	case Player::Animation_Jump:
		//ジャンプ中
		break;
	default:
		break;
	}

}

void Player::Draw(int renderMode)
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
}