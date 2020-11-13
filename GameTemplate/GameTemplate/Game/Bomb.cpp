#include "stdafx.h"
#include "item/Bomb.h"
#include "player/Player.h"
#include "data/GameData.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const CVector3 BOMB_SCALE = { 0.5f,0.5f ,0.5f };			//爆弾の拡大率。

const float DISPOSITION_ADD_Y = -250.0f;					//配置する場所のY軸の加算値。
const float DISPOSITION_ADD_X_OR_Z = 400.0f;				//配置する場所のZ軸またはX軸の加算値。
const float BOMB_MOVE_SPEED = 1.0f;							//爆弾の移動速度。
const float BOMB_END_POSITION = 2.0f;						//爆弾の終了処理場所。

Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}
bool Bomb::Start()
{

	//スキンモデル。
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/Bum.cmo");
	m_position = Player::GetInstance()->GetPosition();
	m_position.y += 250.0f;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(BOMB_SCALE);

	return true;
}

void Bomb::Parabolic()
{
	//投げる場所を決める。

}
void Bomb::MoveBomb() {

	//移動処理。
	m_position = Player::GetInstance()->GetPosition();
	m_position.y += 250.0f;

}

void Bomb::InUse()
{
	//使用中。
	GameData* gamedata = GameData::GetInstance();

	MoveBomb();

	
	//爆弾の処理終了。
	if ((m_position - disPosition).Length() <= BOMB_END_POSITION) {
		gamedata->SetItemInUseFlag(false);
	}

	m_skinModelRender->SetPosition(m_position);

}
void Bomb::EndUse()
{
	//終わり。
	//爆発させる。

}
