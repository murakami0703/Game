#include "stdafx.h"
#include "SoulUI.h"
#include "GameData.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const CVector3 SOUL_FRAME_POS = { -800.0f,200.0f,0.0f };			//フレームの座標
const float SOUL_FLANE_ALPHA = 0.8f;								//フレームの透明度。
const CVector3 SOUL_POS = { -575.0f,200.0f,0.0f };					//魂の座標
const CVector3 SOULANDFRAME_SCALE = { 0.35f,0.35f,0.35f };			//魂とフレームの拡大率


SoulUI::SoulUI()
{
}


SoulUI::~SoulUI()
{
}

bool SoulUI::Start()
{
	//0番→フレーム
	m_soulRender = g_goMgr->NewGameObject<SpriteRender>();
	m_soulRender->Init(L"Assets/sprite/Ui_SouiFrame.dds", 800.0f, 300.0f);
	m_soulRender->SetPosition(SOUL_FRAME_POS);
	m_soulRender->SetScale(SOULANDFRAME_SCALE);
	m_soulRender->SetAlpha(SOUL_FLANE_ALPHA);
	m_spriteRender.push_back(m_soulRender);

	//1番→魂
	m_soulRender = g_goMgr->NewGameObject<SpriteRender>();
	m_soulRender->Init(L"Assets/sprite/Ui_Soui.dds", 400.0f, 300.0f);
	m_soulRender->SetPosition(SOUL_POS);
	m_soulRender->SetScale(SOULANDFRAME_SCALE);
	m_spriteRender.push_back(m_soulRender);

	//魂カウントフォントの設定。
	GameData* gamedate = GameData::GetInstance();
	m_soulFont = g_goMgr->NewGameObject<FontRender>();
	m_soulNowNum = gamedate->GetSoul();
	wchar_t text[MAX_PATH];
	swprintf(text, MAX_PATH - 1, L"%02d", m_soulNowNum);
	m_soulFont->SetText(text);
	m_soulFont->SetScale(2.0f);
	m_soulFont->SetPosition({ -490.0f,230.0f });

	return true;
}
void SoulUI::SoulUIDefault()
{
	//通常状態。(非表示）
	GameData* gamedate = GameData::GetInstance();

	//魂を収集したとき。
	if (gamedate->GetSoul() > m_soulNowNum) {
		m_soulUiState = SoulUI_GetMove;
	}

}
void SoulUI::SoulUIGetMove()
{
	//魂獲得時所持バーの出現処理。
	//リザルト台座を表示。
	//右から表示させる。
	CVector3 m_position = m_spriteRender[0]->GetPosition();	//座標。

	if (m_position.x < -500.0f && bound == false) {
		m_position.x += 20.0f;
	}
	else {
		bound = true;
		//ここからバウンド処理
		if (bound == true && m_position.x > -530.0f) {
			m_position.x -= 5.0f;
		}
		else {
			//バウンド終了、次の処理へ...。
			bound = false;
			m_soulUiState = SoulUI_FontBoundMove;
		}

	}
	m_spriteRender[0]->SetAlpha(1.0f);
	m_spriteRender[0]->SetPosition(m_position);
}
void SoulUI::FontBoundMove()
{
	//魂獲得時フォントのカウントをバウンドさせる処理。
}
void SoulUI::SoulUIIndicate()
{
	//一定時間だけ表示状態のまま保つ。
}
void SoulUI::SoulUIReturn()
{
	//元の状態に戻す。
}
void SoulUI::Update()
{
	GameData* gamedate = GameData::GetInstance();

	switch (m_soulUiState)
	{
	case SoulUI::SoulUI_Default:
		SoulUIDefault();
		break;
	case SoulUI::SoulUI_GetMove:
		SoulUIGetMove();
		break;
	case SoulUI::SoulUI_FontBoundMove:
		FontBoundMove();
		break;
	case SoulUI::SoulUI_Indicate:
		SoulUIIndicate();
		break;
	case SoulUI::SoulUI_Return:
		SoulUIReturn();
		break;
	}

	//魂の加算。
	//wchar_t text[MAX_PATH];
	//swprintf(text, MAX_PATH - 1, L"%02d", gamedate->GetSoul());
	//m_soulFont->SetText(text);
	//m_soulNowNum++;

}

