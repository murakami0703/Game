#include "stdafx.h"
#include "TreasureBox.h"
#include "Player.h"
#include "EffectManager.h"
#include "Item.h"


TreasureBox::TreasureBox()
{
}


TreasureBox::~TreasureBox()
{
}

bool TreasureBox::Start() {
	m_animClips[eAnimation_Close].Load(L"Assets/animData/stage_gimmik/close_box.tka");
	m_animClips[eAnimation_Open].Load(L"Assets/animData/stage_gimmik/open_box.tka");
	//cmoファイルの読み込み。
	m_BoxModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_BoxModelRender->Init(L"Assets/modelData/Treasure_Box.cmo", m_animClips, eAnimation_Num);
	m_fowardVector = { 1.0f,0.0f,0.0f };
	m_BoxModelRender->SetPosition(m_position);
	m_BoxModelRender->SetRotation(m_rotation);
	m_BoxModelRender->SetScale(m_scale);
	m_BoxModelRender->PlayAnimation(0);

	return true;
}

void TreasureBox::Open()
{
	//開封アニメ再生
	m_BoxModelRender->PlayAnimation(1);

	if (m_BoxModelRender->IsPlayingAnimation() == false) {
		//アイテム生成。
		Item* m_item = g_goMgr->NewGameObject<Item>();
		m_item->SetPosition(m_position);
		m_item->SetRotation(m_rotation);
		m_state = eState_Opened;
	}
}
void TreasureBox::Opened()
{
}


void TreasureBox::Update()
{
	Player* player = Player::GetInstance();
	m_toPlayerVec = player->GetPosition() - m_position;

	switch (m_state)
	{
	case TreasureBox::eState_Idle:
		//攻撃中に宝箱に近づくと開くよ！！！
		if (m_toPlayerVec.Length() <= m_openYVec) {
			if (player->GetAttackflag() == true) {
				EffectManager* effect = EffectManager::GetInstance();
				effect->EffectPlayer(EffectManager::open, m_position, { 2.0f,2.0f,2.0f });
				m_state = eState_Open;
			}
		}
		break;
	case TreasureBox::eState_Open:
		Open();
		break;	
	case TreasureBox::eState_Opened:
		Opened();
		break;

	}
}