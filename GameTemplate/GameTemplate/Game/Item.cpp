#include "stdafx.h"
#include "Item.h"
#include "GameData.h"

Item::Item()
{
	//�A�C�e��
	{
		//0�ԁ��񕜖�
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/test.dds", 250.0f, 250.0f);
		m_itemSprite->SetPosition(m_itemC1Pos);
		m_spriteRender.push_back(m_itemSprite);

		/*//1�ԁ����e
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/test.dds", 100.0f, 100.0f);
		m_itemSprite->SetPosition(m_itemC2Pos);
		m_spriteRender.push_back(m_itemSprite);

		//2�ԁ��U����UP
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/test.dds", 100.0f, 100.0f);
		m_itemSprite->SetPosition(m_itemC3Pos);
		m_spriteRender.push_back(m_itemSprite);

		//3�ԁ��ړ����xUP
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/test.dds", 100.0f, 100.0f);
		m_itemSprite->SetPosition(m_itemC4Pos);
		m_spriteRender.push_back(m_itemSprite);
		*/
	}
	//�A�C�e���J�E���g�t�H���g�̐ݒ�B
	GameData* m_gamedate = GameData::GetInstance();
	{
		/*//�񕜖�
		m_itemFont1 = g_goMgr->NewGameObject<FontRender>();
		wchar_t ItemHpRecText[256];
		swprintf(ItemHpRecText, L"%02d", m_gamedate->GetItemHpRecovery());
		m_itemFont1->SetText(ItemHpRecText);
		m_itemFont1->SetPosition({ 460.0f,-240.0f});

		//���e
		m_itemFont2 = g_goMgr->NewGameObject<FontRender>();
		wchar_t ItemBumText[256];
		swprintf(ItemBumText, L"%02d", m_gamedate->GetItemBum());
		m_itemFont2->SetText(ItemBumText);
		//m_itemFont2->SetPosition({ 460.0f,-240.0f });

		//�U����UP
		m_itemFont3 = g_goMgr->NewGameObject<FontRender>();
		wchar_t ItemAtUpText[256];
		swprintf(ItemAtUpText, L"%02d", m_gamedate->GetItemAttackUp());
		m_itemFont3->SetText(ItemAtUpText);
		//m_itemFont3->SetPosition({ 460.0f,-240.0f });

		//�ړ����xUP
		m_itemFont4 = g_goMgr->NewGameObject<FontRender>();
		wchar_t ItemSpeedUpText[256];
		swprintf(ItemSpeedUpText, L"%02d", m_gamedate->GetItemHpRecovery());
		m_itemFont4->SetText(ItemSpeedUpText);
		//m_itemFont4->SetPosition({ 460.0f,-240.0f });
		*/
	}

}

Item::~Item()
{
}
void Item::ItemCountMove(FontRender* m_font)
{
	//�A�C�e���������ɏ�ɓ������B
	m_font->GetPosition();
}
void Item::Update()
{

}

