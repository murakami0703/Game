#include "stdafx.h"
#include "Result.h"

Result* Result::m_instance = nullptr;

Result::Result()
{
	if (m_instance != nullptr) {
			std::abort();//すでに出ているためクラッシュ
		}
	m_instance = this;
	//リザルト
	{
		//0番→R
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_R.dds", 220.0f, 760.0f);
		m_itemSprite->SetPosition({ -m_startXPos3,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//1番→e
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_e.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosition({ -m_startXPos2,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//2番→s
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_s.dds", 210.0f, 760.0f);
		m_itemSprite->SetPosition({ -m_startXPos1,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//3番→u
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_u.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosition({ m_startXPos1,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);
		//2番→l
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_l.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosition({ m_startXPos2,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//3番→t
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_t.dds", 220.0f, 760.0f);
		m_itemSprite->SetPosition({ m_startXPos3,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

	}
	//ふぉんと
	m_font = g_goMgr->NewGameObject<FontRender>();
	const wchar_t* str = L"おわり～～～～～～～";
	m_font->SetText(str);
	m_font->SetPosition({ -500.0f,0.0f });

	m_font->SetPivot({ 0.2f,0.2f });
	
}
Result::~Result()
{
	m_instance = nullptr;

}
void Result::SpriteBound(SpriteRender* m_sprite)
{
	CVector3 m_position = m_sprite->GetPosition();			//座標。
	float alpha = m_sprite->GetAlpha();			//座標。

	if (alpha <= 1.0f) {
		alpha += (1.0f / 60.0);
	}

	if (m_position.y <= 0.0f) {
		m_a = -m_a;
	}
	else if (m_position.y >= 250.0f) {
			m_position.y -= m_a;

	}
	m_sprite->SetPosition(m_position);
	m_sprite->SetAlpha(alpha);

}
void  Result::Bound()
{
	//Resultspriteをバウンド表示。


}
void  Result::TopLeft()
{
	//Resultspriteを縮小、左上に。

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
	SpriteBound(m_spriteRender[0]);
	SpriteBound(m_spriteRender[1]);

	switch (m_state)
	{
	case Result::Result_Bound:
		Bound();
		break;
	case Result::Result_TopLeft:
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
