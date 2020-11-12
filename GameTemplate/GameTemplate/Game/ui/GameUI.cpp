#include "stdafx.h"
#include "GameUI.h"
#include "data/GameData.h"


GameUI* GameUI::m_instance = nullptr;

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const CVector3 ITEM_FRAME1_POS = { 460.0f,-240.0f,0.0f };		//�g1�̍��W�B
const CVector3 ITEM_FRAME2_POS = { 560.0f,-120.0f,0.0f };		//�g2�̍��W�B
const CVector3 ITEM_FRAME3_POS = { 475.0f,-50.0f,0.0f };		//�g3�̍��W�B
const CVector3 ITEM_FRAME4_POS = { 545.0f,-3.0f,0.0f };			//�g4�̍��W�B

const float ITEM_FRAME1_ALPHA = 0.9f;		//�g1�̓����x�B
const float ITEM_FRAME2_ALPHA = 0.6f;		//�g2�̓����x�B
const float ITEM_FRAME3_ALPHA = 0.4f;		//�g3�̓����x�B
const float ITEM_FRAME4_ALPHA = 0.2f;		//�g4�̓����x�B

const CVector3 ITEM_FRAME1_SCALE = { 0.8f,0.8f,0.8f };				//�g1�g�嗦�B
const CVector3 ITEM_FRAME234_SCALE = { 0.7f,0.7f,0.7f };			//�g2�`4�g�嗦�B

const CVector3 ITEM_SELECT_FRAME_POS = { 460.0f,-240.0f,0.0f };		//�I��g�̍��W�B
const CVector3 LB_SPRITE_POS = { 585.0f,-250.0f,0.0f };				//L�̍��W�B
const CVector3 RB_SPRITE_POS = { 605.0f,20.0f,0.0f };				//ZL�̍��W�B
const CVector3 END_SPRITE_POS = { 505.0f,14.0f,0.0f };				//�[�̍��W�B

const CVector3 SELECTFRAME_RB_SPRITE_SCALE = { 0.7f,0.7f,0.7f };	//ZL,�t���[���̊g�嗦�B
const CVector3 LB_SPRITE_SCALE = { 0.8f,0.8f,0.8f };				//L�̊g�嗦�B
const CVector3 END_SPRITE_SCALE = { 0.6f,0.6f,0.6f };				//�[�̊g�嗦�B

const int FRAME_BIGCOUNT_VALUE = 30;								//�g�傳���鎞�ԁB�P�ʁF�t���[��
const int FRAME_SMALLCOUNT_VALUE = 60;								//�k�������鎞�ԁB�P�ʁF�t���[��
const CVector3 SCALING_VALUE = { 0.002f,0.002f,0.002f };			//�I��g�g��l�B

GameUI::GameUI()
{
	m_instance = this;
}
GameUI::~GameUI()
{
}
bool GameUI::Start()
{
	//�A�C�e���g
	{
		//0�ԁ�ItemCase1
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case1.dds", 275.0f, 275.0f);
		r->SetPosition(ITEM_FRAME1_POS);
		r->SetScale(ITEM_FRAME1_SCALE);
		r->SetAlpha(ITEM_FRAME1_ALPHA);
		m_spriteRender.push_back(r);
		//1�ԁ�ItemCase2
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case2.dds", 247.0f, 247.0f);
		r->SetPosition(ITEM_FRAME2_POS);
		r->SetScale(ITEM_FRAME234_SCALE);
		r->SetAlpha(ITEM_FRAME2_ALPHA);
		m_spriteRender.push_back(r);
		//2�ԁ�ItemCase3
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case3.dds", 204.0f, 204.0f);
		r->SetPosition(ITEM_FRAME3_POS);
		r->SetScale(ITEM_FRAME234_SCALE);
		r->SetAlpha(ITEM_FRAME3_ALPHA);
		m_spriteRender.push_back(r);
		//3�ԁ�ItemCase4
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case4.dds", 148.0f, 148.0f);
		r->SetPosition(ITEM_FRAME4_POS);
		r->SetScale(ITEM_FRAME234_SCALE);
		r->SetAlpha(ITEM_FRAME4_ALPHA);
		m_spriteRender.push_back(r);
		//4�ԁ�Itemwaku
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/waku.dds", 363.0f, 362.0f);
		r->SetPosition(ITEM_SELECT_FRAME_POS);
		r->SetScale(SELECTFRAME_RB_SPRITE_SCALE);
		m_spriteRender.push_back(r);
		//5�ԁ�Itemhasi
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/hasi.dds", 70.0f, 63.0f);
		r->SetPosition(END_SPRITE_POS);
		r->SetScale(END_SPRITE_SCALE);
		m_spriteRender.push_back(r);
	}
	//RB,LB����
	{
		//6�ԁ�ItemL
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/L.dds", 100.0f, 148.0f);
		r->SetPosition(LB_SPRITE_POS);
		r->SetScale(LB_SPRITE_SCALE);
		m_spriteRender.push_back(r);
		//7�ԁ�ItemZL
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/ZL.dds", 102.0f, 79.0f);
		r->SetPosition(RB_SPRITE_POS);
		r->SetScale(SELECTFRAME_RB_SPRITE_SCALE);
		m_spriteRender.push_back(r);
	}

	//�v���C���[HPUI
	m_playeHPUi = g_goMgr->NewGameObject<PlayerHPUI>();
	//�A�C�e��UI
	m_itemUi = g_goMgr->NewGameObject<ItemUI>();
	//��UI
	m_soulUi = g_goMgr->NewGameObject<SoulUI>();

	return true;
}

void GameUI::ScalingSelectCase() {

	//�I��g(�I�����W)�̊g��k��
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
	//�S�������B
	//sprite�B
	for (int i = 0; i < m_spriteRender.size(); i++) {
		g_goMgr->DeleteGameObject(m_spriteRender[i]);
	}
	//�e��@�\�̍폜
	g_goMgr->DeleteGameObject(m_playeHPUi);
	g_goMgr->DeleteGameObject(m_itemUi);
	g_goMgr->DeleteGameObject(m_soulUi);
	g_goMgr->DeleteGameObject(this);

}

void GameUI::Update()
{
	GameData* m_gamedate = GameData::GetInstance();

	ScalingSelectCase();	//�I��g�̊g��k�������B

	//�{�X���|���ꂽ�̂�UI�����B
	if (m_gamedate->ResultFlag() == true) {
		OnlyDelete();
	}
	//�Q�[���I�[�o�[�ɂȂ����̂�UI�����B
	if (m_gamedate->GameOverFlag() == true) {
		OnlyDelete();
	}

}
