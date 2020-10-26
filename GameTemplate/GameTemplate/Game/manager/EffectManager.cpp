#include "stdafx.h"
#include "manager/EffectManager.h"
#include "graphics/effect/EffectPlay.h"

EffectManager* EffectManager::m_instance = nullptr;

EffectManager::EffectManager()
{

	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


EffectManager::~EffectManager()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool EffectManager::Start() { return true; }

//�G�t�F�N�g�Đ�
void EffectManager::EffectPlayer(EffectName EF, CVector3 position, CVector3 scale,CQuaternion m_rotation) {
	//�쐬
	EffectPlay* m_player = g_goMgr->NewGameObject<EffectPlay>();
	//���O�����������Ă���
	int len = (int)wcslen(DetaBase[EF]);
	for (int x = 0; x < len+1; x++) {
		EF_Name[x] = DetaBase[EF][x];
	}
	//�ݒ�
	m_player->SetAnimation(EF_Name);
	m_player->SetPosition(position);
	m_player->SetScale(scale);
	m_player->SetRotation(m_rotation);

}

void EffectManager::EffectPlayer(EffectName EF, CVector3 position, CVector3 scale) {
	//�쐬
	EffectPlay* m_player = g_goMgr->NewGameObject<EffectPlay>();
	//���O�����������Ă���
	int len = (int)wcslen(DetaBase[EF]);
	for (int x = 0; x < len + 1; x++) {
		EF_Name[x] = DetaBase[EF][x];
	}
	//�ݒ�
	m_player->SetAnimation(EF_Name);
	m_player->SetPosition(position);
	m_player->SetScale(scale);

}

void EffectManager::Update(){}
