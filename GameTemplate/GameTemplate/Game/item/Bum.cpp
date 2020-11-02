#include "stdafx.h"
#include "item/Bum.h"
#include "player/Player.h"
#include "data/GameData.h"


/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const CVector3 BOMB_SCALE = { 0.5f,0.5f ,0.5f };
Bum::Bum()
{
}


Bum::~Bum()
{
}
bool Bum::Start()
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

void Bum::Parabolic()
{
	Player* player = Player::GetInstance();
	//プレイヤーの向きによって放り投げる位置を決めます。
	//CMath::DegToRad(359.0f)角度　IF
	if (player->GetRotation().y == CMath::DegToRad(80.0f)) {
		//左
	}
	else if (player->GetRotation().y == CMath::DegToRad(-80.0f)) {
		//右
	}
	else if (player->GetRotation().y == CMath::DegToRad(0.0f)) {
		//上
	}
	else if (player->GetRotation().y == CMath::DegToRad(110.0f)) {
		//下
	}


}

void Bum::InUse()
{
	//使用中。
	GameData* gamedate = GameData::GetInstance();

	//移動処理。
	if (g_pad[0].IsTrigger(enButtonX)) {
	}
	else if(gamedate->GetItemInUseFlag() != true){
		m_position = Player::GetInstance()->GetPosition();
		m_position.y += 250.0f;
	}
	m_skinModelRender->SetPosition(m_position);

}
void Bum::EndUse()
{
	//終わり。


}
