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

void Bum::InUse()
{
	//使用中。
	GameData* gamedate = GameData::GetInstance();
	gamedate->SetItemInUseFlag(true);

	//移動処理。
	m_position = Player::GetInstance()->GetPosition();
	m_position.y += 250.0f;
	m_skinModelRender->SetPosition(m_position);

	if (g_pad[0].IsTrigger(enButtonX)) {
		m_position.x += 400.0f;
		m_position.y -= 300.0f;
	}
}
void Bum::EndUse()
{
	//終わり。


}
