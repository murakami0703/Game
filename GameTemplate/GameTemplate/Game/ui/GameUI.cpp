#include "stdafx.h"
#include "GameUI.h"
#include "data/GameData.h"

//各UI処理クラス。
#include "ui/PlayerHPUI.h"
#include "itemui/ItemUI.h"
#include "ui/SoulUI.h"

GameUI* GameUI::m_instance = nullptr;

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const CVector3 ITEM_FRAME1_POS = { 460.0f,-240.0f,0.0f };		//枠1の座標
const CVector3 ITEM_FRAME2_POS = { 560.0f,-120.0f,0.0f };		//枠2の座標
const CVector3 ITEM_FRAME3_POS = { 475.0f,-50.0f,0.0f };		//枠3の座標
const CVector3 ITEM_FRAME4_POS = { 545.0f,-3.0f,0.0f };		//枠4の座標

const CVector3 ITEM_FRAME1_SCALE = { 0.8f,0.8f,0.8f };		//枠1拡大率
const CVector3 ITEM_FRAME234_SCALE = { 0.7f,0.7f,0.7f };		//枠2～4拡大率

const CVector3 ITEM_SELECT_FRAME_POS = { 460.0f,-240.0f,0.0f };		//選択枠の座標
const CVector3 LB_SPRITE_POS = { 585.0f,-250.0f,0.0f };		//Lの座標
const CVector3 RB_SPRITE_POS = { 605.0f,20.0f,0.0f };		//ZLの座標
const CVector3 END_SPRITE_POS = { 505.0f,14.0f,0.0f };		//端の座標

const CVector3 SELECTFRAME_RB_SPRITE_SCALE = { 0.7f,0.7f,0.7f };			//L拡大率
const CVector3 LB_SPRITE_SCALE = { 0.8f,0.8f,0.8f };			//L拡大率
const CVector3 END_SPRITE_SCALE = { 0.6f,0.6f,0.6f };			//端拡大率

const int FRAME_BIGCOUNT_VALUE = 30;
const int FRAME_SMALLCOUNT_VALUE = 60;
const CVector3 SCALING_VALUE = { 0.002f,0.002f,0.002f };			//選択枠拡大値

GameUI::GameUI()
{
	m_instance = this;
}
GameUI::~GameUI()
{
}
bool GameUI::Start()
{
	//アイテム枠
	{
		//0番→ItemCase1
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case1.dds", 275.0f, 275.0f);
		r->SetPosition(ITEM_FRAME1_POS);
		r->SetScale(ITEM_FRAME1_SCALE);
		r->SetAlpha(0.9f);
		m_spriteRender.push_back(r);
		//1番→ItemCase2
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case2.dds", 247.0f, 247.0f);
		r->SetPosition(ITEM_FRAME2_POS);
		r->SetScale(ITEM_FRAME234_SCALE);
		r->SetAlpha(0.6f);
		m_spriteRender.push_back(r);
		//2番→ItemCase3
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case3.dds", 204.0f, 204.0f);
		r->SetPosition(ITEM_FRAME3_POS);
		r->SetScale(ITEM_FRAME234_SCALE);
		r->SetAlpha(0.4f);
		m_spriteRender.push_back(r);
		//3番→ItemCase4
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case4.dds", 148.0f, 148.0f);
		r->SetPosition(ITEM_FRAME4_POS);
		r->SetScale(ITEM_FRAME234_SCALE);
		r->SetAlpha(0.2f);
		m_spriteRender.push_back(r);
		//4番→Itemwaku
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/waku.dds", 363.0f, 362.0f);
		r->SetPosition(ITEM_SELECT_FRAME_POS);
		r->SetScale(SELECTFRAME_RB_SPRITE_SCALE);
		m_spriteRender.push_back(r);
		//5番→Itemhasi
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/hasi.dds", 70.0f, 63.0f);
		r->SetPosition(END_SPRITE_POS);
		r->SetScale(END_SPRITE_SCALE);
		m_spriteRender.push_back(r);
		//6番→ItemL
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/L.dds", 100.0f, 148.0f);
		r->SetPosition(LB_SPRITE_POS);
		r->SetScale(LB_SPRITE_SCALE);
		m_spriteRender.push_back(r);
		//7番→ItemZL
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/ZL.dds", 102.0f, 79.0f);
		r->SetPosition(RB_SPRITE_POS);
		r->SetScale(SELECTFRAME_RB_SPRITE_SCALE);
		m_spriteRender.push_back(r);
	}

	//プレイヤーHPUI
	g_goMgr->NewGameObject<PlayerHPUI>();
	//アイテムUI
	g_goMgr->NewGameObject<ItemUI>();
	//魂UI
	g_goMgr->NewGameObject<SoulUI>();

	return true;
}

void GameUI::ScalingSelectCase() {
	//選択枠の拡大縮小
	if (m_scalingCount > FRAME_SMALLCOUNT_VALUE) {
		m_scalingCount = 0;
	}
	else if (m_scalingCount <= FRAME_BIGCOUNT_VALUE) {
		m_itemSelectFrameScale += SCALING_VALUE;
	}
	else{
		m_itemSelectFrameScale -= SCALING_VALUE;
	}
	m_scalingCount++;
	m_spriteRender[4]->SetScale(m_itemSelectFrameScale);
}


void GameUI::OnlyDelete()
{
	//全部消す。
	//sprite。
	for (int i = 0; i < m_spriteRender.size(); i++) {
		g_goMgr->DeleteGameObject(m_spriteRender[i]);
	}
	//フォント

	g_goMgr->DeleteGameObject(this);
}

void GameUI::Update()
{
	GameData* m_gamedate = GameData::GetInstance();

	
	ScalingSelectCase();

	//ボスが倒されたのでUI消す。
	if (m_gamedate->ResultFlag() == true) {
		OnlyDelete();
	}
}
