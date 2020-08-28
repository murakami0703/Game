#include "stdafx.h"
#include "Item.h"
#include "GameData.h"
#include "Player.h"

Item::Item()
{
}

Item::~Item()
{
}

bool Item::Start()
{
	m_ItemModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	//�����_���ŕ��������肵�ē����܂�
	m_itemNum = rand() % 3;

	//�o��������A�C�e����cmo�t�@�C���̓ǂݍ��݁B
	if (m_itemNum == 0) {
		m_ItemModelRender->Init(L"Assets/modelData/HpRecovery.cmo");

	}
	else if(m_itemNum == 1) {
		m_ItemModelRender->Init(L"Assets/modelData/Bum.cmo");
	}
	else if (m_itemNum == 2) {
		m_ItemModelRender->Init(L"Assets/modelData/AttackUp.cmo");
	}
	else if (m_itemNum == 3) {
		m_ItemModelRender->Init(L"Assets/modelData/SpeedUp.cmo");
	}

	m_ItemModelRender->SetPosition(m_position);	//���W�̐ݒ�B
	//�V���h�E�L���X�^�[�ɓo�^�B
	m_ItemModelRender->SetShadowCaster(true);

	return  true;

}
void Item::ItemAppear()
{
	Player* player = Player::GetInstance();
	//�A�C�e���o��
	//�΂ߑO�ɏo���܂��您
	m_position.x -= 1.0f;
	if (m_timer > ITEM_APPEAR_TIME) {
		//���ŁB
		m_state = Item_Destroy;
	}
	if ((player->GetPosition() - m_position).Length() <= 100.0f) {
		m_state = Item_Get;
	}
}
void Item::ItemGet()
{
	//�A�C�e���l���B
	if (m_itemNum == 0) {
		GameData::GetInstance()->HPRecoveryCalc(1);
	}
	else if (m_itemNum == 1) {
		GameData::GetInstance()->BumCalc(1);
	}
	else if (m_itemNum == 2) {
		GameData::GetInstance()->AttackUpCalc(1);
	}
	else if (m_itemNum == 3) {
		GameData::GetInstance()->SpeedUpCalc(1);
	}

	g_goMgr->DeleteGameObject(m_ItemModelRender);
	g_goMgr->DeleteGameObject(this);

}
void Item::ItemDestroy()
{
	//�A�C�e���폜�B
	//���Ԍo�߂̂��ߏ��ŁB
	g_goMgr->DeleteGameObject(m_ItemModelRender);
	g_goMgr->DeleteGameObject(this);

}

void Item::Update()
{
	switch (m_state)
	{
	case Item::Item_Appear:
		ItemAppear();
		break;
	case Item::Item_Get:
		ItemGet();
		break;
	case Item::Item_Destroy:
		ItemDestroy();
		break;
	}

	//���[���h�s��̍X�V�B
	m_ItemModelRender->SetPosition(m_position);

}

