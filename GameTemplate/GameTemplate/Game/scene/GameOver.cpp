#include "stdafx.h"
#include "scene/GameOver.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const CVector3 CONTINUITY_SET_POS = { 400.0f, -200.0f, 0.0f };	//「コンティニュー」ボタンの座標。
const CVector3 EXIT_SET_POS = { 475.0f, -300.0f, 0.0f };		//「終わり」ボタンの座標。

const CVector3 GAMEOVER_SET_SCALE = { 0.7f, 0.7f, 0.7f };		//ゲームオーバーの拡大率。

const float BG_SET_MULCOLOR = 0.3f;								//BGのカラーの最終乗算値。
const float BG_DECREASE_VALUE = 0.1f;							//BGのカラーの減少値。

const float ACTIVE_TRUE = 1.0f;									//透明度(表示)。
const float ACTIVE_FALSE = 0.0f;								//透明度(非表示)。

const float GAMEOVER_SET_POSY = 400.0f;							//GameOverの初期Ｙ位置。
const float GAMEOBER_BOUND_POSY = 220.0f;						//GameOverの下降位置。
const float GAMEOVER_BOUND_SET_POSY = 250.0f;					//GameOverのバウンド後の位置。
const float GAMEOVER_MOVESPEED = 10.0f;							//GameOverの移動速度。

const float BUTTON_ACTIVE_TIME = 20.0f;							//ボタンを表示させる時間。単位：フレーム
const float CONTINUITY_FADE_DELTA_ALPHA = 1.0f / 20.0f;			//「コンティニュー」の透明度を変位させる値。
const float EXIT_FADE_DELTA_ALPHA = 0.3f / 20.0f;				//「終わり」の透明度を変位させる値。
const float BUTTON_SELECT = 1.0f;								//選択中のフォント。
const float BUTTON_NOT_SELECT = 0.3f;							//選択外のフォント。


GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}


bool GameOver::Start()
{

	//0番→GameOver
	m_spriteRender = g_goMgr->NewGameObject<SpriteRender>();
	m_spriteRender->Init(L"Assets/sprite/gameover.dds", 700.0f, 150.0f);
	m_spriteRender->SetPosition({ 0.0f,GAMEOVER_SET_POSY ,0.0f });
	m_spriteRender->SetScale(GAMEOVER_SET_SCALE);
	m_spriteRender->SetAlpha(ACTIVE_FALSE);
	m_spriteRenderArray.push_back(m_spriteRender);

	//ボタン。
	{
		//1番→Continuity
		m_spriteRender = g_goMgr->NewGameObject<SpriteRender>();
		m_spriteRender->Init(L"Assets/sprite/continuity.dds", 300.0f, 100.0f);
		m_spriteRender->SetPosition(CONTINUITY_SET_POS);
		m_spriteRender->SetAlpha(ACTIVE_FALSE);
		m_spriteRenderArray.push_back(m_spriteRender);

		//2番→Exit
		m_spriteRender = g_goMgr->NewGameObject<SpriteRender>();
		m_spriteRender->Init(L"Assets/sprite/exit.dds", 150.0f, 100.0f);
		m_spriteRender->SetPosition(EXIT_SET_POS);
		m_spriteRender->SetAlpha(ACTIVE_FALSE);
		m_spriteRenderArray.push_back(m_spriteRender);

	}
	return true;
}


void GameOver::BackGDDark()
{
	//背景を暗くしますぅ。
	if (m_mulColor > BG_SET_MULCOLOR) {
		m_mulColor -= BG_DECREASE_VALUE;
		g_goMgr->SetMainSpriteMulColor({ m_mulColor,m_mulColor, m_mulColor, ACTIVE_TRUE });
	}
	else {
		//次の処理へ。
		m_state = GameOver_Set;
	}
}
void GameOver::GameOverSet()
{
	//ゲームオーバーの文字を出す。

	CVector3 m_position = m_spriteRenderArray[0]->GetPosition();

	if (m_position.y > GAMEOBER_BOUND_POSY && m_bound == false) {
		m_position.y -= GAMEOVER_MOVESPEED;
	}
	else {
		m_bound = true;
		//ここからバウンド処理
		if (m_bound == true && m_position.y < GAMEOVER_BOUND_SET_POSY) {
			m_position.y += GAMEOVER_MOVESPEED;
		}
		else {
			//バウンド終了、次の処理へ...。
			m_bound = false;
			m_state = SelectButton_Set;
		}

	}
	m_spriteRenderArray[0]->SetAlpha(1.0f);
	m_spriteRenderArray[0]->SetPosition(m_position);

}
void GameOver::SelectButtonSet()
{
	//選択ボタンの表示。
	//透明度を加算して表示させます。
	m_buttonActiveTimer++;
	if(m_buttonActiveTimer < BUTTON_ACTIVE_TIME) {
		m_spriteRenderArray[1]->DeltaAlpha(CONTINUITY_FADE_DELTA_ALPHA);
		m_spriteRenderArray[2]->DeltaAlpha(EXIT_FADE_DELTA_ALPHA);
	}
	else{
		m_state = Button_Select;
	}

}

void GameOver::ButtonSelect()
{
	//ボタン選択。
	if (g_pad[0].IsTrigger(enButtonA)) {
		m_spriteRenderArray[1]->SetAlpha(ACTIVE_FALSE);
		m_spriteRenderArray[2]->SetAlpha(ACTIVE_FALSE);
		//m_se = g_goMgr->NewGameObject<CSoundSource>();
		//m_se->Init(L"Assets/sound/Decision.wav");
		//m_se->SetVolume(DECIDED_SE_VOLUME);
		//m_se->Play(false);
		m_state = Scene_Switching;
	}
	else if (m_buttonState == Button_Exit && g_pad[0].IsTrigger(enButtonUp)) {
		//「コンティニュー」を選択する。
		m_buttonState = Button_Continuity;
		m_spriteRenderArray[1]->SetAlpha(BUTTON_SELECT);
		m_spriteRenderArray[2]->SetAlpha(BUTTON_NOT_SELECT);
		//m_se = g_goMgr->NewGameObject<CSoundSource>();
		//m_se->Init(L"Assets/sound/SelectButton.wav");
		//m_se->SetVolume(SELECT_SE_VOLUME);
		//m_se->Play(false);
	}
	else if (m_buttonState == Button_Continuity && g_pad[0].IsTrigger(enButtonDown)) {
		//「終わり」を選択する。
		m_buttonState = Button_Exit;
		m_spriteRenderArray[1]->SetAlpha(BUTTON_NOT_SELECT);
		m_spriteRenderArray[2]->SetAlpha(BUTTON_SELECT);
		//m_se = g_goMgr->NewGameObject<CSoundSource>();
		//m_se->Init(L"Assets/sound/SelectButton.wav");
		//m_se->SetVolume(SELECT_SE_VOLUME);
		//m_se->Play(false);
	}

}

void GameOver::Continuity()
{
	//コンティニュー。
	//色々元の状態に戻しましょう。
}
void GameOver::Exit()
{
	//終わり。
	//全部消します。
}

void GameOver::SceneSwitching()
{
	//シーン切り替え。
	switch (m_buttonState)
	{
	case GameOver::Button_Continuity:
		Continuity();
		break;
	case GameOver::Button_Exit:
		Exit();
		break;
	}
}


void GameOver::Update()
{
	switch (m_state)
	{
	case GameOver::BackGD_Dark:
		BackGDDark();
		break;
	case GameOver::GameOver_Set:
		GameOverSet();
		break;
	case GameOver::SelectButton_Set:
		SelectButtonSet();
		break;
	case GameOver::Button_Select:
		ButtonSelect();
		break;
	case GameOver::Scene_Switching:
		SceneSwitching();
		break;
	}	


}

