#include "stdafx.h"
#include "Anima.h"
#include "AnimaManeger.h"
#include "GameData.h"

Anima::Anima()
{
	//アニメーションクリップのロード。
	m_animClips[Anima_Move].Load(L"Assets/animData/AnimaMove.tka");
	//ループフラグの設定。
	m_animClips[Anima_Move].SetLoopFlag(true);
	
	m_animaModel.Init(L"Assets/modelData/Anima.cmo");
	m_scale = { 3.0f,3.0f,3.0f };
	m_animation.Init(m_animaModel, m_animClips, Anima_Num);	//アニメーションの初期化

}


Anima::~Anima()
{
}

void Anima::Appear(Player* player)
{	//出現中。
	m_timer++;

	if ((player->GetPosition() - m_position).Length() < 50.0f) {
		//取得
		m_state = Anima_Get;

	}
	else if (m_timer > m_destroyTimer) {
		//消滅。
		m_state = Anima_Destroy;
	}
	m_animation.Play(Anima_Move, 0.5f);
}

void Anima::Get()
{	//取得したよ！！
	GameData::GetInstance()->AnimaCalc(1);
	AnimaManeger::GetInstance()->DeleteAnima(this);
}
void Anima::Destroy()
{	//時間経過のため消滅。
	AnimaManeger::GetInstance()->DeleteAnima(this);

}
void Anima::Update(Player* player)
{
	m_position.y = 50.0f;
	m_animation.Update(0.05f);//アニメーション再生
	switch (m_state)
	{
	case Anima::Anima_Appear:
		Appear(player);
		break;
	case Anima::Anima_Get:
		Get();
		break;
	case Anima::Anima_Destroy:
		Destroy();
		break;
	}
	//ワールド行列の更新。
	m_animaModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_animaModel.Update();
}

void Anima::Draw(EnRenderMode renderMode)
{
	m_animaModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
}

