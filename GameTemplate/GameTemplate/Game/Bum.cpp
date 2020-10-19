#include "stdafx.h"
#include "Bum.h"
#include "Player.h"


Bum::Bum()
{
}


Bum::~Bum()
{
}
bool Bum::Start()
{

	//���e
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/bomb.dds", 250.0f, 250.0f);
	m_itemSprite->SetPosition(NEXT1_ITEM_POSITION);
	m_itemSprite->SetScale(NEXT1_ITEM_SCALE);

	//�X�L�����f���B
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/box.cmo");
	m_position = Player::GetInstance()->GetPosition();
	m_position.y += 200.0f;
	m_skinModelRender->SetPosition(m_position);

	m_number = 1;			//�A�C�e���ʒu�ԍ��i�I�𒆁j

	return true;
}

void Bum::InUse()
{
	//�g�p���B
}
void Bum::EndUse()
{
	//�I���B
}
