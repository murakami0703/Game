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

	//0番→枠
	m_Sprite = g_goMgr->NewGameObject<SpriteRender>();
	m_Sprite->Init(L"Assets/sprite/spe.dds", 250.0f, 250.0f);
	m_Sprite->SetPosition({ 0.55f,0.55f ,0.55f });
	m_Sprite->SetScale({ 0.55f,0.55f ,0.55f });
	m_spriteRender.push_back(m_Sprite);

	//1番→スピードアップ薬
	m_Sprite = g_goMgr->NewGameObject<SpriteRender>();
	m_Sprite->Init(L"Assets/sprite/spe.dds", 250.0f, 250.0f);
	m_Sprite->SetPosition({ 0.55f,0.55f ,0.55f });
	m_Sprite->SetScale({ 0.55f,0.55f ,0.55f });
	m_spriteRender.push_back(m_Sprite);

	return true;
}
void SpeedUp::InUse()
{
	//使用中。
}
void SpeedUp::Flashing()
{
	//点滅。
}
void SpeedUp::EndUse()
{
	//終わり。
}

