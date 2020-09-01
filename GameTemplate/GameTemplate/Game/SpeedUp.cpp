#include "stdafx.h"
#include "SpeedUp.h"
#include "Player.h"
#include "EffectManager.h"


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
		//0�ԁ��g
		m_Sprite = g_goMgr->NewGameObject<SpriteRender>();
		m_Sprite->Init(L"Assets/sprite/itemframe.dds", 75.0f, 50.0f);
		m_Sprite->SetPosition({ 0.55f,0.55f ,0.55f });
		m_Sprite->SetScale({ 0.55f,0.55f ,0.55f });
		m_spriteRender.push_back(m_Sprite);

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
	
}
void SpeedUp::Flashing()
{
	//�_�ŁB
}
void SpeedUp::EndUse()
{
	//�I���B
}
void SpeedUp::Update()
{
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
