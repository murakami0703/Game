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
	Player* m_playerPos = Player::GetInstance();
	
	m_StartPoint = m_playerPos->GetPosition();	//始点
	CVector3 Pos = m_position;
	Pos.y += 100.0f;
	m_endPoint = Pos;	//終点
	CVector3 Vec = Pos - m_playerPos->GetPosition();	//始点から終点に伸びるベクトル
	Vec /= 4.0f;
	CVector3 Pos2 = m_playerPos->GetPosition() + Vec;
	Pos2.y += 100.0f;
	m_middlePoint1 = Pos2;	//始点寄り
	Pos2 = Pos - Vec;
	Pos2.y = m_middlePoint1.y;
	m_middlePoint2 = Pos2;	//終点寄り



	m_catmull_U += 0.1f;
	CVector3 output_point = m_StartPoint * (1 - m_catmull_U)*(1 - m_catmull_U)*(1 - m_catmull_U) + 3 *
		m_middlePoint1 * m_catmull_U*(1 - m_catmull_U)*(1 - m_catmull_U) + 3 *
		m_middlePoint2 * m_catmull_U*m_catmull_U*(1 - m_catmull_U) +
		m_endPoint * m_catmull_U*m_catmull_U*m_catmull_U;
}

void Bum::InUse()
{
	//使用中。
	GameData* gamedate = GameData::GetInstance();

	//移動処理。
	if (g_pad[0].IsTrigger(enButtonX)) {
		m_position.x += 200.0f;
		//m_position.y -= 300.0f;
		gamedate->SetItemInUseFlag(true);
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
