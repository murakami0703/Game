#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "FadeIn.h"

Title* Title::m_instance = nullptr;

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////
const CVector2 m_startFontPos = { 250.0f,-250.0f };	//「はじめる」の座標
const CVector2 m_loadFontPos = { 460.0f,-250.0f };		//「つづける」の座標
const float m_startFontScale = 1.50f;	//「はじめる」の座標

const float m_lightsUpTime = 45.0f;
const float m_lightsOffTime = 90.0f;
const float m_lightAlpha = 0.7f / 45.0f;

const CVector4 a = { 1.0f,1.0f ,1.0f ,1.0f };		//「つづける」の座標




Title::Title(){}
Title::~Title(){}

bool Title::Start()
{
	m_instance = this;

	//諸々
	{
		//0番→Title(背景)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/title.dds", 1280.0f, 720.0f);
		m_titleSprite->SetMulColor({ 0.0f,0.0f ,0.0f ,1.0f });
		m_spriteRender.push_back(m_titleSprite);

		//1番→star_chips(星屑)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/star_chips.dds", 1280.0f, 720.0f);
		m_titleSprite->SetMulColor({ 0.0f,0.0f ,0.0f ,1.0f });
		m_spriteRender.push_back(m_titleSprite);

		//2番→Game_title
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/game_title.dds", 650.0f, 150.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetPosition({ 0.0f,280.0f,0.0f });
		m_titleSprite->SetScale({ 0.65f,0.65f,0.65f });
		m_spriteRender.push_back(m_titleSprite);

		//3番→light
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/light.dds", 1280.0f, 720.0f);
		m_titleSprite->SetAlpha(0.5f);
		m_titleSprite->SetMulColor({ 0.0f,0.0f ,0.0f ,1.0f });
		m_spriteRender.push_back(m_titleSprite);

	}
	//小人
	{
		//4番→Villain1
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain1.dds", 100.0f, 200.0f);
		m_titleSprite->SetPosition({ 450.0f,-225.0f,0.0f });
		m_titleSprite->SetScale({ 0.6f,0.6f,0.6f });
		m_spriteRender.push_back(m_titleSprite);

		//5番→Villain2
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain2.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//6番→Villain3
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain3.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//7番→Villain4
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain4.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//8番→Villain5
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain5.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//9番→Villain6
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain6.dds", 120.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//10番→Villain7
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain7.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//11番→Villain8
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain8.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.3f,0.3f,0.3f });
		m_spriteRender.push_back(m_titleSprite);

		//12番→Villain9
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/Villain9.dds", 100.0f, 200.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_titleSprite->SetScale({ 0.5f,0.5f,0.5f });
		m_spriteRender.push_back(m_titleSprite);
	}
	//フォント
	{
		//はじめる
		m_startFont = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* start = L"Start";
		m_startFont->SetText(start);
		m_startFont->SetAlpha(0.0);
		m_startFont->SetPosition(m_startFontPos);
		m_startFont->SetScale(m_startFontScale);
		//続きから
		m_loadFont = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* load = L"Load";
		m_loadFont->SetText(load);
		m_loadFont->SetScale(m_startFontScale);
		m_loadFont->SetAlpha(0.0);
		m_loadFont->SetPosition(m_loadFontPos);
	}
	
	/*m_titleBgm = g_goMgr->NewGameObject<CSoundSource>();
	m_titleBgm->Init(L"Assets/sound/stage1BGM.wav");
	m_titleBgm->Play(false);*/

	return true;
}

void Title::SelectButtun(FontRender* m_font)
{
	//選択中のボタン

}
void Title::LightFlashing()
{
	//ライトの点滅
	m_flashingTimer++;
	if (m_flashingTimer <= m_lightsUpTime) {
		m_spriteRender[3]->DeltaAlpha(m_lightAlpha);
	}
	else if (m_flashingTimer <= m_lightsOffTime)
	{
		m_spriteRender[3]->DeltaAlpha(-m_lightAlpha);
	}
	else {
		m_flashingTimer = 0.0f;
	}

}

void Title::TitleFadeIn() 
{
	//フェードイン。
	FadeIn* fadein = g_goMgr->NewGameObject<FadeIn>();
	fadein->SetSprite(m_spriteRender[0]);
	fadein = g_goMgr->NewGameObject<FadeIn>();
	fadein->SetSprite(m_spriteRender[1]);
	fadein = g_goMgr->NewGameObject<FadeIn>();
	fadein->SetSprite(m_spriteRender[3]);

	if (m_spriteRender[3]->GetMulColor().x >= 1.0f &&
		m_spriteRender[3]->GetMulColor().y >= 1.0f &&
		m_spriteRender[3]->GetMulColor().z >= 1.0f ) 
	{
		m_state = Title_GameTitle;
	}
}
void Title::TitleGameTitle()
{
	//文字の表示。
	//タイトルの後に選択ボタンを表示させます。
	m_fontTimer++;
	if (m_fontTimer <= 30) {

	}
	else if (m_fontTimer >= 30) {

	}
	else {

	}
	m_spriteRender[3]->DeltaAlpha(-m_lightAlpha);

	m_startFont->SetAlpha(0.0);
	m_loadFont->SetAlpha(0.0);

}
void Title::TitleSelect()
{
	//ボタン選択。
}
void Title::TitleFadeOut()
{
	//フェードアウト。
}

void Title::Update()
{
	switch (m_state)
	{
	case Title::Title_FadeIn:
		TitleFadeIn();			//フェードイン。
		break;
	case Title::Title_GameTitle:
		TitleGameTitle();		//文字の表示。
		break;
	case Title::Title_Select:
		TitleSelect();			//ボタン選択。
		break;
	case Title::Title_FadeOut:
		TitleFadeOut();		//フェードアウト。
		break;
	}
}
