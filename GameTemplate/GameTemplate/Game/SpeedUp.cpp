#include "stdafx.h"
#include "SpeedUp.h"
#include "Player.h"
#include "GameData.h"
#include "EffectManager.h"


const CVector3 ITEMFRAME_SET_POTITION = { -600.0f,100.0f ,0.0f };		//フレームの座標。
const CVector3 ITEMFRAME_SET_SCALE = { 1.5f,1.5f ,1.5f };			//フレームの拡大率。

const CVector3 ITEM_SET_POTITION = { -600.0f,100.0f ,0.0f };		//アイテムの座標。
const CVector3 ITEM_SET_SCALE = { 0.65f,0.65f ,0.65f };			//アイテムの拡大率。

const float ICON_INCREASE_TIME = 30.0f;						//アイコンの明るさを増加させる時間。
const float ICON_DECREASE_TIME = 60.0f;						//アイコンの明るさを減少させる時間。
const float ICON_DELTA_ALPHA = 0.7f / 30.0f;				//変位させる透明度の値。
const float ICON_TIMER_RESET = 0.0f;						//アイコンのタイマーを初期状態にする。

SpeedUp::SpeedUp()
{
}


SpeedUp::~SpeedUp()
{
}

bool SpeedUp::Start()
{

	//左上に表示するアイコン関係のsprite
	{
		//0番→枠
		m_frameSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_frameSprite->Init(L"Assets/sprite/itemframe.dds", 75.0f, 50.0f);
		m_frameSprite->SetPosition(ITEMFRAME_SET_POTITION);
		m_frameSprite->SetScale(ITEMFRAME_SET_SCALE);

		//1番→スピードアップ薬
		m_itemiconSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemiconSprite->Init(L"Assets/sprite/SpeedUp.dds", 125.0f, 125.0f);
		m_itemiconSprite->SetPosition(ITEM_SET_POTITION);
		m_itemiconSprite->SetScale(ITEM_SET_SCALE);
	}

	return true;
}
void SpeedUp::InUse()
{
	//使用中。
	//アイコンの点滅。
	m_flashingTimer++;
	if (m_flashingTimer <= ICON_INCREASE_TIME) {
		m_itemiconSprite->DeltaAlpha(ICON_DELTA_ALPHA);
	}
	else if (m_flashingTimer <= ICON_DECREASE_TIME)
	{
		m_itemiconSprite->DeltaAlpha(-ICON_DELTA_ALPHA);
	}
	else {
		m_flashingTimer = ICON_TIMER_RESET;
	}

}
void SpeedUp::EndUse()
{
	//終わり。
	g_goMgr->DeleteGameObject(this);
}
void SpeedUp::Update() {

}

