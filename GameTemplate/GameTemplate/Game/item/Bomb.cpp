#include "stdafx.h"
#include "Bomb.h"
#include "player/Player.h"
#include "data/GameData.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const CVector3 BOMB_SCALE = { 0.5f,0.5f ,0.5f };			//爆弾の拡大率。

const float DISPOSITION_ADD_Y = -250.0f;					//配置する場所のY軸の加算値。
const float DISPOSITION_ADD_X_OR_Z = 400.0f;				//配置する場所のZ軸またはX軸の加算値。
const float BOMB_MOVE_SPEED = 5.0f;							//爆弾の移動速度。
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

	Player* player = Player::GetInstance();
	//プレイヤーの向きによって放り投げる位置を決めます。
	//CMath::DegToRad(359.0f)角度　IF
	if (player->GetRotation().y == CMath::DegToRad(80.0f)) {
		//左
		disPosition.x = m_position.x - DISPOSITION_ADD_X_OR_Z;
		disPosition.y = m_position.y + DISPOSITION_ADD_Y;

	}
	else if (player->GetRotation().y == CMath::DegToRad(-80.0f)) {
		//右
		disPosition.x = m_position.x + DISPOSITION_ADD_X_OR_Z;
		disPosition.y = m_position.y + DISPOSITION_ADD_Y;

	}
	else if (player->GetRotation().y == CMath::DegToRad(0.0f)) {
		//上
		disPosition.z = m_position.z + DISPOSITION_ADD_X_OR_Z;
		disPosition.y = m_position.y + DISPOSITION_ADD_Y;

	}
	else if (player->GetRotation().y == CMath::DegToRad(110.0f)) {
		//下
		disPosition.z = m_position.z - DISPOSITION_ADD_X_OR_Z;
		disPosition.y = m_position.y + DISPOSITION_ADD_Y;

	}


}
void Bomb::MoveBomb() {

	//移動処理。
	if (m_bombMoveFlag != false) {
		m_position = Player::GetInstance()->GetPosition();
		if (g_pad[0].IsTrigger(enButtonX)) {
			Parabolic();
			m_bombMoveFlag = false;
		}
	}
	else {
		CVector3 move = m_position - disPosition;
		move.Normalize();
		m_position += move * BOMB_MOVE_SPEED;
	}
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
