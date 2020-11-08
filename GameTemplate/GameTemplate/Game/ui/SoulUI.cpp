#include "stdafx.h"
#include "ui/SoulUI.h"
#include "data/GameData.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const CVector3 SOUL_FRAME_POS = { -800.0f,200.0f,0.0f };			//フレームの座標。
const float SOUL_FLANE_ALPHA = 0.8f;								//フレームの透明度。
const CVector3 SOUL_POS = { -840.0f,200.0f,0.0f };					//魂の座標。
const CVector3 SOULANDFRAME_SCALE = { 0.35f,0.35f,0.35f };			//魂とフレームの拡大率。

const float SOUL_FRAME_UPBOUND = -500.0f;							//フレームのバウンド時X軸に上昇する位置。
const float SOUL_FRAME_DOWNBOUND = -540.0f;							//フレームのバウンド時X軸に下降する位置。
const float SOUL_ICON_UPBOUND = -540.0f;							//魂アイコンのバウンド時X軸に上昇する位置。
const float SOUL_ICON_DOWNBOUND = -580.0f;							//魂アイコンのバウンド時X軸に下降する位置。

const float UPBOUND_ADD = 10.0f;									//上昇バウンド時加算する値。
const float DOWNBOUND_ADD = 5.0f;									//下降バウンド時加算する値。

const CVector2 SOUL_COUNT_FONT_POS = { -780.0f,230.0f };			//カウントフォントの座標。
const float SOUL_COUNT_FONT_SCALE = 2.0f;							//カウントフォントの拡大率。

const float SOUL_COUNT_FONT_X_UPBOUND = -480.0f;					//魂カウントフォントのバウンド時X軸に上昇する位置。
const float SOUL_COUNT_FONT_X_DOWNBOUND = -520.0f;					//魂カウントフォントのバウンド時X軸に下降する位置。

const float SOUL_COUNT_FONT_UPBOUND = 250.0f;						//カウントフォントのバウンド時Y軸に上昇する位置。
const float SOUL_COUNT_FONT_DOWNBOUND = 230.0f;						//カウントフォントのバウンド時Y軸に下降する位置。
const float SOUL_COUNT_FONT_BOUND_ADD = 5.0f;						//カウントフォントのバウンド時加算する値。

const int INDICATE_END = 200;										//魂カウントUIの表示終了タイム。
const float RETURN_MOVE_SPEED = 10.0f;								//元に戻すときの移動速度。

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

	swprintf(soulNum, MAX_PATH - 1, L"%02d", m_soulNowNum);
	m_soulFont->SetText(soulNum);
	m_soulFont->SetPosition(SOUL_COUNT_FONT_POS);
	m_soulFont->SetScale(SOUL_COUNT_FONT_SCALE);

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
	CVector3 m_framePos = m_spriteRender[0]->GetPosition();		//フレーム座標。
	CVector3 m_soulIconPos = m_spriteRender[1]->GetPosition();	//魂アイコン座標。
	CVector2 m_soulCountPos = m_soulFont->GetPosition();		//フォント座標。
	
	if (m_framePos.x < SOUL_FRAME_UPBOUND &&
		m_soulIconPos.x < SOUL_ICON_UPBOUND &&
		m_soulCountPos.x < SOUL_COUNT_FONT_X_UPBOUND &&
		bound == false) {
		m_framePos.x += UPBOUND_ADD;
		m_soulIconPos.x += UPBOUND_ADD;
		m_soulCountPos.x += UPBOUND_ADD;
	}
	else {
		bound = true;
		//ここからバウンド処理
		if (m_framePos.x > SOUL_FRAME_DOWNBOUND &&
			m_soulIconPos.x > SOUL_ICON_DOWNBOUND &&
			m_soulCountPos.x > SOUL_COUNT_FONT_X_DOWNBOUND &&
			bound == true) {
			m_framePos.x -= DOWNBOUND_ADD;
			m_soulIconPos.x -= DOWNBOUND_ADD;
			m_soulCountPos.x -= DOWNBOUND_ADD;
		}
		else {
			//バウンド終了、次の処理へ...。
			bound = false;
			m_soulUiState = SoulUI_SoulCount;
		}

	}
	m_spriteRender[0]->SetPosition(m_framePos);
	m_spriteRender[1]->SetPosition(m_soulIconPos);
	m_soulFont->SetPosition(m_soulCountPos);

}		
void SoulUI::SoulCount()
{
	//魂の加算。
	GameData* gamedate = GameData::GetInstance();
	m_soulNowNum++;
	swprintf(soulNum, MAX_PATH - 1, L"%02d", gamedate->GetSoul());
	m_soulFont->SetText(soulNum);
	m_soulUiState = SoulUI_FontBoundMove;

}
void SoulUI::FontBoundMove()
{
	//魂獲得時フォントのカウントをバウンドさせる処理。
	//バウンド処理。	
	CVector2 m_position = m_soulFont->GetPosition();	//フォント座標。

	if (m_position.y < SOUL_COUNT_FONT_UPBOUND && bound == false) {
		m_position.y += SOUL_COUNT_FONT_BOUND_ADD;
	}
	else {
		bound = true;
		//ここからバウンド処理
		if (bound == true && m_position.y > SOUL_COUNT_FONT_DOWNBOUND) {
			m_position.y -= SOUL_COUNT_FONT_BOUND_ADD;
		}
		else {
			//バウンド終了、次の処理へ...。
			bound = false;
			m_soulUiState = SoulUI_Indicate;
		}

	}
	m_soulFont->SetPosition(m_position);

}
void SoulUI::SoulUIIndicate()
{
	GameData* gamedate = GameData::GetInstance();
	//一定時間だけ表示状態のまま保つ。
	m_indicateTimer++;

	if (m_indicateTimer >= INDICATE_END) {
		m_indicateTimer = 0;
		m_soulUiState = SoulUI_Return;
	}

	//もし表示状態中に魂を取得したら
	//カウントバウンド状態に戻ります。
	if (gamedate->GetSoul() > m_soulNowNum) {
		m_indicateTimer = 0;
		m_soulUiState = SoulUI_SoulCount;
	}
}
void SoulUI::SoulUIReturn()
{
	//元の状態に戻す。
	CVector3 m_framePos = m_spriteRender[0]->GetPosition();		//フレーム座標。
	CVector3 m_soulIconPos = m_spriteRender[1]->GetPosition();	//魂アイコン座標。
	CVector2 m_soulCountPos = m_soulFont->GetPosition();		//フォント座標。

	if (m_framePos.x > SOUL_FRAME_POS.x &&
		m_soulIconPos.x > SOUL_POS.x &&
		m_soulCountPos.x > SOUL_COUNT_FONT_POS.x) {
		m_framePos.x -= RETURN_MOVE_SPEED;
		m_soulIconPos.x -= RETURN_MOVE_SPEED;
		m_soulCountPos.x -= RETURN_MOVE_SPEED;
	}
	else {
		m_soulUiState = SoulUI_Default;
	}

	m_spriteRender[0]->SetPosition(m_framePos);
	m_spriteRender[1]->SetPosition(m_soulIconPos);
	m_soulFont->SetPosition(m_soulCountPos);

}
void SoulUI::Update()
{

	switch (m_soulUiState)
	{
	case SoulUI::SoulUI_Default:
		SoulUIDefault();
		break;
	case SoulUI::SoulUI_GetMove:
		SoulUIGetMove();
		break;
	case SoulUI::SoulUI_SoulCount:
		SoulCount();
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

}

