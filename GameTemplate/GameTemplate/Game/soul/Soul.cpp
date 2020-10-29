#include "stdafx.h"
#include "Soul.h"
#include "player/Player.h"
#include "data/GameData.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////
const CVector3 SOUL_SETSCALE = { 5.0f,5.0f,5.0f };	//魂の拡大値。
const int SOUL_GET = 1;		//魂を獲得
const float SOUL_DESTROY_TIME = 600.0f;	//魂の消滅時間。
const float GROUND_POSY = 430.0f;		//地面のY座標。
const float SOUL_GET_LENGTH = 50.0f;	//魂が獲得できる距離。
const float SOUL_MOVESPEED = 5.0f;		//魂の下降速度。

Soul::Soul(){}
Soul::~Soul(){}

bool Soul::Start()
{
	//アニメーションクリップのロードとループフラグの設定。
	m_animClips[eAnimation_Move].Load(L"Assets/animData/AnimaMove.tka");
	m_animClips[eAnimation_Move].SetLoopFlag(true);

	//cmoファイルの読み込み。
	m_animaModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_animaModelRender->Init(L"Assets/modelData/Anima.cmo", m_animClips, eAnimation_Num);
	m_animaModelRender->SetPosition(m_position);
	m_animaModelRender->SetScale(SOUL_SETSCALE);
	m_animaModelRender->PlayAnimation(eAnimation_Move);

	m_animaModelRender->SetShadowCaster(true);


	return  true;
}

void Soul::Appear()
{
	//出現中。
	//魂が地面から離れていたら下降します。
	if (m_position.y <= GROUND_POSY) {
		//地面付近なので取得できるようになるよ！
		m_timer++;
		Player* player = Player::GetInstance();
		if ((player->GetPosition() - m_position).Length() < SOUL_GET_LENGTH) {
			//獲得
			m_state = Anima_Get;

		}
		else if (m_timer > SOUL_DESTROY_TIME) {
			//消滅。
			m_state = Anima_Destroy;
		}
	}
	else {
		//下降。
		m_position.y -= SOUL_MOVESPEED;
	}

}
void Soul::Get()
{
	//取得したよ！！
	GameData::GetInstance()->SoulCalc(SOUL_GET);
	m_state = Anima_Destroy;	//獲得したので消滅させる。
}
void Soul::Destroy()
{
	//消滅。
	g_goMgr->DeleteGameObject(m_animaModelRender);
	g_goMgr->DeleteGameObject(this);
}

void Soul::Update()
{
	switch (m_state)
	{
	case Soul::Anima_Appear:
		//出現中。
		Appear();
		break;
	case Soul::Anima_Get:
		//獲得。
		Get();
		break;
	case Soul::Anima_Destroy:
		//消滅。
		Destroy();
		break;
	}

	//ワールド行列の更新。
	m_animaModelRender->SetPosition(m_position);
	m_animaModelRender->SetScale(SOUL_SETSCALE);

}

