#include "stdafx.h"
#include "Item.h"
#include "GameData.h"

Item::Item()
{
}

Item::~Item()
{
}

bool Item::Start()
{
	m_ItemModelRender = g_goMgr->NewGameObject<SkinModelRender>();
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
	//�A�C�e���o��
	//�΂ߑO�ɏo���܂��您
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

