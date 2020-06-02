#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title* Title::m_instance = nullptr;

Title::Title()
{
	m_instance = this;

	{
		//0�ԁ�Title(�w�i)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/title.dds", 1280.0f, 720.0f);
		m_spriteRender.push_back(m_titleSprite);

		//1�ԁ�star_chips(����)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/star_chips.dds", 1280.0f, 720.0f);
		m_titleSprite->SetAlpha(1.0f);
		m_spriteRender.push_back(m_titleSprite);

		//2�ԁ�Game_title
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/game_title.dds", 400.0f, 80.0f);
		m_titleSprite->SetPosition({ 0.0f,280.0f,0.0f });
		m_spriteRender.push_back(m_titleSprite);

		//3�ԁ�light
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/light.dds", 1280.0f, 720.0f);
		m_titleSprite->SetAlpha(0.5f);
		m_spriteRender.push_back(m_titleSprite);

	}
	//�t�H���g
	{
		m_startFont = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* start = L"�͂��߂�";
		m_startFont->SetText(start);
		m_startFont->SetPosition(m_startFontPos);

		m_loadFont = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* load = L"�Â���";
		m_loadFont->SetText(load);
		m_loadFont->SetPosition(m_loadFontPos);

	}
}


Title::~Title()
{

}
void Title::SelectButtun(FontRender* m_font)
{
	//�I�𒆂̃{�^��
}
void Title::LightFlashing()
{
	//���C�g�̓_��
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
void Title::Update()
{

	LightFlashing();
	if (g_pad[0].IsTrigger(enButtonStart)) {
		g_goMgr->NewGameObject<Game>();

	}

}
