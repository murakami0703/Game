#include "stdafx.h"
#include "Result.h"
#include "Gamedata.h"

Result* Result::m_instance = nullptr;

Result::Result()
{
	if (m_instance != nullptr) {
			std::abort();//���łɏo�Ă��邽�߃N���b�V��
		}
	m_instance = this;

	//�w�i�œ�����texture
	{
		//0�ԁ�Result_Backgraund1
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Backgraund.dds", 1280.0f, 720.0f);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);
		//1�ԁ�Result_Backgraund2
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Backgraund.dds", 1280.0f, 720.0f);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);
	}
	//2�ԁ�R
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/tesst.dds", 1280, 720.0f);
	m_itemSprite->SetPosition(m_bgStartPos);
	m_itemSprite->SetAlpha(1.0f);
	m_spriteRender.push_back(m_itemSprite);

	//���U���g����
	{

		//3�ԁ�R
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_R.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos1, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//4�ԁ�e
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_e.dds", 210.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos2, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//5�ԁ�s
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_s.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos3, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//6�ԁ�u
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_u.dds", 200.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos4, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//7�ԁ�l
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_l.dds", 220.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos5, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

		//8�ԁ�t
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_t.dds", 220.0f, 760.0f);
		m_itemSprite->SetPosScale(m_resultPos6, m_resultScale);
		m_itemSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_itemSprite);

	}
	//��Ί֘A
	{
		//8�ԁ����
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/jewelry_01.png.dds", 400.0f, 600.0f);
		m_itemSprite->SetAlpha(0.5f);
		m_spriteRender.push_back(m_itemSprite);

	}

	//�ӂ����
	{
		m_font = g_goMgr->NewGameObject<FontRender>();
		const wchar_t* str = L"�����`�`�`�`�`�`�`";
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
	CVector3 m_position = m_sprite->GetPosition();	//���W�B
	float m_alpha = m_sprite->GetAlpha();			//�����x
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
	//Backgraund��\���B
	//�E����\��������
	CVector3 m_position = m_spriteRender[2]->GetPosition();	//���W�B
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
	//Resultsprite���k���A����ɁB
	SpriteMove(m_spriteRender[3]);
	SpriteMove(m_spriteRender[4]);
	SpriteMove(m_spriteRender[5]);
	SpriteMove(m_spriteRender[6]);
	SpriteMove(m_spriteRender[7]);
	SpriteMove(m_spriteRender[8]);

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
