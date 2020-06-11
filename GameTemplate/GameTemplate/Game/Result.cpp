#include "stdafx.h"
#include "Result.h"
#include "Gamedata.h"

Result* Result::m_instance = nullptr;

Result::Result()
{
	if (m_instance != nullptr) {
			std::abort();//すでに出ているためクラッシュ
		}
	m_instance = this;

	//背景で動かすtexture
	{
		//0番→Result_Backgraund1
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Backgraund.dds", 1280.0f, 720.0f);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);
		//1番→Result_Backgraund2
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Backgraund.dds", 1280.0f, 720.0f);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);
	}
	//2番→R
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/tesst.dds", 1280, 720.0f);
	m_itemSprite->SetPosition(m_bgStartPos);
	m_itemSprite->SetAlpha(1.0f);
	m_spriteRender.push_back(m_itemSprite);

	//リザルト文字
	{

		//3番→R
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_R.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos1, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//4番→e
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_e.dds", 210.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos2, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//5番→s
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_s.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos3, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//6番→u
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_u.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos4, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//7番→l
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_l.dds", 220.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos5, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//8番→t
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_t.dds", 220.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos6, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

	}
	//宝石関連
	{
		//8番→宝石
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/jewelry_01.png.dds", 400.0f, 600.0f);
		m_itemSprite->SetAlpha(0.5f);
		m_spriteRender.push_back(m_itemSprite);

	}

	//ふぉんと
	{
		m_font = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* str = L"おわり～～～～～～～";
		m_font->SetText(str);
		m_font->SetPosition({ -500.0f,0.0f });

		m_font->SetPivot({ 0.2f,0.2f });
	}
}
Result::~Result()
{
	m_instance = nullptr;

}
void Result::SpriteMove(SpriteRender* m_sprite)
{
	CVector3 m_position = m_sprite->GetPosition();	//座標。
	float m_alpha = m_sprite->GetAlpha();			//透明度
	if (m_position.y > m_resultSetYPos) {
			m_position.y -= 10.0f;

	}
	if (m_alpha < 1.0f) {
		m_alpha += 0.1f;

	}
	m_sprite->SetPosition(m_position);
	m_sprite->SetAlpha(m_alpha);

}
void  Result::Bound()
{
	//Backgraundを表示。
	//右から表示させる
	CVector3 m_position = m_spriteRender[2]->GetPosition();	//座標。
	if (m_position.x > 0.0f) {
		m_position.x -= 20.0f;
		m_spriteRender[2]->SetPosition(m_position);

	}
	else {
		m_state = Result_SpriteMove;
	}
	
}
void  Result::TopLeft()
{
	//Resultspriteを縮小、左上に。
	SpriteMove(m_spriteRender[3]);
	SpriteMove(m_spriteRender[4]);
	SpriteMove(m_spriteRender[5]);
	SpriteMove(m_spriteRender[6]);
	SpriteMove(m_spriteRender[7]);
	SpriteMove(m_spriteRender[8]);

}
void  Result::Soul()
{
	//stageでゲットした魂の数カウント
}
void  Result::Total()
{
	//合計魂のカウント

}
void  Result::Jewelry()
{
	//ボスが排出した宝石処理

}

void Result::Update()
{
	switch (m_state)
	{
	case Result::Result_Background:
		Bound();
		break;
	case Result::Result_SpriteMove:
		TopLeft();
		break;
	case Result::Result_Soul:
		Soul();
		break;
	case Result::Result_Total:
		Total();
		break;
	case Result::Result_Jewelry:
		Jewelry();
		break;
	}
}
