#include "stdafx.h"
#include "SpeedUp.h"
#include "Player.h"
#include "EffectManager.h"
#include "GameData.h"


SpeedUp::SpeedUp()
{
}


SpeedUp::~SpeedUp()
{
}

bool SpeedUp::Start()
{
	//�A�C�e���g�p
	{
		//1�ԁ��X�s�[�h�A�b�v��
		m_Sprite = g_goMgr->NewGameObject<SpriteRender>();
		m_Sprite->Init(L"Assets/sprite/speedUp.dds", 250.0f, 250.0f);
		m_Sprite->SetPosition({ 0.55f,0.55f ,0.55f });
		m_Sprite->SetScale({ 0.55f,0.55f ,0.55f });
		m_spriteRender.push_back(m_Sprite);
	}
	return true;
}
void SpeedUp::InUse()
{
	//�g�p���B
	GameData* gamedata = GameData::GetInstance();
	if (m_timer < 1) {
		//�ړ����x�A�b�v�B
		gamedata->SPDCalc(1.0f);
	}
	else if (m_timer > 600) {
		m_state = Flashing_Use;
	}
}
void SpeedUp::Flashing()
{
	//�_�ŁB
	if (m_timer <= 900) {
		m_changeCount++;
		if (m_changeCount < 10) {
			m_spriteRender[0]->DeltaAlpha(0.0f);
		}
		else if (m_changeCount > 10 && m_changeCount < 20) {
			m_spriteRender[0]->DeltaAlpha(1.0f);
		}
		else {
			m_changeCount = 0;
		}
	}
	else {
		m_state = End_Use;
	}

}
void SpeedUp::EndUse()
{
	//�I���B
	//���X�����B
	GameData* gamedata = GameData::GetInstance();
	gamedata->SPDCalc(-1.0f);
	g_goMgr->DeleteGameObject(this);
}
void SpeedUp::Update()
{
	m_timer++;

	switch (m_state)
	{
	case SpeedUp::In_Use:
		break;
	case SpeedUp::Flashing_Use:
		break;
	case SpeedUp::End_Use:
		break;
	}
}
