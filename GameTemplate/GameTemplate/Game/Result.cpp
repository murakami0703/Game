#include "stdafx.h"
#include "Result.h"

Result* Result::m_instance = nullptr;

Result::Result()
{
	if (m_instance != nullptr) {
			std::abort();//���łɏo�Ă��邽�߃N���b�V��
		}
	m_instance = this;

	//���U���g
	{
		//0�ԁ�R
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_R.dds", 220.0f, 760.0f);
		m_itemSprite->SetPosition({ -500.0f,0.0f,0.0f });
		m_spriteRender.push_back(m_itemSprite);

		//1�ԁ�e
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_e.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosition({ -300.0f,0.0f,0.0f });
		m_spriteRender.push_back(m_itemSprite);

		//2�ԁ�s
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_s.dds", 210.0f, 760.0f);
		m_itemSprite->SetPosition({ -100.0f,0.0f,0.0f });
		m_spriteRender.push_back(m_itemSprite);

		//3�ԁ�u
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_u.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosition({ 100.0f,0.0f,0.0f });
		m_spriteRender.push_back(m_itemSprite);
		//2�ԁ�l
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_l.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosition({ 300.0f,0.0f,0.0f });
		m_spriteRender.push_back(m_itemSprite);

		//3�ԁ�t
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_t.dds", 220.0f, 760.0f);
		m_itemSprite->SetPosition({ 500.0f,0.0f,0.0f });
		m_spriteRender.push_back(m_itemSprite);

	}
	//�ӂ����
	m_font = g_goMgr->NewGameObject<FontRender>();
	const wchar_t* str = L"�����`�`�`�`�`�`�`";
	m_font->SetText(str);
	m_font->SetPosition({ -500.0f,0.0f });

	m_font->SetPivot({ 0.2f,0.2f });
	
}
Result::~Result()
{
	m_instance = nullptr;

}
void Result::SpriteBound(SpriteRender& m_sprite)
{

}

void Result::Update()
{

}
