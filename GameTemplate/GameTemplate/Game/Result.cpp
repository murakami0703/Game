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
		m_itemSprite->SetPosition({ -m_startXPos3,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//1�ԁ�e
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_e.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosition({ -m_startXPos2,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//2�ԁ�s
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_s.dds", 210.0f, 760.0f);
		m_itemSprite->SetPosition({ -m_startXPos1,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//3�ԁ�u
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_u.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosition({ m_startXPos1,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);
		//2�ԁ�l
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_l.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosition({ m_startXPos2,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//3�ԁ�t
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_t.dds", 220.0f, 760.0f);
		m_itemSprite->SetPosition({ m_startXPos3,m_startYPos,0.0f });
		m_itemSprite->SetAlpha(0.0f);
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
void Result::SpriteBound(SpriteRender* m_sprite)
{
	CVector3 m_position = m_sprite->GetPosition();			//���W�B
	float alpha = m_sprite->GetAlpha();			//���W�B

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
	//Resultsprite���o�E���h�\���B


}
void  Result::TopLeft()
{
	//Resultsprite���k���A����ɁB

}
void  Result::Soul()
{
	//stage�ŃQ�b�g�������̐��J�E���g
}
void  Result::Total()
{
	//���v���̃J�E���g

}
void  Result::Jewelry()
{
	//�{�X���r�o������Ώ���

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
